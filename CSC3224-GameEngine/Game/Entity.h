#pragma once

#include <iostream>
#include "../../SFML/include/SFML/Graphics.hpp"
#include "../../Box2D/Box2D/Box2D.h"


const float	PI = 3.14159265358979323846f;

//Entity Class used for game objects such as ship and asteroid, inherits Convex Shape and Circle Shape provided by SFML

class Entity : public sf::ConvexShape, public sf::CircleShape {

public:
	Entity() {}	
	~Entity() {}



	/********************************/
	/**** Circle Shape functions ****/
	/* Used For Destroyed Asteroids */

	//Set and get the current position of the object
	void setCircPos(sf::Vector2f pos) {
		sf::CircleShape::setPosition(pos);
	}
	void setCircPos(float x, float y) {
		sf::CircleShape::setPosition(x, y);
	}
	sf::Vector2f getCircPos() {
		return sf::CircleShape::getPosition();
	}

	//Set how many points the circle should have
	void setPointCirc(size_t count) {
		sf::CircleShape::setPointCount(count);
	}

	//Get the number of vertices
	size_t getPointCirc() {
		return sf::CircleShape::getPointCount();
	}

	//Set Texture
	void setTextCirc(sf::Texture& p) {
		sf::CircleShape::setTexture(&p);
	}

	//Return pointer to the circle object if one were created
	sf::CircleShape* getShapeCircle() {
		return this;
	}

	/*************************************/
	/****** Convex Shape functions *******/
	/*Used for ship, asteroid and bullet*/

	//Set and get the current position of the object
	void setConvPos(sf::Vector2f pos) {
		sf::ConvexShape::setPosition(pos);
	}
	void setConvPos(float x, float y) {
		sf::ConvexShape::setPosition(x, y);
	}
	sf::Vector2f getConvPos() {
		return sf::ConvexShape::getPosition();
	}

	//Used to set how many vertices the Convex Shape has
	void setPointConv(size_t count) {
		sf::ConvexShape::setPointCount(count);
	}

	//Get the number of vertices
	size_t getPointConv() {
		return sf::ConvexShape::getPointCount();
	}

	//Set Texture of the object
	void setTextConv(sf::Texture& p) {
		sf::ConvexShape::setTexture(&p);
	}

	//Set and get Rotation for the convex shape
	void setRotation(float rot) {
		sf::ConvexShape::setRotation(rot);
	}
	float getRotation() {
		return sf::ConvexShape::getRotation();
	}

	sf::Transform getTransform() {
		return sf::ConvexShape::getTransform();
	}
	sf::Vector2f getPoint(size_t index) {
		return sf::ConvexShape::getPoint(index);
	}

	//Return pointer to the convex shape object if one were created
	sf::ConvexShape* getShape() {
		return this;
	}


	/**************************/
	/**** Entity Functions ****/
	/**************************/
	/* Used for all entities although destroyed asteroids will not use many of these */


	//Pass in array of x, y points, error if the shape's point count hasn't been initialised yet
	void setPoints(sf::Vector2f points[]) {

		if (getPointConv() == 0) {
			std::cout << "Point count hasn't been set" << std::endl;
			return;
		}
		for (size_t i = 0; i < getPointConv(); i++) {
			setPoint(i, points[i]);
		}
	}


	//Is the entity a player? Used for ship, as asteroids aren't player controlled
	bool isPlayer() {
		return playerControlled;
	}

	//Set the velocity vector to 0, used for player controlled entity 
	void SetToZero() {
		setVelocity(0.0f, 0.0f);
	}

	//Set and get the velocity of the entity
	void setVelocity(sf::Vector2f vel) {
		velocity = vel;
	}
	void setVelocity(float x, float y) {
		setVelocity(sf::Vector2f(x, y));
	}
	sf::Vector2f getVelocity() {
		return velocity;
	}

	void setVelocity(sf::Int32 msec, int dir) {

		sf::Vector2f veloc;
		float angle = (sf::ConvexShape::getRotation() - 90) * PI / 180;

		sf::Vector2f direction = sf::Vector2f((float)cos(angle), (float)sin(angle));
		veloc.x = direction.x * getMoveSpeed();
		veloc.y = direction.y * getMoveSpeed();
		veloc.x = veloc.x * (msec * 0.001f);
		veloc.y = veloc.y * (msec * 0.001f);

		//Used really for ship, if going baackwards forwards..
		if (dir == 0) {
			veloc = -veloc;
		}

		velocity = veloc;
	}

	//Set and get the physics body of the entity, used in the b2 physics world.
	void setPhysics(b2Body& b) {
		physics = &b;
	}
	b2Body* getPhysics() {
		return physics;
	}

	//Set and get the move speed of the entity
	float getMoveSpeed() {
		return moveSpeed;
	}
	void setMoveSpeed(float a) {
		moveSpeed = a;
	}

	//Numerical value used for type, 1 == ship, 2 == asteroid, 3 == bullet, 4 == destroyed asteroid
	void setType(int a) {
		type = a;
	}
	int getType() {
		return type;
	}

	//Set and get lives of the entitiy
	void setLives(int live) {
		lives = live;
	}
	int getLives() {
		return lives;
	}


	b2Body * physics;
	
	sf::Texture texture;
	sf::Vector2f velocity;
	
	float moveSpeed;
	
	int lives;
	int type;

	bool playerControlled;
	bool deleted;

	//All physics objects are dynamic but just used to distinguish between moving objects
	bool isDynamic;
};
