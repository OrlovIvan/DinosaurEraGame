#include "pch.h"
#include "Astronomer.h"

unsigned Astronomer::getLuck() const
{
	return Person::getLuck()+1;
}
