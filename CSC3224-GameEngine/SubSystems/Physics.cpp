#include "../../CSC3224-GameEngine/SubSystems/Physics.h"


const float scale = 60.0f;

Physics::Physics() {
	isInit = false;
}

Physics::~Physics() {
	
}

b2World * Physics::InitWorld() {

	//Create new collision and apply that to the box2d world
	coll = new Collision();

	//Gravity is set as 0,0
	b2Vec2 gravity = b2Vec2(0, 0);
	b2World* world = new b2World(gravity);
	world->SetContactListener(coll);

	if (world) {
		isInit = true;
	}

	return world;
}


//This function creates a new body for the worl, Only for use by the destroyed entity..
b2Body* Physics::explodedBody(b2World* world, Entity* ent) {

	//Create a body definition from box2D
	b2BodyDef bodydef;

	bodydef.type = b2_dynamicBody;

	//Set the user data of the body to be that of the entity 
	bodydef.userData = ent;

	//Create the body given the body def defined above
	b2Body* body = world->CreateBody(&bodydef);
	//body->SetSleepingAllowed(false);

	b2CircleShape circle;

	circle.m_p.Set((ent->getCircPos().x + 14.0f ) / scale , (ent->getCircPos().y + 13.0f)/ scale );
	circle.m_radius = ent->getRadius() / scale;

	//Create the box2d fixture definition and assign the polygon shape defined above to it
	b2FixtureDef fixture;

	fixture.shape = &circle;
	fixture.density = 1.0f;
	body->CreateFixture(&fixture);

	return body;
}



b2Body* Physics::PhysicsObject(b2World * world, Entity* ent) {

	//Create a body definition from box2D
	b2BodyDef bodydef;	

	//All bodies in this game are dynamic
	bodydef.type = b2_dynamicBody;

	//Set the user data of the body to be that of the entity 
	bodydef.userData = ent;

	 //Create the body given the body def defined above
	b2Body* body = world->CreateBody(&bodydef);

	//Set transform (position and angle) for the entity/body 
	float angle = (ent->getRotation() - 90) * PI / 180;
	body->SetTransform(b2Vec2(ent->getConvPos().x / scale, ent->getConvPos().y / scale), angle);

	if (!ent->isPlayer()) {
		body->SetFixedRotation(true);
	}
	
	
	//Create a box2d polygon shape
	b2PolygonShape polyGon;
	
	//If entity is player just create triangle shape from first three vertices
	size_t pointCount = ent->getPointConv();
	if (ent->isPlayer()) {
		pointCount = 3;
	}

	//Apply the vertices from the shape defined for the SFML shape to the shape in the physics worlds
	int intCount = static_cast<int>(pointCount);
	b2Vec2* vec = new b2Vec2[intCount];
	int p = 0;
	for (int i = intCount - 1; i >= 0; i--) {
		vec[p] = b2Vec2(ent->getPoint(i).x / scale, ent->getPoint(i).y / scale);
		p++;
	}
	
	polyGon.Set(vec, intCount);
	delete[] vec;
	
	//Create the box2d fixture definition and assign the polygon shape defined above to it
	b2FixtureDef fixture;	

	fixture.shape = &polyGon;
	fixture.density = 1.0f;
	body->CreateFixture(&fixture);

	//return the created body to attach to the entity physics pointer
	return body;
}


void Physics::updatePhysicsWorld(b2World * world,std::vector<Entity *>ents) {

	//Iterate through b2world bodies
	for (b2Body* tmp = world->GetBodyList(); tmp; tmp = tmp->GetNext()){
		Entity * en = (Entity*)tmp->GetUserData();

		if (en->isDynamic) {
			
			//Update Bodies velocity if entity is not deleted
			if (!en->deleted) {
				tmp->SetLinearVelocity(b2Vec2(en->getVelocity().x / scale, en->getVelocity().y / scale/* * M2P */));
				
				
				
			}
			//If is player then set to 0, other objects keep moving
			if (en->isPlayer()) {

				//Check to see if player is within bounds of the screen
				tmp->SetTransform(b2Vec2(tmp->GetPosition().x, tmp->GetPosition().y), en->getRotation());
				if (tmp->GetPosition().x < 0 || tmp->GetPosition().y < 0 || tmp->GetPosition().x > 800 || tmp->GetPosition().y > 600) {
					PlayerWithinBounds(tmp);
				}
				en->SetToZero();
			}
		}

		else {

			//tmp->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
			b2Fixture* f = tmp->GetFixtureList();
			b2CircleShape* circ = (b2CircleShape*) f->GetShape();
			circ->m_radius = en->getRadius() / scale;
		}
	}

	//World step 8 milliseconds -- around 120 times a second, 1 velocity iteration and 1 position iteration
	world->Step(8, 1, 1);

	b2Body* bod;
	
	//Iterate through entities and update position based on steps taken in loop above
	for (std::vector<Entity*>::iterator i = ents.begin(); i != ents.end(); i++) {
		bod = (*i)->getPhysics();
		if (bod != nullptr) {
			Entity* en = (Entity*)(*i);
			if (en->isDynamic) {
				en->setConvPos(bod->GetPosition().x * scale, bod->GetPosition().y * scale);
			}

			//Only update the radius of the destroyed asteroid, not its positon unlike the other
			else {
				DestroyedAsteroid* destro = (DestroyedAsteroid*)en;
				destro->updateRadius();
			}
		}
	}
}


void Physics::setVelocities(std::vector<Entity*> &Entities, sf::Int32 msec) {

	//Loop through entities and assign velocity to them as long as it is not the player
	for (unsigned int i = 0; i < Entities.size(); i++) {
		if (Entities.at(i)->isDynamic && !Entities.at(i)->isPlayer()) {
			Entity* den = (Entity*)Entities.at(i);
			den->setVelocity(msec, 1);
		}
	}
}


//If player moves outside of the screen then mirror and appear at the other side
void Physics::PlayerWithinBounds(b2Body* bod) {
	
		if ((bod->GetPosition().x * scale < 0) && (bod->GetPosition().y * scale < 600 && bod->GetPosition().y * scale > 0)) {
			Entity* ent = (Entity*)bod->GetUserData();
			bod->SetTransform(b2Vec2(800 / scale, bod->GetPosition().y), ent->getRotation());
		}
		if ((bod->GetPosition().x * scale > 800) && (bod->GetPosition().y * scale < 600 && bod->GetPosition().y * scale > 0)) {
			Entity* ent = (Entity*)bod->GetUserData();
			bod->SetTransform(b2Vec2(0 / scale, bod->GetPosition().y), ent->getRotation());
		}

		if ((bod->GetPosition().y * scale < 0) && (bod->GetPosition().x * scale < 800 && bod->GetPosition().x * scale > 0)) {
			Entity* ent = (Entity*)bod->GetUserData();
			bod->SetTransform(b2Vec2(bod->GetPosition().x, 600 / scale), ent->getRotation());
		}
		if ((bod->GetPosition().y * scale > 600) && (bod->GetPosition().x * scale < 800 && bod->GetPosition().x * scale > 0)) {
			Entity* ent = (Entity*)bod->GetUserData();
			bod->SetTransform(b2Vec2(bod->GetPosition().x, 0 / scale), ent->getRotation());
		}
}
