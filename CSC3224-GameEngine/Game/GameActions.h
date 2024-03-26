#pragma once

/*Game Actions Class -- used to control the state of the game.. Is it paused? Has the game ended?*/

//#include <SFML\System\Time.hpp>
#include <iostream>
#include "../../CSC3224-GameEngine/SubSystems/Generator.h"
#include "../../CSC3224-GameEngine/SubSystems/Sound.h"
#include "../../CSC3224-GameEngine/Game/GameScene.h"



class GameScene;

class GameActions {
public:
	GameActions(Generator*, Sound* s, GameScene* sce);
	~GameActions();

	void pause();

	void React();

	//Update the score when bullet collides with asteroid
	void updateScore() {
		score += 1;
	}

	//Is the game paused?
	bool isPaused() {
		return paused;
	}

	int getScore() {
		return score;
	}

	//Has the ship been hit? 
	bool isGameOver() {
		return gameIsOver;
	}


	void closeWindow();

	void playerMove(int dir);

	void playerRotate(int dir);

	void playerFire();

private:

	bool gameIsOver;
	bool paused;

	int score;
	int shotfired;

	int asterLifeUpdate;
	int LifeTag;


	sf::Int32 pauseTime;
	sf::Int32 asteroidUpdate;
	sf::Int32 firingTime;
	sf::Int32 fireLimit = 500;
	sf::Int32 Ptimer = 200;

	Ship* ship;

	Sound* sound;

	//Set the end game bool as true and stop the background music
	void endGame() {
		scene->stopB();
		sound->playSound(3);
		gameIsOver = true;
	}

	Generator* gen;
	GameScene* scene;
};
