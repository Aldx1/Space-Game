#include "../../CSC3224-GameEngine/SubSystems/Generator.h"

Generator::Generator(MemoryManager<sf::Texture> * texs, b2World * worl, Physics* p) {

	textures = texs;
	world = worl;
	ph = p;

	//Used for game action class
	endGame = false;
	shot = false;
	explode = false;
	
	//Asteroids have 1 life when the game starts, with a movement speed of 6.0f and maximum 15 on screen at one time
	asterLife = 1;
	asterSpeed = 6.0f;
	astersOnScreen = 15;

}

Generator::~Generator() {

}

void Generator::InitGameObjects(std::vector<Entity*> &Entities) {

	//Initialise the ship
	ship = new Ship(400, 300);
	ship->setText((*textures->get(0)));
	ship->lives = 1;
	addBody(Entities, *ship);

	//Create asteroids, bullets and destroyed asteroids on start up of the game
	for (int i = 0; i < 1000; i++) {
		Asteroid* aster = new Asteroid();
		asteroids.push_back(aster);

	}
	for (int i = 0; i < 10000; i++) {
		Bullet* bull = new Bullet();
		bullets.push_back(bull);
	}
	for (int i = 0; i < 1000; i++) {
		DestroyedAsteroid* dAst = new DestroyedAsteroid();
		destroyedAsts.push_back(dAst);
	}

	//Only instantiate the ship physics pointer to begin with, all others will be instantied when added to the entity vector
	ship->physics = ph->PhysicsObject(world, ship);
}


//Generate a random starting position for the asteroid
sf::Vector2f Generator::genAsterPos() {

	//Could assign values in a better way ie get graphics window size
	float min = -50.f;
	float maxX = 850.0f;
	float maxY = 650.0f;

	//Generate random values for start pos
	float x = randomValue(min, maxX);
	float y = randomValue(min, maxY);

	//Create random position that would make asteroid start outside of the screen
	while ((x > 25.0f && x < 775.0f && y < 575.0f && y > 25.0f)) {

		x = randomValue(min, maxX);
		y = randomValue(min, maxY);
	}

	sf::Vector2f pos(x, y);
	return pos;
}

//Generate a random rotation for the asteroid as long as it points towards the screen
float Generator::genAsterRot(sf::Vector2f pos) {

	//Create a target location so asteroids move into the screen area
	float minTargX = 150.0f;
	float maxTargX = 650.0f;
	float minTargY = 112.5f;
	float maxTargY = 487.5f;
	float targetX = randomValue(minTargX, maxTargX);
	float targetY = randomValue(minTargX, maxTargX);

	//Generate angle for between start position and target
	float angle = atan2(pos.y - targetY, pos.x - targetX);
	angle -= 90;
	angle = angle * 180 / PI;

	return angle;
}

void Generator::addAsteroid(std::vector<Entity*> &Entities) {


	/*Remove asteroid from generated asteroid vector
	 and add to list of entities for game*/
	Asteroid* astero = asteroids.back();
	asteroids.pop_back();

	//Set asteroids position and rotation to be random values
	astero->setPos(genAsterPos());
	astero->setRotation(genAsterRot(astero->getPos()));
	astero->setText((*textures->get(1)));
	astero->setLives(asterLife);
	astero->setMoveSpeed(asterSpeed);

	//Create asteroids physics body and then add to entities vector
	astero->physics = ph->PhysicsObject(world, astero);
	Entities.push_back(astero);
}

//Add a destroyed asteroid with the coordinates of the asteroid that had been destroyed
void Generator::addDestroyedAsteroid(std::vector<Entity*> &Entities, float x, float y) {

	/*Remove destroyed asteroid from generated vector and add to the entity vector*/
	DestroyedAsteroid* destro = destroyedAsts.back();
	destroyedAsts.pop_back();

	destro->setPos(x, y);
	destro->setText((*textures->get(3)));
	destro->setDestroyed();

	//Create physics object but with different function to one used for other entities, Destroyed asteroid is a circle not convex shape.
	destro->physics = ph->explodedBody(world, destro);
	Entities.push_back(destro);
}


void Generator::addBullet(std::vector<Entity*> &Entities) {

		//Get bullet from back of bullets vector
		Bullet* bull = bullets.back();
		bullets.pop_back();

		//Set bullet positon and rotation according to ship
		bull->setPos(ship->getTurretPos());
		bull->setRotation(ship->getRotation());

		//Reset the bullets clock and create physics body 
		bull->setClock();
		bull->physics = ph->PhysicsObject(world, bull);

		//Push bullet into entities vector and play sound for shooting
		Entities.push_back(bull);
}

