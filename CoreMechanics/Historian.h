#pragma once
#include "Person.h"
class Historian :
    public Person
{
public:
    ~Historian() = default;

    unsigned hit() override;
    //enemy switch
    //first step attack bonus
};

