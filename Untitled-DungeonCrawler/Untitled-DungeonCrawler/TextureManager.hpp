#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map> // std hashmap - used for effiient lookup of textures
#include <SFML/Graphics.hpp>

using std::string;
using std::ifstream;
using std::unordered_map;

class TextureManager
{
public:
	static TextureManager*& getInstance(); // a static function means that the function is independant of a class's instance (can be called without initializing a class)

	void loadTextures(string fileName /* 'file' should be a txt file which contains the file directories to other files that contain sprites */);

	sf::Texture& getTexture(string search);

	void destroyManager();


private:
	static TextureManager* instance; // static means that the variable stays the same regardless of instantiation (which there should only be one)
	sf::Texture defaultTexture; // blank texture
	unordered_map<string, sf::Texture> textureMap; // hashmap for texture look up (Key: string, Value: sf::Texture)

	TextureManager() { }; // We don't want to instantiate this class more than once (we only ever want one instance), so we will make the constructor private, called once internally

	TextureManager(TextureManager& manager) = delete; // Make the copy constructor private to prevent copying
	TextureManager& operator=(TextureManager& oldManager) = delete;

	~TextureManager() { return; } // Make the destructor private, we will have a function that must be manually called to destroy the manager (just remember to implement it)

};