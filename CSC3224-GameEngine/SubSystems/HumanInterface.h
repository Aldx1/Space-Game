#pragma once

#include "../../CSC3224-GameEngine/SubSystems/Event.h"

/*Human Interface class used to determine which buttons have been pressed to make the game user friendly I suppose*/

class HumanInterface {

public:
	
	HumanInterface(GameScene*, GameActions*);
	~HumanInterface();


	//Act on player input and pass through to the event class
	void  Act();

	void checkInput();

	void checkPauseToggle();

	bool isJoystickConnected();
	
	void checkWindowEvent();

	void checkEndInput(std::string& name);

private:
	GameScene* scene;
	GameActions* action;

	//Actions to pass through the even class to act with
	std::vector<bool> actions;

	Event* eventHandler;
	
};
