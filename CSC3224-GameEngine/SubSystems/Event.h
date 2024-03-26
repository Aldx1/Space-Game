#pragma once

#include "../../CSC3224-GameEngine/Game/GameActions.h"
#include "../../CSC3224-GameEngine/Game/GameScene.h"

/* Created this class just to pass through player events to the game action class from human interface */
class Event {
public:
	Event(GameActions*);
	~Event();

	void ActOnPlayerEvent(std::vector<bool> events);

private:
	GameActions* action;

};

