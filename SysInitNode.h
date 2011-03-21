#include "globals.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "BaseNode.h"

#ifndef SYSINITNODE_H
#define SYSINITNODE_H

struct genInit
{
    Robot robot;
    int args[GeneratorType::NUMBER];
};


class sysInitNode:public BaseNode
{
public:

private:
    std::vector<genInit> inits;//wektor gdyz w jednym stanie inicjalizacji moze sie znajdowac wiele robotów
    Transmitter transmitter;
    bool cubestate;
    std::vector<Sensor> sensors;
};

#endif // SYSINITNODE_H
