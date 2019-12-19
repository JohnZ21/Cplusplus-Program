#include "Oviparous.h"

Oviparous::Oviparous()
{
	subType = "";
	type = "Oviparous";
	numberOfEggs = 0;
}

Oviparous::Oviparous(int eggs)
{
	subType = "";
	type = "Oviparous";
	numberOfEggs = eggs;
}

string Oviparous::getType()
{
	return "Oviparous";
}

string Oviparous::getSubType()
{
	return subType;
}

int Oviparous::getNumberOfEggs()
{
	return numberOfEggs;
}

void Oviparous::display()
{
	cout << right << setfill('0') <<
		setw(6) << trackNumber;
	cout << left <<setfill(' ')<< 
		setw(10)<< " "<<
		setw(16) << name <<
		setw(16) << type <<
		setw(16) << subType <<
		setw(10) << numberOfEggs <<
		setw(10) << "0" <<
		endl;
}
