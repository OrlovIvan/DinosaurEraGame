#pragma once
#include "Person.h"

class Policeman :
    public Person
{
public:
    //attack twice
    unsigned hit() override;
};

