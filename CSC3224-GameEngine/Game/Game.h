#pragma once

/* Game Class used containing the main game loop. 
Takes in the game scene and action pointers to be used to control the 
state and entities of the game */

#include "../../CSC3224-GameEngine/Game/GameScene.h"
#include "../../CSC3224-GameEngine/Game/GameActions.h"
#include "../../CSC3224-GameEngine/SubSystems/HumanInterface.h"


class Game {

public: 
	Game(GameScene* sce, GameActions* act);

	//Function containing the main game loop
	void run();

private:
	GameScene * scene;
	GameActions* action;
	
};
