#include "../../CSC3224-GameEngine/SubSystems/Collisions.h"


void Collision::BeginContact(b2Contact * contact) {

	Entity* entityA = static_cast<Entity *>(contact->GetFixtureA()->GetBody()->GetUserData());
	Entity* entityB = static_cast<Entity *>(contact->GetFixtureB()->GetBody()->GetUserData());

	//If objects are asteroids ignore collision
	if (entityA->getType() == 2 && entityB->getType() == 2) {
		contact->SetEnabled(false);
	}


	//If coliision happens between destroyed asteroid and ship then remove life from ship - End Game
	if ((entityA->getType() == 4 || entityB->getType() == 4) && (entityA->getType() == 1 || entityB->getType() == 1)) {
		entityA->getType() == 1 ? entityA->lives = 0 : entityB->lives = 0;
	}

	//Highly unlikely occurence but ignore collisions between two bullets
	if (entityA->getType() == 3 && entityB->getType() == 3) {
		contact->SetEnabled(false);
	}

	//If objects colliding are asteroid or ship. Tried to make it more accurate by ignoring the start of contact between 
	if ((entityA->getType() == 1 || entityB->getType() == 1) && (entityA->getType() == 2 || entityB->getType() == 2)) {

		//Tried to make the collision more accurate by testing whether the points of the asteroid or ship lie within one another
		if (areReallyTouching(entityA, entityB)) {
			entityA->getType() == 1 ? entityA->lives = 0 : entityB->lives = 0;
		}
	}

	//If bullet collides with asteroid mark both for deletion and update score
	if ((entityA->getType() == 2 || entityB->getType() == 2) && (entityA->getType() == 3 || entityB->getType() == 3)) {


		//Mark asteroid as shot so that the explode noise can be played 
		Asteroid*as;
		entityA->getType() == 2 ? as = (Asteroid*)entityA : as = (Asteroid*)entityB;
		as->shot = true;
		as->setLives(as->getLives() - 1);

		//Mark the other contact collision (bullet) as deleted
		Entity* ent;
		entityA->getType() == 3 ? ent = (Entity*)entityA : ent = (Entity*)entityB;
		ent->deleted = true;
	}
}


void Collision::EndContact(b2Contact * contact) {

	Entity* entityA = static_cast<Entity *>(contact->GetFixtureA()->GetBody()->GetUserData());
	Entity* entityB = static_cast<Entity *>(contact->GetFixtureB()->GetBody()->GetUserData());

	//Ignore any collisions that involve a destroyed asteroid
	if ((entityA->getType() == 4 || entityB->getType() == 4)) {
		contact->SetEnabled(false);
	}

	//If objects are asteroids ignore collision
	if (entityA->getType() == 2 && entityB->getType() == 2) {
		contact->SetEnabled(false);
	}

	//Highly unlikely occurence but ignore collisions between two bullets
	if (entityA->getType() == 3 && entityB->getType() == 3) {
		contact->SetEnabled(false);
	}

}

void Collision::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) {
	Entity* entityA = static_cast<Entity *>(contact->GetFixtureA()->GetBody()->GetUserData());
	Entity* entityB = static_cast<Entity *>(contact->GetFixtureB()->GetBody()->GetUserData());

	//Ignore any collisions that involve a destroyed asteroid
	if ((entityA->getType() == 4 || entityB->getType() == 4)) {
		contact->SetEnabled(false);
	}

	//If objects are asteroids ignore collision
	if (entityA->getType() == 2 && entityB->getType() == 2) {
		contact->SetEnabled(false);
	}

	//Highly unlikely occurence but ignore collisions between two bullets
	if (entityA->getType() == 3 && entityB->getType() == 3) {
		contact->SetEnabled(false);
	}

}
void Collision::PreSolve(b2Contact* contact, const b2Manifold* oldManifold) {

	Entity* entityA = static_cast<Entity *>(contact->GetFixtureA()->GetBody()->GetUserData());
	Entity* entityB = static_cast<Entity *>(contact->GetFixtureB()->GetBody()->GetUserData());

	
	//Ignore any collisions that involve a destroyed asteroid
	if ((entityA->getType() == 4 || entityB->getType() == 4)) {
		contact->SetEnabled(false);
	}

	//If objects are asteroids ignore collision
	if (entityA->getType() == 2 && entityB->getType() == 2) {
		contact->SetEnabled(false);
	}
	
	//Highly unlikely occurence but ignore collisions between two bullets
	if (entityA->getType() == 3 && entityB->getType() == 3) {
		contact->SetEnabled(false);
	}

	//If objects colliding are asteroid or ship. Tried to make it more accurate by ignoring the start of contact between 
	if ((entityA->getType() == 1 || entityB->getType() == 1) && (entityA->getType() == 2 || entityB->getType() == 2)) {
		contact->SetEnabled(false);
	}

}


bool Collision::areReallyTouching(Entity * a, Entity * b) {

	//If points collide then return true
	return checkPointsCollide(a, b);

}


float Collision::screenAreaOfTri(const sf::Vector2f a, const sf::Vector2f b, const sf::Vector2f c) {

	float area = abs((a.x * b.y) + (b.x* c.y) + (c.x*a.y)) - ((b.x*a.y) + (c.x * b.y) + (a.x*c.y));
	return area * 0.5f;
}


