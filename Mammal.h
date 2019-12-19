#pragma once
#include "Animal.h"
class Mammal :
	public Animal
{
private:
	int nurse;
public:
	string subType;

	Mammal();
	Mammal(int tempNurse);
	string getType();
	string getSubType();
	int getNurse();
	void display();
};

