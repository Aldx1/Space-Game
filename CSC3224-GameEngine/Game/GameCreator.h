#pragma once

/*Game Creator class mainly used for initialising and shutting down the game..
Initialised Graphics, b2World and sound used for the game*/


#include "../../CSC3224-GameEngine/SubSystems/Graphics.h"
#include "../../CSC3224-GameEngine/SubSystems/Physics.h"
#include "../../CSC3224-GameEngine/Game/GameScene.h"
#include "../../CSC3224-GameEngine/Game/GameActions.h"
#include "../../CSC3224-GameEngine/SubSystems/Sound.h"

class GameCreator {

public:
	GameCreator();
	~GameCreator();

	bool Init();
	GameScene* createScene();
	GameActions* createActions(Generator* g, Sound* s, GameScene* sce);



private:
	Graphics* g;
	Physics* p;
	Sound* s;
	b2World* world;
};