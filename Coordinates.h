#include "globals.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>

#include "Pose.h"

#ifndef COORDINATES_H
#define COORDINATES_H

class Coordinates
{
public:

private:
    std::string filePath;
    CoordType coordType;
    MotionType motionType;
    std::vector<Pose> poses;


};

#endif // COORDINATES_H
