#pragma once
#include "Person.h"

class Astronomer :
    public Person
{
public:
    Astronomer();
    virtual ~Astronomer() {};

    bool isThunderSafe() override { return true; }
    
private:

};

