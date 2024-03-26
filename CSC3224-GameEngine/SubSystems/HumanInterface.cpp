#include "../../CSC3224-GameEngine/SubSystems/HumanInterface.h"


HumanInterface::HumanInterface(GameScene* sce, GameActions* act) {
	scene = sce;
	action = act;
	eventHandler = new Event(action);

	for (unsigned int i = 0; i < 7; i++) {
		actions.push_back(false);
	}
}

HumanInterface::~HumanInterface() {
	delete eventHandler;
}

void  HumanInterface::Act() {

	for (unsigned int i = 0; i < 7; i++) {
		actions.at(i) = false;
	}

	//Only if game is not paused then check user input
	if (!action->isPaused()) {
		checkInput();
	}

	//Check to see if user has unpaused 
	checkPauseToggle();

	//Pass through appropriate values to the event class
	eventHandler->ActOnPlayerEvent(actions);

}

void  HumanInterface::checkInput() {


	//Didn't have a controller to test with, so not sure if this works.
	//Meant for use with an Xbox 360 controller, have used values that were found online. 
	if (isJoystickConnected()) {

		//Dpad Up
		if (sf::Joystick::isButtonPressed(0, 11)) {

			actions.at(0) = true;
		}
		//DPad Down
		if (sf::Joystick::isButtonPressed(0, 12)) {

			actions.at(1) = true;
		}
		//Dpad Left
		if (sf::Joystick::isButtonPressed(0, 13)) {

			actions.at(2) = true;
		}
		//Dpad Right
		if (sf::Joystick::isButtonPressed(0, 14)) {

			actions.at(3) = true;
		
		}

		//A Button
		if (sf::Joystick::isButtonPressed(0, 0)) {

			actions.at(4) = true;
		}
	}


	//Rotate player 0 - ie to the left and 1 for the right rotation. 
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {

		actions.at(2) = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {

		actions.at(3) = true;
	}

	//Move player forward, sets velocity to - velocity if 0 is selected. 
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {

		actions.at(0) = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {

		actions.at(1) = true;
	}

	//Fire a bullet
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {

		actions.at(4) = true;
	}
}



//If Joystick is connected and start button is pressed or p on the keyboard then pause game,
void HumanInterface::checkPauseToggle() {


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {

		actions.at(5) = true;
	}

	if (isJoystickConnected()) {
		
		if (sf::Joystick::isButtonPressed(0, 8)) {

			actions.at(5) = true;
		}
	}


	checkWindowEvent();
}


//Seperate function used just placed it here for some reason. Checks window event i.e. close button
void HumanInterface::checkWindowEvent() {
	sf::Event event;

	if (scene->getG()->window.rendWind.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			scene->getG()->window.rendWind.close();
		}
	}
}


//Return true if a joystick is connected
bool HumanInterface::isJoystickConnected() {

	return sf::Joystick::isConnected(0);
}


//Used for the end of the game so the person can enter name
void HumanInterface::checkEndInput(std::string& name) {

	sf::Event evnt;

	while (scene->getG()->window.rendWind.pollEvent(evnt)) {

		switch (evnt.type) {

		case sf::Event::TextEntered:
			if (evnt.text.unicode < 128) {
				name += evnt.text.unicode;
			}
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)) {
		if (name != "") {
			name.erase(name.size() - 1);
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
		scene->getG()->window.rendWind.close();
	}
}