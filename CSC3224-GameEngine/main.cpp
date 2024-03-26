#ifdef _DEBUG
#pragma comment(lib, "../Debug/Box2D.lib")		
#else 
#pragma comment(lib, "../Release/Box2D.lib")	
#endif

#include "../CSC3224-GameEngine/Game/GameActions.h"
#include "../CSC3224-GameEngine/Game/GameCreator.h"
#include "../CSC3224-GameEngine/Game/GameScene.h"
#include "../CSC3224-GameEngine/Game/Game.h"


int main() {

	//Background url
	//www.google.co.uk/url?sa=i&rct=j&q=&esrc=s&source=images&cd=&cad=rja&uact=8&ved=2ahUKEwjvpoeT77zaAhUDVhQKHeOwDO0QjRx6BAgAEAU&url=https%3A%2F%2Fwww.youtube.com%2Fwatch%3Fv%3DEZ7la-hMNuk&psig=AOvVaw1vR8TwbyDG8zUx5tG7Zt-S&ust=1523901903858335
	
	//Sounds aquired from http:/freesound.org/
	

	//Used to randomise the asteroid starting positions and target positions
	srand((unsigned int)(time(NULL)));

	//Start up the game
	GameCreator* gc = new GameCreator();
	if (!gc->Init()) {
		std::cout << "GameCreator has had issues" << std::endl;
	}

	//Create the scene and actions for the game
	GameScene* t = gc->createScene();
	GameActions* l = gc->createActions(t->getGen(), t->getSound(), t);
	

	//Launch the game given everything else has initialised. 
	Game* game = new Game(t,l);
	game->run();
		
	delete gc;
	delete game;
}