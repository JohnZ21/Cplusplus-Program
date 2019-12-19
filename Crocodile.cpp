#include "Crocodile.h"

Crocodile::Crocodile()
{
	subType = "Crocodile";
}

Crocodile::Crocodile(int tempEggs)
	:Oviparous(tempEggs)
{
	subType = "Crocodile";
}
