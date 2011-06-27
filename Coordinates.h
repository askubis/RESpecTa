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
class QXmlStreamReader;
QT_END_NAMESPACE


class Coordinates
{
public:
    Coordinates(){}
    Coordinates(Coordinates& old)
    {
        this->coordType=old.coordType;
        this->motionType=old.motionType;
        Pose * x;
        for(unsigned int i=0;i<old.poses.size();i++)
        {
            x=new Pose(*(old.poses[i]));
            this->poses.push_back(x);
        }
    }

    ~Coordinates()
    {
        for(unsigned int i = 0;i<poses.size();i++)
        {
            delete poses[i];
        }
    }



    CoordType getCoordType() {return coordType;}
    void setCoordType(CoordType newCoordType) {coordType=newCoordType;}

    MotionType getMotionType() {return motionType;}
    void setMotionType(MotionType newMotionType) {motionType=newMotionType;}

    std::vector<Pose *> getPoses(){return poses;}
    void setPoses(std::vector<Pose *> newPoses){poses=newPoses;}

    std::string Print()
    {
        std::string x;
        if(poses.size()>0 )
        {
            x+="\nMotion Type:";
            x+=MOTION_TYPE_TABLE[motionType];
            x+="\nCoord Type:";
            x+=COORD_TYPE_TABLE[coordType];
            foreach(Pose * pos, poses)
            {
                x+=pos->Print();
            }
        }
        return x;
    }

    void Print(QXmlStreamWriter * writer)
    {
        writer->writeStartElement("Trajectory");
        writer->writeAttribute(QString("coordinateType"), QString().fromStdString(COORD_TYPE_TABLE[coordType]));
        writer->writeAttribute(QString("motionType"), QString().fromStdString(MOTION_TYPE_TABLE[motionType]));
        foreach(Pose * pos, poses)
        {
            pos->Print();
        }
        writer->writeEndElement();
    }

    QStringList LoadFromXML(QXmlStreamReader * reader)
    {
        QStringList errors;
        if(reader->attributes().hasAttribute("coordinateType")&&reader->attributes().hasAttribute("motionType"))
        {
            CoordType Cindex = (CoordType)(getCoordTypeTable().indexOf(reader->attributes().value("coordinateType").toString()));
            if(isProper(coordType))
            {
                 coordType = Cindex;
            }
            else
            {
                coordType = (CoordType)0;
                char linenum[30];
                sprintf(linenum,"; line: %lld", reader->lineNumber());
                errors.push_back(QString("Out of bounds CoordType")+=linenum);
            }
            MotionType Mindex = (MotionType)(getMotionTypeTable().indexOf(reader->attributes().value("motionType").toString()));
            if(isProper(Mindex))
            {
                 motionType = Mindex;
            }
            else
            {
                motionType = (MotionType)0;
                char linenum[30];
                sprintf(linenum,"; line: %lld", reader->lineNumber());
                errors.push_back(QString("Out of bounds MotionType")+=linenum);
            }
        }
        else
        {
            char linenum[30];
            sprintf(linenum,"; line: %lld", reader->lineNumber());
            errors.push_back(QString("The trajectory has no coordinateType or motionType attribute")+=linenum);
            return errors;
        }
        while (!reader->atEnd())
        {
            if(reader->name().toString()=="Trajectory"&&reader->isEndElement())
            {
                return errors;
            }
              reader->readNextStartElement();
            if(reader->name().toString()=="Trajectory"&&reader->isEndElement())
            {
                return errors;
            }
            else if (reader->name()=="Pose"&&reader->isStartElement())
            {
                bool mark = true;
                Pose * tmp = new Pose();
                errors+=tmp->LoadFromXML(reader);
                if(poses.size()>0)
                {
                    Pose * pose = poses[0];
                    if(pose->getA().size()!=tmp->getA().size())
                    {
                        char linenum[30];
                        sprintf(linenum,"; line: %lld", reader->lineNumber());
                        errors.push_back(QString("The new pose has a different vectors length than the previous one: ")+=linenum);
                        mark = false;
                    }
                }
                if(mark==true)
                {
                    poses.push_back(tmp);
                }
            }
            else if (reader->isStartElement())
            {
                char linenum[30];
                sprintf(linenum,"; line: %lld", reader->lineNumber());
                errors.push_back((QString("unexpected name while reading <coordinates>: ")+=reader->name())+=linenum);
            }
        }
            return errors;
    }



private:
    CoordType coordType;
    MotionType motionType;
    std::vector<Pose *> poses;


};

#endif // COORDINATES_H


