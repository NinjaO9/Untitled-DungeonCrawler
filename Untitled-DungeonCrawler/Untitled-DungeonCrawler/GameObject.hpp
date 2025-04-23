#pragma once
#include <iostream>
#include <cmath>
#include <random>
#include <SFML/Graphics.hpp>
using std::string;
using std::cout;
using std::endl;

class GameManager; // forward declaration

class GameObject // Variables / Functions in this class should be applicable to nearly everything we will have in the game
{
public:
	GameManager* gm; // intentionally public, any gameobject should be able to easily get their pointer to the game manager
	GameObject(sf::Vector2f pos = sf::Vector2f(0,0), string tag = "Missing-Tag")
	{ 
		this->tag = tag; 
		this->pos = pos;
		this->gm = nullptr; // just to get rid of warnings
		initializeGameManager();
	}

	virtual ~GameObject();

	string getTag() { return this->tag; }

	void setTag(string const tag) { this->tag = tag; };

	float checkDistance(sf::Vector2f& const target); // Implicitly check the distance from this gameObject to another object

	float checkDistance(sf::Vector2f& const origin, sf::Vector2f& const target); // check the distance from a given origin to another object

	/*  Virtual functions */

	virtual void update(); // every derived class should contain this

	virtual sf::Vector2f& getPos(); // Some classes may handle pos differently

	virtual void setPos(sf::Vector2f const newPos);


private:

	void initializeGameManager();

	string tag;
	sf::Vector2f pos;
};

/*
* Variable Explanation:
*  - 'tag' is a string which will be used to identify each object. This will allow us to distinguish gameObjects from a higher level if we need to do so
* - 'pos' is a Vector2 (float) which is used to contain the position of the gameObject. Each gameObject has a position on the screen, so it makes sense for the position to be at the highest level
*/

