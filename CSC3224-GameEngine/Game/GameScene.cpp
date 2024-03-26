#include "../../CSC3224-GameEngine/Game/GameScene.h"

GameScene::GameScene(Physics* ph, Graphics* gr, Sound* so) {
	p = ph;
	g = gr;
	s = so;
	
	score = 0;

	nameEntered = false;
}

GameScene::~GameScene() {
	delete world;
	delete gen;
}


bool GameScene::Init() {

	//Total time of the game, and time of last bullet
	totaltime = 0;
		
	//Create the textures and 1 font used
	textures = new MemoryManager<sf::Texture>(5);
	fonts = new MemoryManager<sf::Font>(5);
	

	//Load fonts, textures returns false if error loading
	if (!FileLoader::loadFonts(fonts, "../Assets/Fonts/")) {
		std::cout << "Error Loading Fonts" << std::endl;
		return false;
	}

	if (!FileLoader::loadTextures(textures, "../Assets/Textures/")) {
		std::cout << "Error Loading Textures" << std::endl;
		return false;
	}

	//Initialise the b2world, return false if error or world is null pointer
	world = p->InitWorld();
	if (!world) {
		std::cout << "Error Physics world isn't there :O" << std::endl;
		return false;
	}

	//Initialise sounds
	InitSounds();

	gen = new Generator(textures, world, p);
	gen->InitGameObjects(Entities);

	//Initialise objects
	InitObjects();

	return true;
}

void GameScene::InitObjects() {

	//Create the background sprite
	sf::Sprite back((*textures->get(2)), sf::IntRect(0, 0, 800, 600));
	g->addBack(back);

	//Set the score text properties
	text.setFont((*fonts->get(0)));
	text.setCharacterSize(25);
	text.setFillColor(sf::Color::Red);
	text.setStyle(sf::Text::Bold);
	
}

//Attach sound buffers to sound
void GameScene::InitSounds() {

	for (unsigned int i = 0; i < 5; i++) {
		sf::Sound soun = sf::Sound((*s->getSBUFF(i)));
		s->addSound(soun);
	}
}


//Alot of the game loop functionality is within this function
void GameScene::update(sf::Int32 ms) {
		
	totaltime += ms;
	msec = ms;

	//Update velocities and physics world
	p->setVelocities(Entities, ms);	
	p->updatePhysicsWorld(world, Entities);

	drawScene();

	//Delete bodies from world and remove entities from vector
	gen->updateGameWorld(world, Entities);
	
}

void GameScene::drawScene() {

	//Pass score and entities to graphics to draw accordingly
	std::string scor = std::to_string(score);
	std::string disp = "Score: " + scor;
	text.setString(disp);
	g->drawScene(text, Entities);
}

void GameScene::closeWindow() {

	g->window.rendWind.close();
}
