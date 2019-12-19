#pragma once
#include <string>
#include <iostream>
#include <iomanip>
using namespace std;


class Animal
{

public:
	string name;
	int trackNumber;
	string type;
	Animal() {};

	virtual string getSubType() { return ""; };

	virtual void display() {};
};

