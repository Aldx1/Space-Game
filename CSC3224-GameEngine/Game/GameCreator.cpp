#include "../../CSC3224-GameEngine/Game/GameCreator.h"

GameCreator::GameCreator() {

}
GameCreator::~GameCreator() {
	
	delete g;
	delete p;
	delete s;
	g = nullptr;
	p = nullptr;
	s = nullptr;
}


//Returns true if graphics, physics and sound have been initialised correctly.
bool GameCreator::Init() {

	g = new Graphics(800, 600);

	//Have graphics been initialised successfully
	if (!g->isInit()) {
		std::cout << "Graphics has had issues initialising" << std::endl;
		return false;
	}

	p = new Physics();
	s = new Sound();

	//Has Sound been initialised successfully
	if (!s->Init()) {
		return false;
	}

	return true;
}

//Create and return the gamescene used for Game Creator class. 
GameScene* GameCreator::createScene() {

	GameScene* scene = new GameScene(p, g, s);

	//Initialise the scene elements
	scene->Init();
	return scene;
}

//Same function as above except with the game actions..
GameActions* GameCreator::createActions(Generator* g, Sound* s, GameScene* sce) {

	GameActions* action = new GameActions(g, s, sce);
	return action;
}

