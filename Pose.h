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
    Pose();
    bool operator == (Pose other)
    {
        if (this->a.size()!=other.a.size()) return false;
        for(int i=0;i<a.size();i++)
        {
            if(this->a[i]!=other->a[i]) return false;
        }
        if (this->v.size()!=other.v.size()) return false;
        for(int i=0;i<v.size();i++)
        {
            if(this->v[i]!=other->v[i]) return false;
        }
        if (this->coordinates.size()!=other.coordinates.size()) return false;
        for(int i=0;i<coordinates.size();i++)
        {
            if(this->coordinates[i]!=other->coordinates[i]) return false;
        }


        return true;
    }

private:
    std::vector<int> a;
    std::vector<int> v;
    std::vector<int> coordinates;
};

#endif // POSE_H
