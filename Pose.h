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
        this->a=other.a;
        this->v=other.v;
        this->coordinates=other.coordinates;
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

    std::vector<int> getA(){return a;}
    void setA(std::vector<int> newA){a=newA;}

    std::vector<int> getV(){return v;}
    void setV(std::vector<int> newV){v=newV;}

    std::vector<int> getC(){return coordinates;}
    void setC(std::vector<int> newC){coordinates=newC;}

private:
    std::vector<int> a;
    std::vector<int> v;
    std::vector<int> coordinates;
};

#endif // POSE_H
