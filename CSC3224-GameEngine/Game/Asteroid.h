#pragma once
#include "../../CSC3224-GameEngine/Game/Entity.h"

/*Class Asteroid is an entity or SFML convex shape..*/

class Asteroid : public Entity {
public:
	Asteroid() {
		init();
	}

	~Asteroid() {
	}


	//Create asteroid at defined position
	Asteroid(sf::Vector2f pos) {
		init();
		setConvPos(pos);
		
	}

	Asteroid(float x, float y) {
		init();
		setConvPos(x, y);
	}

	void setPos(sf::Vector2f f) {
		setConvPos(f);
	}
	void setPos(float x, float y) {
		setConvPos(x, y);
	}

	sf::Vector2f getPos() {
		return getConvPos();
	}

	void setText(sf::Texture& p) {
		setTextConv(p);
	}

	void init() {
		
		//Used to play the explosion sound when shot..
		shot = false;

		//Asteroid is not player controlled
		playerControlled = false;

		//Type is 2 == asteroid
		setType(2);
		deleted = false;
		
		//Set as a square and move speed at 5
		setPointConv(4);
		sf::Vector2f points[4] = { { 10, -10 } ,{ 10, 10 },{ -10, 10 },{ -10, -10 }};
		setPoints(points);
		isDynamic = true;
	}

	//Attempted to try and make the explosion as central as possible, this function just gets all the transformed points and returns the calculated middle
	sf::Vector2f getMiddle() {
		sf::Vector2f p1 =  getTransform().transformPoint(getPoint(0));
		sf::Vector2f p2 = getTransform().transformPoint(getPoint(1));
		sf::Vector2f p3 = getTransform().transformPoint(getPoint(2));
		sf::Vector2f p4 = getTransform().transformPoint(getPoint(3));

		float x = (p1.x + p2.x + p3.x + p4.x) / 4.0f;
		float y = (p1.y + p2.y + p3.y + p4.y) / 4.0f;

		return sf::Vector2f(x - 10.5f, y - 10.5f);
	}

	bool shot;
	bool destroyed;
};
