#include "TextureManager.hpp"

TextureManager* TextureManager::instance = nullptr; // was getting an external error

TextureManager*& TextureManager::getInstance() // a static function means that the function is independant of a class's instance (can be called without initializing a class)
{
	if (!instance)
	{
		instance = new TextureManager;
	}
	return instance;
}

void TextureManager::loadTextures(string fileName /* 'file' should be a txt file which contains the file directories to other files that contain sprites */)
{
	ifstream file(fileName);
	char cLine[100] = { '\0' }; // each line should not exeed 100 characters
	int index = 0;
	string line, newKey, newTexturePath;
	sf::Texture newTexture;
	while (file.getline(cLine, 100))
	{
		line = cLine; // change the obtained line into a cpp string because we can use more functions
		if (line[0] != '#' && line[0] != '\0') // hardcodded ignore value (Any line that starts with # will be ignored)
		{
			index = line.find('-'); // textures should be differntiated by 'name-filePath' | I am not putting this in a Try-Catch because the user should not be inputting, we should
			newKey = line.substr(0, index);
			newTexturePath = line.substr((index + 1), line.length());
			newTexture.loadFromFile(newTexturePath);
			textureMap.insert({ newKey, newTexture });
			std::cout << "Line: " << line << " loaded correctly!" << std::endl;
		}
	}
}

sf::Texture& TextureManager::getTexture(string search)
{
	try
	{
		return textureMap.at(search);
	}
	catch (std::out_of_range)
	{
		std::cout << "Texture: " << search << " was not found!" << std::endl;
		return defaultTexture;
	}
}


void TextureManager::destroyManager()
{
	delete instance;
	instance = nullptr;
}