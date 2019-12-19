#include "Pelican.h"

Pelican::Pelican()
{
	subType = "Pelican";
}

Pelican::Pelican(int tempEggs)
	:Oviparous(tempEggs)
{
	subType = "Pelican";
}
