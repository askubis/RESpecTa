#include "globals.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>


#ifndef POSE_H
#define POSE_H
class Pose
{
public:
    Pose(){}
    Pose(const Pose& other)
    {
        for(int i=0; i<other.a.size();i++)
        {
            this->a.push_back(other.a[i]);
            this->v.push_back(other.v[i]);
            this->coordinates.push_back(other.coordinates[i]);
        }

    }

    /*bool operator == (Pose other)
    {
        if (this->a.size()!=other.a.size()) return false;
        for(int i=0;i<a.size();i++)
        {
            if(this->a[i]!=other.a[i]) return false;
        }
        if (this->v.size()!=other.v.size()) return false;
        for(int i=0;i<v.size();i++)
        {
            if(this->v[i]!=other.v[i]) return false;
        }
        if (this->coordinates.size()!=other.coordinates.size()) return false;
        for(int i=0;i<coordinates.size();i++)
        {
            if(this->coordinates[i]!=other.coordinates[i]) return false;
        }


        return true;
    }*/

    std::vector<double> getA(){return a;}
    void setA(std::vector<double> newA){a=newA;}

    std::vector<double> getV(){return v;}
    void setV(std::vector<double> newV){v=newV;}

    std::vector<double> getC(){return coordinates;}
    void setC(std::vector<double> newC){coordinates=newC;}

private:
    std::vector<double> a;
    std::vector<double> v;
    std::vector<double> coordinates;
};

#endif // POSE_H
