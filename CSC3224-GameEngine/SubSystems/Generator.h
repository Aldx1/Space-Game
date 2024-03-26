#pragma once

#include "../../CSC3224-GameEngine/Game/Ship.h"
#include "../../CSC3224-GameEngine/Game/Asteroid.h"
#include "../../CSC3224-GameEngine/Game/Bullet.h"
#include "../../CSC3224-GameEngine/Game/DestroyedAsteroid.h"
#include "../../CSC3224-GameEngine/SubSystems/MemoryManager.h"
#include "../../CSC3224-GameEngine/SubSystems/Physics.h"
#include <SFML\System\Time.hpp>
#include <SFML\Audio.hpp>


/*Generator class used to create scenarios for the game */

/* Updates Entity vector as well as producing random starting 
 positions and rotations for the asteroids. Instantiates the appropriate 
 vectors for each entity if any fall below a certain level */

class Generator {

public:
	Generator(MemoryManager<sf::Texture> * texs, b2World* world, Physics* p);
	~Generator();

	//function to initialise the game objects, to be called from the game scene class. 
	void InitGameObjects(std::vector<Entity*> &Entities);

	//Add bullet to the entity vector
	void addBullet(std::vector<Entity*>& Entities);

	//Return a random value used for asteroid position and rotation
	float randomValue(float min, float max) {
		return ((float)rand() / (float)RAND_MAX) * (max - min) + min;
	}
	
	//Function to just update the game entities in the world, such as deleting bodies from physics world or removing from entity vector
	void updateGameWorld(b2World* world, std::vector<Entity*>&Entities) {

		//Delete the bodies from the physics world
		deleteBodies(world, Entities);

		//Remove entities from the entity vector if they have lived their life
		RemoveEntitites(Entities);

		//Update the entities vector, such as adding more asteroids
		updateGameEnts(Entities);
	}


	//Update the asteroid speed and quantity that appear on screen every 15 seconds, or however long decided in the action class
	void updateSpeed() {
		if (asterSpeed + 1.0f <= MAX_ASTEROID_SPEED) {
			asterSpeed += 1.0f;	
		}
		if (astersOnScreen + 1 <= MAX_ASTEROID_ONSCREEN) {
			astersOnScreen += 1;
		}
	}

	//Update the lives of the asteroids when a certain score has been reached
	void updateLife() {
		if (asterLife + 1.0f < +MAX_ASTEROID_LIFE) {
			asterLife += 1.0f;
		}
	}

	//Add entitiy to entities
	void addBody(std::vector<Entity*> &Entities, Entity& ent) {
		Entities.push_back(&ent);
	}
	

	//If bullets, asteroid or destroyed asteroid vectors fall below certain level
	bool bulletsRemain() {
		if (bullets.size() < 100) {
			return false;
		}
		else {
			return true;
		}
	}

	bool AstersRemain() {
		if (asteroids.size() < 100) {
			return false;
		}
		else {
			return true;
		}
	}

	bool DestroyedAstersRemain() {
		if (destroyedAsts.size() < 100) {
			return false;
		}
		else {
			return true;
		}
	}


	//Add more bullets, asteroids or destroyed asteroids.. Always update so the bullets have 10000 in the vector, 
	//asteroids and destroyed asteroids are both set to be at a size of 1000
	void addMoreBulls() {

		unsigned int dif = 10000 - bullets.size();
		for (unsigned int i = 0; i < dif; i++) {
			Bullet* bull = new Bullet();
			bullets.push_back(bull);
		}
	}

	void addMoreAsteroids() {

		unsigned int dif = 1000 - asteroids.size();
		for (unsigned int i = 0; i < dif; i++) {
			Asteroid* ast = new Asteroid();
			asteroids.push_back(ast);
		}
	}

	void addMoreDestroyed() {

		unsigned int dif = 1000 - destroyedAsts.size();
		for (unsigned int i = 0; i < dif; i++) {
			DestroyedAsteroid* ast = new DestroyedAsteroid();
			destroyedAsts.push_back(ast);
		}
	}


	//If asteroids in the entity vector falls below a certain level then add more
	void addAsterstoEnts(std::vector<Entity*> &Entities) {
		unsigned int coun = 0;
		for (unsigned int i = 0; i < Entities.size(); i++) {
			if (Entities.at(i)->getType() == 2) {
				coun++;
			}
		}
		unsigned int dif = 0;
		if (coun < astersOnScreen) {
			dif = astersOnScreen - coun;

			for (unsigned int i = 0; i < dif; i++) {
				addAsteroid(Entities);
			}
		}
	}

	std::vector<Asteroid*> getAsteroids() {
		return asteroids;
	}

	std::vector<Bullet*> getBullets() {
		return bullets;
	}
	
	Ship* getShip() {
		return ship;
	}

	Ship* ship;


	//These are used for the action class so it can react accordingly
	bool endGame;
	bool shot;
	bool explode;

private:

	//Set the max speed quanity and lives for the asteroid
	float MAX_ASTEROID_SPEED = 25.0f;
	unsigned int MAX_ASTEROID_ONSCREEN = 30;
	int   MAX_ASTEROID_LIFE = 3;

	//Used to create the asteroid properties with these variables, cannot exceed the max values defined above
	float asterSpeed;
	unsigned int astersOnScreen;
	int asterLife;


	//Update game entity vectors, i.e. bullets and asteroids. 
	void updateGameEnts(std::vector<Entity*> &Entities);

	//Remove entities from the entity vector
	void RemoveEntitites(std::vector<Entity*>& Entities);

	//Delete bodies from the physics world
	void deleteBodies(b2World* world, std::vector<Entity*> &Entities);

	//Add asteroid or destroyed asteroid to entity vector
	
	void addAsteroid(std::vector<Entity*>& Entities);
	void addDestroyedAsteroid(std::vector<Entity*> &Entities, float x, float y);


	//Bullets only live for 1 second where destroyed asteroids live for 1.5 seconds
	sf::Int32 bulletLife = 1000;
	sf::Int32 DESASTlife = 1500;
	
	std::vector<Bullet*> bullets;
	std::vector<Asteroid*> asteroids;
	std::vector<DestroyedAsteroid*> destroyedAsts;

	MemoryManager<sf::Texture> * textures;
	
	b2World* world;
	Physics* ph;
	
	//Generate a random starting position for the asteroid. 
	sf::Vector2f genAsterPos();

	//Generate a random Rotation for the asteroid pointing inwards of the screen, given the asteroids starting position
	float genAsterRot(sf::Vector2f pos);

};
