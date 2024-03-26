#pragma once

#include <SFML/Graphics.hpp>

/*Rend Window class used to initialise the SFML Render Window*/

class RendWindow {

public:
	
	//Create a new render window given heigh and width, and name it :)
	RendWindow(sf::Uint16 height, sf::Uint16 width, sf::String name);
	~RendWindow();

	void initialise();

	bool Init();

	//Created these just for ease of access i suppose. Used to display background, score-text and game entities
	void draw(sf::Text l);
	void draw(sf::ConvexShape l);
	void draw(sf::CircleShape l);
	void draw(sf::Sprite l);

	void clear();

	void display();

	sf::RenderWindow rendWind;

private:
	bool isFullScreen;
	
	sf::String sName;
	sf::Uint16 sHeight;
	sf::Uint16 sWidth;
};
