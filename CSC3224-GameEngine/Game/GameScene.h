#pragma once

/*GameScene Class used to create all assets used within the game and to control the entities and actions */
#include <string>
#include "../../CSC3224-GameEngine/SubSystems/Physics.h"
#include "../../CSC3224-GameEngine/SubSystems/Graphics.h"
#include "../../CSC3224-GameEngine/Game/Ship.h"
#include "../../CSC3224-GameEngine/Game/Bullet.h"
#include "../../CSC3224-GameEngine/Game/Asteroid.h"
#include "../../CSC3224-GameEngine/SubSystems/FileLoader.h"
#include "../../CSC3224-GameEngine/SubSystems/Generator.h"

class GameScene {

public:
	GameScene(Physics* ph, Graphics* gr, Sound* so);
	~GameScene();

	void setScore(int sco) {
		score = sco;
	}

	//Has scene initialised successfully, objects created and sounds linked
	bool Init();
	
	
	//Play the lovely background music
	void playB() {
		if (s->getSounds().size() >= 2) {
			s->getSounds().at(1).setLoop(true);
			s->getSounds().at(1).play();
		}
	}
	void stopB() {
		if (s->getSounds().size() >= 2) {
			s->getSounds().at(1).stop();
		}
	}

	//Return a random value used for asteroid position and rotation
	float randomValue(float min, float max) {
		return ((float)rand() / (float)RAND_MAX) * (max - min) + min;
	}
		
	//Add entitiy to entities
	void addBody(Entity& ent) {
		Entities.push_back(&ent);
	}
	
	
	//Update render window graphics, and update physics world
	void update(sf::Int32 ms);
	

	Sound* getSound() {
		return s;
	}

	Graphics* getG() {
		return g;
	}

	Physics* getP() {
		return p;
	}

	Generator* getGen() {
		return gen;
	}

	//Both draws and display functions are used to link to the graphics window
	void drawScene();

	void display() {
		g->display();
	}

	//Total up the time
	void totalT(sf::Int32 ms) {
		totaltime += ms;
	}

	//Get total time
	sf::Int32& getTotalTime() {
		return totaltime;
	}

	void closeWindow();

	
	sf::Text text;
	
	
	std::vector<Entity*>& getEnts() {
		return Entities;
	}
	


	//Used for the running of the game, msec updates every iteration of the main game loop
	sf::Int32 msec;
	sf::Int32 totaltime;
	sf::Int32 bulletLife = 3000;
	
	sf::Font* getFont(int id) {
		return fonts->get(id);
	}


private:


	/*Vector for the game entities, could have probably
	been less lazy and used a Memory manager for this*/
	std::vector<Entity*> Entities;

	void InitObjects();
	void InitSounds();

	Physics* p;
	Graphics* g;
	Sound* s;
	Generator* gen;

	int score;
	
	b2World* world;

	MemoryManager<sf::Texture> * textures;
	MemoryManager<sf::Font> * fonts;
	
	bool nameEntered;

	sf::Font font;
};