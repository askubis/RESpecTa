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
    Coordinates(){}
    Coordinates(Coordinates& old)
    {
        this->coordType=old.coordType;
        this->filePath=old.filePath;
        this->motionType=old.motionType;
        this->poses=old.poses;
    }

private:
    std::string filePath;
    CoordType coordType;
    MotionType motionType;
    std::vector<Pose> poses;


};

#endif // COORDINATES_H
