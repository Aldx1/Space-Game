#include "../../CSC3224-GameEngine/SubSystems/Event.h"

Event::Event(GameActions* act) {
	action = act;


}

Event::~Event() {
}


//Depending on the input - invoke the correct game actions function
void Event::ActOnPlayerEvent(std::vector<bool> events) {

	if (events.at(0) == true) {
		action->playerMove(1);
	}
	if (events.at(1) == true) {
		action->playerMove(0);
	}
	if (events.at(2) == true) {
		action->playerRotate(0);
	}
	if (events.at(3) == true) {
		action->playerRotate(1);
	}
	if (events.at(4) == true) {
		action->playerFire();
	}
	if (events.at(5) == true) {
		action->pause();
	}
	if (events.at(6) == true) {
		action->closeWindow();
	}

}