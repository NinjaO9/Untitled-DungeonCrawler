#pragma once
#include <iostream>
using std::string;

class GameObject
{
public:

	GameObject();

	~GameObject();

	string getTag();

	void setTag(string tag);

private:
	string tag;
};

