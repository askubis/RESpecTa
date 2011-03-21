#include "globals.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "BaseNode.h"
#include "Coordinates.h"

#ifndef RUNGENNODE_H
#define RUNGENNODE_H

class RunGenNode:public BaseNode
{
public:




private:
    ROBOT x;
    GeneratorType genType;
    Coordinates * coords;
    float * genArg;
    std::string speech;


};

#endif // RUNGENNODE_H
