#include "../../CSC3224-GameEngine/SubSystems/FileLoader.h"



FileLoader::FileLoader() {

}

FileLoader::~FileLoader() {

}

bool FileLoader::loadTextures(MemoryManager<sf::Texture>* textures, std::string filePath) {

	//Include the text document to read the textures
	std::ifstream f(filePath + "TextureIncludes.txt");
	std::string line;

	if (!f) {
		return false;
	}

	//While the input has a line to read, add it to the appropriate location
	while (getline(f, line)) {

		//Return false if one of the files included in the text document isn't able to load
		sf::Texture* tempText = textures->create();
		if (!tempText->loadFromFile(filePath + "/" + line)) {
			std::cout << "Error loading texture from :" << filePath << " " << line << std::endl;
			return false;
		}
	}

	f.close();
	
	//return true if all textures have been loaded
	return true;
}


bool FileLoader::loadSounds(MemoryManager<sf::SoundBuffer>* sounds, std::string filePath) {

	std::ifstream f(filePath + "AudioIncludes.txt");
	std::string line;

	if (!f) {
		return false;
	}

	while (getline(f, line)) {

		//Return false if one of the files included in the text document isn't able to load
		sf::SoundBuffer* tempSoundBuff = sounds->create();
		if (!tempSoundBuff->loadFromFile(filePath + "/" + line)) {
			std::cout << "Error loading sound from :" << filePath << " " << line << std::endl;
			return false;
		}
	}

	f.close();

	//return true if all sounds have been loaded
	return true;
}

bool FileLoader::loadFonts(MemoryManager<sf::Font>* fonts, std::string filePath) {

	std::ifstream f(filePath + "FontIncludes.txt");
	std::string line;

	if (!f) {
		return false;
	}

	while (getline(f, line)) {

		//Return false if one of the files included in the text document isn't able to load.. There is only one inside the text document
		sf::Font* tempSoundBuff = fonts->create();
		if (!tempSoundBuff->loadFromFile(filePath + "/" + line)) {
			std::cout << "Error loading font from :" << filePath << " " << line << std::endl;
			return false;
		}
	}

	f.close();

	//return true if the font has been loaded
	return true;
}


//File loader used for highscores, break names and numbers into list to determine where to insert 
bool FileLoader::loadFile(std::string filePath) {

	std::ifstream f(filePath + "Highscores.txt");
	std::string line;

	if (!f) {
		std::cout << "Unable to open highscore file.." << std::endl;
		return false;
	}

	
	while (getline(f, line)) {
		size_t pos = line.find(":");
		names.push_back(line);

		//Split into a substring after the colon to store in the score vector
		if (pos != std::string::npos) {
			std::stringstream stream(line.substr(pos + 1));
			int n;

			stream >> n;

			Iscores.push_back(n);
		}
	}
		
	f.close();
	
	return true;
}

std::vector<int> FileLoader::getScores() {

	return Iscores;
}

//Update the highscore file
bool FileLoader::updateScores(std::string filePath, std::vector<std::string> scores) {

	std::ofstream of(filePath + "Highscores.txt");
	if (!of) {
		std::cout << "Unable to find output file.. " << std::endl;
		return false;
	}

	if (of) {
		for (unsigned int i = 0; i < scores.size(); i++) {
			of << scores.at(i) << std::endl;
		}
	}

	of.close();
	return true;
}

