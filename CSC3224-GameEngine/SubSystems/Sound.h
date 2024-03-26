#pragma once

#include <SFML\Audio.hpp>

#include "../../CSC3224-GameEngine/SubSystems/MemoryManager.h"
#include "../../CSC3224-GameEngine/SubSystems/FileLoader.h"

class Sound {
public:
	Sound();
	~Sound();


	bool Init();
	MemoryManager<sf::SoundBuffer> * getSBuffers() ;

	sf::SoundBuffer* getSBUFF(int id);


	void playSound(unsigned int id);


	std::vector<sf::Sound>& getSounds() {
		return sounds;
	}

	void addSound(sf::Sound s) {
		sounds.push_back(s);
	}
	
private:

	std::vector<sf::Sound> sounds;	
	MemoryManager<sf::SoundBuffer> * soundBuffers;
};