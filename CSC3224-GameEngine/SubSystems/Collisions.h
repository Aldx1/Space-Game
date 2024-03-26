#pragma once
#include <iostream>

#include "../../Box2D/Box2D/Dynamics/b2WorldCallbacks.h"
#include "../../CSC3224-GameEngine/Game/Asteroid.h"


/*Collision class used for the b2World contact listener. Tried to extend the contact listener class from box2D to apply to the entities in my game*/

class Collision : public b2ContactListener {

public: 
	Collision() {
		
	}
	~Collision() {

	}

	//These four functions have been inherited from the b2ContactListener Class, Have implemented to work with the game entities
	//They are called when bounding boxes of the shape or body created in world space have either started contact or ending contact.

	virtual void BeginContact(b2Contact * contact);

	virtual void EndContact(b2Contact * contact);

	virtual void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);

	virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);


	//Returns true or false if the points overlap
	bool areReallyTouching(Entity * a, Entity * b);

	//Returns the area of a triangle given three vertices, used to determine if points lay inside the shapes
	float screenAreaOfTri(const sf::Vector2f a, const sf::Vector2f b, const sf::Vector2f c);

	//Check if points between the ship and asteroid actually collide to make the graphics look a bit better on collisions. 
	bool checkPointsCollide(Entity* a, Entity * b);
};