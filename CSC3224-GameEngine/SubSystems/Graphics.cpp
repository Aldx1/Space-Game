#include "../../CSC3224-GameEngine/SubSystems/Graphics.h"



Graphics::Graphics(int width, int height) : window(width, height, "Game") {

}

Graphics::~Graphics() {

}


void Graphics::drawScene(sf::Text text, std::vector<Entity*> ents) {

	//Clear the render window from the last frame.
	window.clear();

	//Draw the background first 
	window.draw(back);

	//Then draw the list or vector of entities
	for (std::vector<Entity*>::iterator i = ents.begin(); i != ents.end(); i++) {
		if (!(*i)->deleted) {

			//If the entity is dynamic then get convex shape
			if ((*i)->isDynamic) {
				sf::ConvexShape* shap = (*i)->getShape();
				window.draw(*shap);
			}

			//Else its destroyed asteroid so get circle shape
			else {
				sf::CircleShape* shap = (*i)->getShapeCircle();
				window.draw(*shap);
			}
		}
	}

	//Then draw the score on top, in the left corner
	window.draw(text);
}

bool Graphics::isInit() {
	return window.Init();
}

void Graphics::display() {
	window.display();
}