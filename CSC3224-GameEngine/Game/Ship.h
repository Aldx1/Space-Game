#pragma once
#include "../../CSC3224-GameEngine/Game/Entity.h"

/*Class Ship is an entity or SFML convex shape..*/

class Ship : public Entity{

public:
	Ship() {
		init();
	}

	~Ship() {
	}

	//Instantiate ship at certain position and initialise
	Ship(sf::Vector2f pos) {
		init();
		setConvPos(pos);
	}
	Ship(float x, float y) {
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
		//Ship is player controlled
		playerControlled = true;
		deleted = false;
		
		//Type used for identification, Ship == 1
		setType(1);
		
		//Set points, rotation and move speed
		setPointConv(4);
		sf::Vector2f points[4] = { { -8, 17 } ,{ 0, -10 },{ 8, 17 },{ 0, 10 } };
		setPoints(points);
		sf::ConvexShape::setRotation(0);
		setMoveSpeed(20);
		isDynamic = true;
	}

	void rotate(float angle) {
		setRotation(getRotation() + angle);
	}
	
	//Get position of a point, to use for bullet start position
	sf::Vector2f getTurretPos() {
		return sf::ConvexShape::getTransform().transformPoint(sf::ConvexShape::getPoint(1));		
	}

	sf::ConvexShape* getShape() {
		return this;
	}
};
