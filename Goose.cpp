#include "Goose.h"

Goose::Goose()
{
	subType = "Goose";
}

Goose::Goose(int tempEggs)
	:Oviparous(tempEggs)
{
	subType = "Goose";
}
