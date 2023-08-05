#pragma once
#include "Person.h"

class Astronomer :
    public Person
{
public:
    Astronomer() {};
    ~Astronomer() {};

    bool isThunderSafe() override { return true; }
    unsigned getLuck() const override;
private:

};

