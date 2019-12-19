#include "Whale.h"

Whale::Whale()
{
	subType = "Whale";
}

Whale::Whale(int tempNurse)
	:Mammal(tempNurse)
{
	subType = "Whale";

}
