#include "../../CSC3224-GameEngine/SubSystems/RendWindow.h"


RendWindow::RendWindow(sf::Uint16 height, sf::Uint16 width, sf::String name) :
	sHeight(height), sWidth(width), sName(name) {

	initialise();

}

RendWindow::~RendWindow() {

}

bool RendWindow::Init() {

	return rendWind.isOpen();
}


void RendWindow::initialise()  {

		rendWind.create(sf::VideoMode(sHeight, sWidth), sName);

		//Not sure if i need to do this, limits the fram rate to 60 frames a second.. 
		rendWind.setFramerateLimit(60);
}


void RendWindow::draw(sf::ConvexShape l) {

	rendWind.draw(l);
}

void RendWindow::draw(sf::CircleShape l) {

	rendWind.draw(l);
}

void RendWindow::draw(sf::Sprite l) {

	rendWind.draw(l);
}

void RendWindow::draw(sf::Text l) {

	rendWind.draw(l);
}

void RendWindow::clear() {

	rendWind.clear();

}

void RendWindow::display() {

	rendWind.display();
}
