#include "globals.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <QXmlStreamReader>


#ifndef ROBOTSET_H
#define ROBOTSET_H
class RobotSet
{
public:
    std::vector<Robot> first;
    std::vector<Robot> second;
    QStringList LoadFromXML(QXmlStreamReader * reader)
    {
        bool wasFirst = false;
        bool wasSecond = false;
        std::vector<Robot> * tmpRobotVect;
        QStringList errors;
        while (!reader->atEnd())
        {
            std::cout<<"READING SET"<<std::endl;
              reader->readNextStartElement();
              std::cout<<reader->name().toString().toStdString()<<std::endl;
            if(reader->name().toString()=="SetOfRobots"&&reader->isEndElement())
            {
                return errors;
            }
            else if(reader->name()=="FirstSet")
            {
                if(wasFirst)
                {
                    //error
                }
                else
                {
                    wasFirst = true;
                    if(reader->isStartElement())
                          tmpRobotVect = &first;
                    else
                          tmpRobotVect = NULL;
                }
            }
            else if(reader->name()=="SecSet")
            {
                if(wasSecond)
                {
                    //error
                }
                else
                {
                    wasSecond = true;
                    if(reader->isStartElement())
                          tmpRobotVect = &second;
                    else
                          tmpRobotVect = NULL;
                }
            }
           else if(reader->name()=="ROBOT")
            {
                if (tmpRobotVect!=NULL)
                {
                    int index = getRobotTable().indexOf(reader->readElementText());
                    if(index<ROBOTS_NUMBER)
                    {
                        tmpRobotVect->push_back((Robot)index);
                    }
                    else
                    {
                        //error out of bounds robot
                    }
                }
                else
                {
                    //error robot outside FirstSet/SecSet in SetOfRobots
                }
            }
            else
            {
                //error unexpected name
            }
        }
    }

};

#endif // ROBOTSET_H
