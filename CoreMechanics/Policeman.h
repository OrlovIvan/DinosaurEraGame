#pragma once
#include "Person.h"

class Policeman :
    public Person
{
    //attack twice
    unsigned hit() override;
};