//Delete the bodies from the physics world if they have been marked for deletion or have no lives left
void Generator::deleteBodies(b2World* world, std::vector<Entity*>& Entities) {

	shot = false;
	endGame = false;
	explode = false;

	//Loop through physics world bodies and remove if marked for deletion
	for (b2Body* tmp = world->GetBodyList(); tmp; tmp = tmp->GetNext()) {

		b2Body* champ = tmp->GetNext();

		//If body is linked to an entity
		if (champ != nullptr) {
			Entity* en = (Entity *)champ->GetUserData();
	
			//Check to see if entity is player and still has a life left
			if (en->isPlayer()) {

				//If no lives left then delete and set end game as true
				if (en->lives <= 0) {
					world->DestroyBody(champ);
					champ->SetUserData(nullptr);
					champ = nullptr;

					//Set end game as true and break out of the loop
					endGame = true;
					break;
				}
			}

			//If entity is asteroid
			if (en->getType() == 2) {
				Asteroid* a = (Asteroid*)en;

				//If asteroid has been shot then set shot as true for the action class to react
				if (a->shot) {
					shot = true;
					a->shot = false;

					//If the asteroid has no lives left
					if (a->getLives() <= 0) {

						//Set explode as true for the action class to react
						explode = true;
						
						//Add destroyed asteroid to the entity vector given the coordinates of the asteroid
						addDestroyedAsteroid(Entities, a->getMiddle().x, a->getMiddle().y);
						
						//Mark asteroid as deleted and set the physics to a null pointer and remove from physics world
						en->deleted = true;
						world->DestroyBody(champ);
						champ->SetUserData(nullptr);
						champ = nullptr;
					}
					continue;
				}
			}

			//If entity is marked as deleted then remove from physics world and set physics pointer to null
			if (en->deleted) {
				world->DestroyBody(champ);
				champ->SetUserData(nullptr);
				champ = nullptr;
				continue;
			}

			//If entity is outside of the screen space then mark as deleted and remove from physics world
			if (en->getConvPos().x > 900 || en->getConvPos().x < -100
				|| en->getConvPos().y < -100 || en->getConvPos().y > 700) {

				en->deleted = true;
				world->DestroyBody(champ);
				champ->SetUserData(nullptr);
				champ = nullptr;
				continue;
			}
		}	
	}
}


//Remove the entities that have been marked as deleted or have lived their life
void Generator::RemoveEntitites(std::vector<Entity*>& Entities) {

	//If endgame is true from delete bodies function then return from function
	if (endGame) {
		return;
	}

	//Loop through entity vector and mark for deletion and erase
	for (unsigned int i = 0; i < Entities.size(); i++) {

		//If entity is a destroyed asteroid
		if (Entities.at(i)->getType() == 4) {
			DestroyedAsteroid* des = (DestroyedAsteroid*)Entities.at(i);

			//If the destroyed asteroid has lived its life or reached maximum radius
			if (des->getTime() > DESASTlife || des->getRadius() >= des->max_RADIUS) {
				Entities.at(i)->deleted = true;
			}
		}

		//If entity is a bullet
		if (Entities.at(i)->getType() == 3) {
			Bullet* b = (Bullet *)Entities.at(i);

			//If bullet has lived its life, mark for deletion
			if (b->getTime() >= bulletLife) {
				Entities.at(i)->deleted = true;
			}
		}

		//Remove any entities from the vector
		if (Entities.at(i)->deleted) {
			Entities.erase(Entities.begin() + i);
		}
	}
}


void Generator::updateGameEnts(std::vector<Entity*> &Entities) {

	//If endgame is true from delete bodies function then return from function
	if (endGame) {
		return;
	}

	//If bullets, asteroids or destroyed asteroid vector is low then add more..
	//Decided to check if one was low then update all to have fewer interferences as possible with the gameplay
	if (!bulletsRemain() || !AstersRemain() || !DestroyedAstersRemain()) {
		addMoreBulls();
		addMoreAsteroids();
		addMoreDestroyed();
	}

	//If sufficient amount of asteroids remain in asteroid vector 
	//Check to see how many asteroids are within entities vector and act accordingly
	if (AstersRemain()) {
		addAsterstoEnts(Entities);
	}
}

