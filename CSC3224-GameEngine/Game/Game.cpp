#include "../../CSC3224-GameEngine/Game/Game.h"

Game::Game(GameScene* sce, GameActions* act)  {
	scene = sce;
	action = act;
}


/*Run function containing the main game loop, 
runs while the SFML Render Window is initialised
or the player has no lives */

//Includes 3 loops for the game, the first to introduce the controls, the next is the main loop and finally a loop to see highscores
//Could have split the functionality up a bit here, but wanted to keep it under one function

void Game::run() {

	sf::Clock clock;
	HumanInterface keybo = HumanInterface(scene, action);

	scene->playB();

	//Intro Text
	sf::Text introduc;
	introduc.setFont((*scene->getFont(0)));
	introduc.setCharacterSize(20);
	introduc.setFillColor(sf::Color::Red);
	introduc.setStyle(sf::Text::Bold);
	introduc.setPosition(100, 100);
	introduc.setString("Press the up and down key to move back and forward \n\n Left and right to rotate \n\n Space to shoot and P to pause :) \n\n Press Enter to start the game");




	/********** Intro loop to introduce the keys :) ***************/

	while (scene->getG()->window.Init() && !(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))) {

		keybo.checkWindowEvent();
		scene->getG()->window.clear();
		scene->getG()->window.draw(introduc);
		scene->display();
	}
	/**************  END of INTRO LOOP ***********/





	/******************** MAIN game LOOP *******************/

	//While graphics window is initialised continue to run...
	while (scene->getG()->window.Init()) {

		//If the game has finished, ie player has no lives. 
		if (!action->isGameOver()) {

			//Human Interface class acting on input keys
			keybo.Act();

			//If the game is not paused carry on to update the scene and check input
			if (!action->isPaused()) {

				//Update the game scene with the time elapsed from each loop
				scene->update(clock.getElapsedTime().asMilliseconds());

				//Ask the action class to anything within the game 
				action->React();
			}

			//If game is paused then check to see if is unpaused.. 
			if (action->isPaused()) {

				//Total up running time of the game
				scene->totalT(clock.getElapsedTime().asMilliseconds());
			}

			clock.restart();
		}

		//If game is over i.e. player has no lives left then break out the Game Loop
		if (action->isGameOver()) {
			break;
		}

		scene->display();
	}
	/*************** END of MAIN game LOOP *************/






	/**** Start to the High score element of the game *****/

	sf::Text scores;
	std::vector<std::string> names;
	std::string temp = "";
	std::vector<int> jj;
	FileLoader fl;

	bool loaded = false;

	//Load in Highscore file
	if (fl.loadFile("../Assets/Files/")) {
		loaded = true;

		names = fl.getNames();
		jj = fl.getScores();

		temp += "Highscores :\n";
		//List the top 5 scores from the highscore text file
		for (unsigned int i = 0; i < 5; i++) {

			temp += names.at(i) + "\n";
			if (i + 1 >= names.size()) {
				break;
			}
		}
	}
	else {
		temp += " Highscores Unable to load";
	}


	//Set properties for the highscore text in the window
	scores.setFont((*scene->getFont(0)));
	scores.setCharacterSize(25);
	scores.setFillColor(sf::Color::Red);
	scores.setStyle(sf::Text::Bold);
	scores.setPosition(200, 100);
	scores.setString(temp);

	//Position to insert the score
	unsigned int count = 0;

	//Check to see if score is a highscore depnding on previous scores and size
	bool highSCORE = false;

	//Loop through to see where to load the score. 
	if (loaded) {

		//If scores vector is less than 5 it will be a highscore
		unsigned int tag = 5;
		if (jj.size() < 5) {
			tag = jj.size();
			highSCORE = true;
		}

		//Find position to place the score if it a high one
		for (unsigned int i = 0; i < tag; i++) {
			if (action->getScore() > jj.at(i)) {
				highSCORE = true;
				break;
			}
			count++;
		}
	}

	//Change string accordingly if it is or isn't a high score
	std::string getName = "Enter Name: ";
	if (!highSCORE) {
		getName = "Not a High Score, Better Luck Next Time";
	}

	/*Random Strings using to try and initialise the highscore element of the game*/
	std::string name = "";
	sf::Text text;
	text.setFont((*scene->getFont(0)));
	text.setCharacterSize(25);
	text.setFillColor(sf::Color::Red);
	text.setStyle(sf::Text::Bold);
	text.setPosition(200, 400);


	/********** HIGH score LOOP *************/
	//Loop to enter name and add to the highscore text file
	while (scene->getG()->window.Init()) {

		if (highSCORE) {
			keybo.checkEndInput(name);
		}
		text.setString(getName + name);

		keybo.checkWindowEvent();

		scene->getG()->window.clear();
		scene->getG()->window.draw(text);
		scene->getG()->window.draw(scores);
		scene->display();
	}
	/********* END of HIGH score LOOP ***********/


	std::string h;

	//If its a high score and name has been entered update the score vector and pass it to the file loader.
	if (name.size() > 1 && highSCORE) {
		h = name + " : " + std::to_string(action->getScore());
		names.insert(names.begin() + count, h);
		fl.updateScores("../Assets/Files/", names);
	}
}