#pragma once

#include "../../CSC3224-GameEngine/Game/DestroyedAsteroid.h"
#include "../../CSC3224-GameEngine/Game/Entity.h"
#include "../../Box2D/Box2D/Dynamics/b2World.h"
#include "../../Box2D/Box2D/Box2D.h"
#include "../../Box2D/Box2D/Dynamics/b2Body.h"
#include "../../Box2D/Box2D/Collision/Shapes/b2PolygonShape.h"
#include "../../Box2D/Box2D/Collision/b2Collision.h"
#include "../../CSC3224-GameEngine/SubSystems/Collisions.h"

/*Physics Class used to instantiate the Box2d b2world and update world bodies accordingly */

class Physics {

public:
	Physics();

	~Physics();

	//Initialise a physics object given a destroyed asteroid entity
	b2Body* explodedBody(b2World* world, Entity* ent);

	//Initialise and return the b2World
	b2World* InitWorld();

	//Initialise the physics object given the entity and return the body
	b2Body* PhysicsObject(b2World* world, Entity* ent);

	//Update all bodies in the physics world and apply updates to entity positions
	void updatePhysicsWorld(b2World * world, std::vector<Entity *> ents);

	void setVelocities(std::vector<Entity*> &Entities, sf::Int32 msec);

	void PlayerWithinBounds(b2Body* bod);

	//Has physics initialised.. Not sure this is in use anymore
	bool hasInit() {
		return isInit;
	}
	
private:
	bool isInit;
	Collision* coll;
};