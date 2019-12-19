#include "Bat.h"

Bat::Bat()
{
	subType = "Bat";
}

Bat::Bat(int tempNurse)
	:Mammal(tempNurse)
{
	subType = "Bat";

}
