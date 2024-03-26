#pragma once

#include <iostream>
#include <cmath> 

#include "../../SFML/include/SFML/Graphics/ConvexShape.hpp"
#include "../../CSC3224-GameEngine/SubSystems/RendWindow.h"
#include "../../CSC3224-GameEngine/Game/Bullet.h"
#include "../../CSC3224-GameEngine/Game/Ship.h"
#include "../../CSC3224-GameEngine/Game/Entity.h"
#include "../../CSC3224-GameEngine/Game/DestroyedAsteroid.h"

/*Graphics Class used to instantiate SFML window and draw to the render window screen*/

class Graphics {

public :
	Graphics(int width, int height);
	~Graphics();
	
	//Function used in early times, not sure if its needed but why not have it here
	float toRadians(float deg) {
		return (float) deg * PI / 180.0f;
	}
	
	//Has SFML RenderWindow initialised?
	bool isInit();	

	//Draw the single Sprite, for background usage
	void draw(sf::Sprite& s) {
		window.draw(s);
	}

	//Add background
	void addBack(sf::Sprite a) {
		back = a;
	}

	//Draw the scene of entites and the score
	void drawScene(sf::Text tex, std::vector<Entity*>);

	RendWindow window;

	void display();

private:

	sf::Sprite back;
};
