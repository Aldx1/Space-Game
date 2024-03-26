#pragma once

#include "../../CSC3224-GameEngine/SubSystems/Sound.h"
#include "../../CSC3224-GameEngine/SubSystems/MemoryManager.h"
#include <SFML\Graphics.hpp>
#include <fstream>
#include <iostream>
#include <sstream>

/*File Loader Class to read in files and return true or false depending on errors*/

class FileLoader {
public:

	FileLoader();
	~FileLoader();

	//Load in textures, sounds, and fonts..
	static bool loadTextures(MemoryManager<sf::Texture>* textures, std::string filePath);
	static bool loadSounds(MemoryManager<sf::SoundBuffer>* sounds, std::string filePath);
	static bool loadFonts(MemoryManager<sf::Font>* fonts, std::string filePath);
	bool loadFile(std::string filePath);

	bool updateScores(std::string filePath, std::vector<std::string>);

	std::vector<int>  getScores();

	std::vector<std::string> getNames() {
		return names;
	}

	std::vector<int> Iscores;
	std::vector<std::string> names;
	
		
};