#pragma once
#include "../../CSC3224-GameEngine/Game/Entity.h"

/*Class Bullet is an entity or SFML convex shape..*/

class Bullet : public Entity {

public:
	Bullet() {
		init();
	}

	~Bullet() {
	}

	//Instantiate bullet at certain position
	Bullet(sf::Vector2f pos) {
		init();

		setConvPos(pos);
	}


	Bullet(float x, float y) {
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
		//Bullet is not player controlled
		playerControlled = false;
		deleted = false;

		//Bullet is type 3, used for identification
		setType(3);

		//set bullet vertices or points -- Rotation is determined when bullet is used
		setPointConv(4);
		setMoveSpeed(60);
		sf::Vector2f points[4] = {{-0.5, 1},{ 0.5, 1 },{ 0.5,-1},{-0.5,-1 }};
		setPoints(points);
		sf::ConvexShape::setFillColor(sf::Color::White);
		isDynamic = true;
	}



	//Set clock to 0 so can add bullet to entity vector from bullet vec
	void setClock() {
		timeAlive.restart();
	}

	sf::Int32 getTime() {
		return timeAlive.getElapsedTime().asMilliseconds();
	}

	//Used this to determine how long bullet has been active for
	sf::Clock timeAlive;
};
