#include "../../CSC3224-GameEngine/SubSystems/Sound.h"

Sound::Sound() {

}

Sound::~Sound() {


}

bool Sound::Init() {
	soundBuffers = new MemoryManager<sf::SoundBuffer>(10);


	if (!FileLoader::loadSounds(soundBuffers, "../Assets/Audio/")) {
		std::cout << "Error Loading Sound Buffers" << std::endl;
		return false;
	}
	else {
		return true;
	}
}

sf::SoundBuffer* Sound::getSBUFF(int id) {

	return soundBuffers->get(id);
}

MemoryManager<sf::SoundBuffer> * Sound::getSBuffers() {

	return soundBuffers;
}

void Sound::playSound(unsigned int id ) {

	sounds.at(id).play();
}
