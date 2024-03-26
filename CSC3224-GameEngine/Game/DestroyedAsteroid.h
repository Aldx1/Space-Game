#pragma once
#include "../../CSC3224-GameEngine/Game/Entity.h"
#include <SFML\Graphics\CircleShape.hpp>

/*Class Asteroid is an entity or SFML convex shape..*/

class DestroyedAsteroid : public Entity {
public:

	DestroyedAsteroid() {
		init();
	}

	~DestroyedAsteroid() {
	}

	//Create asteroid at defined position
	DestroyedAsteroid(float xPos, float yPos) {
		init();	
	}

	//Increase the radius only if it doesn't exceed the max radius
	void updateRadius() {

		if (getRadius() + 0.5f <= max_RADIUS) {
			setRadius(getRadius() + 0.5f);
		}
	}

	void setPos(sf::Vector2f f) {
		setCircPos(f);
	}
	void setPos(float x, float y) {
		setCircPos(x, y);
	}

	sf::Vector2f getPos() {
		return getCircPos();
	}

	void setText(sf::Texture& p) {
		setTextCirc(p);
	}


	void init() {

		deleted = false;
		//Type is 4 == Destroyed Asteroid
		setType(4);

		setCircPos(x, y);
		sf::CircleShape::setRadius(5.0f);
		setPointCirc(100);
		playerControlled = false;
		isDynamic = false;
	}

	//Get the time to determine whether to delete
	sf::Int32 getTime() {
		return timeDestroyed.getElapsedTime().asMilliseconds();
	}

	//Start the clock when joining the entity vector
	void setDestroyed() {
		timeDestroyed.restart();
	}

	sf::CircleShape* getShapeCircle() {
		return this;
	}
	
	//Used to determine how long explosion has taken place for
	sf::Clock timeDestroyed;

	float x, y;
	
	//Max destroyed radius
	float max_RADIUS = 20.0f;
};

