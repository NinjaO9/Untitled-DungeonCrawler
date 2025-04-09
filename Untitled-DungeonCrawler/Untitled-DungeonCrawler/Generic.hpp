#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>


class Generic
{
public:

	Generic()
	{
		window = sf::RenderWindow(sf::VideoMode({ 200, 200 }), "SFML works!");
	}


private:

	sf::RenderWindow window;
};

