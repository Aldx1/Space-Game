#include "../../CSC3224-GameEngine/Game/GameActions.h"


GameActions::GameActions(Generator* g, Sound* s, GameScene* sce) {
	paused = false;

	gen = g;
	sound = s;
	scene = sce;

	ship = g->getShip();

	pauseTime = 0;
	firingTime = 0;
	shotfired = 0;

	//Used to update the asteroid properties in the generator class
	asteroidUpdate = 0;
	LifeTag = 0;

	gameIsOver = false;
	score = 0;
}

GameActions::~GameActions() {
}

void GameActions::pause() {

	/*Used this if statement as you end up fighting with time to try and pause the game.
	Probably a more efficient way of manipulating the sf::keyboard class but seems to work ok*/
	if (scene->getTotalTime() - pauseTime > Ptimer || scene->getTotalTime() <= Ptimer) {
		if (!paused) {
			paused = true;
		}
		else {
			paused = false;
		}
		pauseTime = scene->getTotalTime();
	}
}

//Functions to either rotate or set the ships velocity
void GameActions::playerMove(int dir) {

	ship->setVelocity(scene->msec, dir);
}

void GameActions::playerRotate(int dir) {

	float angle = 2;
	
	if (dir == 0) {
		angle = -angle;
	}
	ship->rotate(angle);
}

void GameActions::closeWindow() {

	scene->closeWindow();
}


//Fire a bullet if the time lets you
void GameActions::playerFire() {
	
	//If firing time is within range then add bullet
	if ((scene->getTotalTime() - firingTime >= fireLimit) || (scene->getTotalTime() <= fireLimit && shotfired == 0)) {
		shotfired = 1;

		//Add a bullet in the generator class and play the shooting sound
		gen->addBullet(scene->getEnts());
		sound->playSound(0);

		//update the firing time
		firingTime = scene->getTotalTime();
	}
}


//React to anything such as game ending, or if a certain time has been reached to update the generator class
void GameActions::React() {

	//If generator states ship has no lives then end the game
	if (gen->endGame) {
		endGame();
	}
	
	//If the generator states an asteroid has been shot and has no lives left, update the score and play explode sound
	if (gen->explode) {
		updateScore();
		sound->playSound(2);
	}

	//If the generator states the asteroid has been shot, play the shot sound - more noticeable when asteroids have multiple lives
	if (gen->shot) {
		sound->playSound(4);
	}

	//Update the tags used to increase asteroid lives or speed
	asteroidUpdate += scene->msec;
	asterLifeUpdate = getScore() - LifeTag;
	
	//Update the asteroid speed and number of asteroids on screen every 15 seconds
	if (asteroidUpdate >= 15000) {
		asteroidUpdate = 0;
		gen->updateSpeed();
	}

	//Update the asteroid lives every time player gets a multiple of 30 points
	if (asterLifeUpdate >= 30) {
		asterLifeUpdate = 30;
		LifeTag = (getScore() / asterLifeUpdate) * getScore();
		asterLifeUpdate = 0;
		gen->updateLife();
	}

	scene->setScore(getScore());
}