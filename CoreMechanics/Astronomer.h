#pragma once
#include "Person.h"

class Astronomer :
    public Person
{
public:
    Astronomer() {};
    ~Astronomer() {};

    bool isThunderSafe() override { return true; }
    int luck() override { return 1; }
private:

};

