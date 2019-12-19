#pragma once
#include "Animal.h"
class Oviparous :
	public Animal
{
private:
	int numberOfEggs;
public:
	string subType;

	Oviparous();
	Oviparous(int eggs);
	string getType();
	string getSubType();
	int getNumberOfEggs();
	void display();

};


