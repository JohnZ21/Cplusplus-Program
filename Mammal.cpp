#include "Mammal.h"

Mammal::Mammal()
{
	subType = "";
	type = "Mammal";
	nurse = 0;
}

Mammal::Mammal(int tempNurse)
{
	subType = "";
	type = "Mammal";
	nurse = tempNurse;
}

string Mammal::getType()
{
	return type;
}

string Mammal::getSubType()
{
	return subType;
}

int Mammal::getNurse()
{
	return nurse;
}

void Mammal::display()
{
	cout << right << setfill('0') <<
		setw(6) << trackNumber;
	cout << left << setfill(' ') <<
		setw(10) << " " <<
		setw(16) << name <<
		setw(16) << type <<
		setw(16) << subType << 
		setw(10) << "0" <<
		setw(10) << nurse <<
		endl;
}