//Function at trying to make collisions more accurate for graphics, Maybe a bit long winded...
bool Collision::checkPointsCollide(Entity* a, Entity * b) {

	Entity* triangle = a->getType() == 1 ? a : b;
	Entity* box = a->getType() == 2 ? a : b;

	//Get all transform points of the asteroids and ship i.e. vertices
	sf::Vector2f box1 = box->getTransform().transformPoint(box->getPoint(0));
	sf::Vector2f box2 = box->getTransform().transformPoint(box->getPoint(1));
	sf::Vector2f box3 = box->getTransform().transformPoint(box->getPoint(2));
	sf::Vector2f box4 = box->getTransform().transformPoint(box->getPoint(3));

	sf::Vector2f Tri1 = triangle->getTransform().transformPoint(triangle->getPoint(0));
	sf::Vector2f Tri2 = triangle->getTransform().transformPoint(triangle->getPoint(1));
	sf::Vector2f Tri3 = triangle->getTransform().transformPoint(triangle->getPoint(2));

	bool isColliding;

	//Calculate the tri area to be used for comparisons
	float TriArea = screenAreaOfTri(Tri1, Tri2, Tri3);
	float TBoxArea1, TBoxArea2, TBoxArea3;

	TBoxArea1 = screenAreaOfTri(Tri1, Tri2, box1);
	TBoxArea2 = screenAreaOfTri(Tri2, Tri3, box1);
	TBoxArea3 = screenAreaOfTri(Tri3, Tri1, box1);

	//Test for box vertex 1..
	//If all triangle areas from box (or asteroid) coordinates are equal to that of the ship, then asteroid vertex lays inside ship
	if ((TBoxArea1 + TBoxArea2 + TBoxArea3) == TriArea) {
		//std::cout << " Collide Box 1 " << std::endl;
		return true;
	}
	else {
		isColliding = false;
	}
	
	//Have to test all 4 corners of the box...
	TBoxArea1 = screenAreaOfTri(Tri1, Tri2, box2);
	TBoxArea2 = screenAreaOfTri(Tri2, Tri3, box2);
	TBoxArea3 = screenAreaOfTri(Tri3, Tri1, box2);

	if ((TBoxArea1 + TBoxArea2 + TBoxArea3) == TriArea) {
		//std::cout << " Collide Box 2 " << std::endl;
		return true;
	}
	else {
		isColliding = false;
	}

	//Could have maybe implemented this a bit better to test the asteroids corners...
	TBoxArea1 = screenAreaOfTri(Tri1, Tri2, box3);
	TBoxArea2 = screenAreaOfTri(Tri2, Tri3, box3);
	TBoxArea3 = screenAreaOfTri(Tri3, Tri1, box3);

	if ((TBoxArea1 + TBoxArea2 + TBoxArea3) == TriArea) {
		//std::cout << " Collide Box 3 " << std::endl;
		return true;
	}
	else {
		isColliding = false;
	}

	//But my brain is fried and I am tired.. 
	TBoxArea1 = screenAreaOfTri(Tri1, Tri2, box4);
	TBoxArea2 = screenAreaOfTri(Tri2, Tri3, box4);
	TBoxArea3 = screenAreaOfTri(Tri3, Tri1, box4);

	if ((TBoxArea1 + TBoxArea2 + TBoxArea3) == TriArea) {
		//std::cout << " Collide Box 4 " << std::endl;
		return true;
	}
	else {
		isColliding = false;
	}
	

	//Box is 20 x 20 so area is 400..!? Maybe for some reason it isn't this 
	float boxArea = 400;
	float TBoxArea4;

	//Test All vertices of the triangle (ship)
	TBoxArea1 = screenAreaOfTri(box1, box2, Tri1);
	TBoxArea2 = screenAreaOfTri(box2, box3, Tri1);
	TBoxArea3 = screenAreaOfTri(box3, box4, Tri1);
	TBoxArea4 = screenAreaOfTri(box4, box1, Tri1);


	//Test For vertex 1 of triangle
	if ((TBoxArea1 + TBoxArea2 + TBoxArea3 + TBoxArea4) == boxArea) {
		//std::cout << " Collide Tri 1" << std::endl;
		return true;
	}
	else {
		isColliding = false;
	}

	//Test for the second vertex
	TBoxArea1 = screenAreaOfTri(box1, box2, Tri2);
	TBoxArea2 = screenAreaOfTri(box2, box3, Tri2);
	TBoxArea3 = screenAreaOfTri(box3, box4, Tri2);
	TBoxArea4 = screenAreaOfTri(box4, box1, Tri2);

	if ((TBoxArea1 + TBoxArea2 + TBoxArea3 + TBoxArea4) == boxArea) {
		//std::cout << " Collide Tri 2" << std::endl;
		return true;
	}
	else {
		isColliding = false;
	}


	//Test for the third and final :D
	TBoxArea1 = screenAreaOfTri(box1, box2, Tri3);
	TBoxArea2 = screenAreaOfTri(box2, box3, Tri3);
	TBoxArea3 = screenAreaOfTri(box3, box4, Tri3);
	TBoxArea4 = screenAreaOfTri(box4, box1, Tri3);

	if ((TBoxArea1 + TBoxArea2 + TBoxArea3 + TBoxArea4) == boxArea) {
		//std::cout << " Collide Tri 3" << std::endl;
		return true;
	}
	else {
		isColliding = false;
	}

	return isColliding;
}