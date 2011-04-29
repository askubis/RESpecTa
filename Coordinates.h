#include "globals.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>

#include "Pose.h"



#ifndef COORDINATES_H
#define COORDINATES_H

QT_BEGIN_NAMESPACE
class QString;
QT_END_NAMESPACE


class Coordinates
{
public:
    Coordinates(){}
    Coordinates(Coordinates& old)
    {
        this->coordType=old.coordType;
        this->filePath=old.filePath;
        this->motionType=old.motionType;
        Pose * x;
        for(int i=0;i<old.poses.size();i++)
        {
            x=new Pose(*(old.poses[i]));
            this->poses.push_back(x);
        }
    }

    ~Coordinates()
    {
        for(int i = 0;i<poses.size();i++)
        {
            delete poses[i];
        }
    }

    QString getFilePath() {return filePath;}
    void setFilePath(QString newPath) {filePath=newPath;}

    CoordType getCoordType() {return coordType;}
    void setCoordType(CoordType newCoordType) {coordType=newCoordType;}

    MotionType getMotionType() {return motionType;}
    void setMotionType(MotionType newMotionType) {motionType=newMotionType;}

    std::vector<Pose *> getPoses(){return poses;}
    void setPoses(std::vector<Pose *> newPoses){poses=newPoses;}


private:
    QString filePath;
    CoordType coordType;
    MotionType motionType;
    std::vector<Pose *> poses;


};

#endif // COORDINATES_H


