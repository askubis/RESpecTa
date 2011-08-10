class RobotSet;

#ifndef ROBOTSET_H
#define ROBOTSET_H

#include "globals.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <QXmlStreamReader>

class RobotSet
{
public:

    /**
    *   Creates a string describing the coordinates attributes.
    *   @returns String with the description of the RobotSet
    */
    std::string Print()
    {
        std::string x;
        x+="\nFIRST SET:";
        for(std::vector<Robot>::iterator it = first.begin();it!=first.end();it++)
        {
            x+="\nROBOT: ";
            x+=ROBOT_TABLE[(*it)];
        }
        /*x+="\nSECOND SET:";
        for(std::vector<Robot>::iterator it = second.begin();it!=second.end();it++)
        {
            x+="\nROBOT: ";
            x+=ROBOT_TABLE[(*it)];
        }*/
        return x;
    }

    bool equals(RobotSet other)
    {
        if(this->first.size()==other.first.size())
        {
            for(int i=0;i<first.size();i++)
            {
                if(first[i]!=other.first[i])
                    return false;
            }
            return true;
        }
        return false;
    }

    /**
    *   Writes the data of the state to the XML stream.
    *   @param writer Stream to which the data is written
    */
    void Print(QXmlStreamWriter * writer)
    {
        writer->writeStartElement("SetOfRobots");
        writer->writeStartElement("FirstSet");
        for(std::vector<Robot>::iterator it = first.begin();it!=first.end();it++)
        {
            writer->writeTextElement("ROBOT", QString().fromStdString(ROBOT_TABLE[(*it)]));
        }
        writer->writeEndElement();

        /*if(second.size()>0)
        {
            writer->writeStartElement("SecSet");
            for(std::vector<Robot>::iterator it = second.begin();it!=second.end();it++)
            {
                writer->writeTextElement("ROBOT", QString().fromStdString(ROBOT_TABLE[(*it)]));
            }
            writer->writeEndElement();
        }*/
        writer->writeEndElement();
    }

    /**
    *   Loads from XML Stream the data and passes it to the Poses(if any).
    *   @param  reader Stream from which the data is read
    *   @returns List of errors, which occured while loading
    */
    QStringList LoadFromXML(QXmlStreamReader * reader)
    {
        QStringList errors;
        bool wasFirst = false;
        std::vector<Robot> * tmpRobotVect;
        while (!reader->atEnd())
        {
              reader->readNextStartElement();
            if(reader->name().toString()=="SetOfRobots"&&reader->isEndElement())
            {
                if(first.size()==0)
                {
                    char linenum[30];
                    sprintf(linenum,"; line: %lld", reader->lineNumber());
                    errors.push_back(QString("Set empty in robotset")+=linenum);
                }
                return errors;
            }
            else if(reader->name()=="FirstSet")
            {
                if(reader->isStartElement())
                {
                    if(wasFirst)
                    {
                        char linenum[30];
                        sprintf(linenum,"; line: %lld", reader->lineNumber());
                        errors.push_back(QString("second set defined more than once")+=linenum);
                    }
                    else
                    {
                          wasFirst = true;
                          tmpRobotVect = &first;
                    }
                }
                else
                {
                    wasFirst = true;
                    tmpRobotVect = NULL;
                }
            }
            /*else if(reader->name()=="SecSet")
            {
                if(reader->isStartElement())
                {
                    if(wasSecond)
                    {
                        char linenum[30];
                        sprintf(linenum,"; line: %lld", reader->lineNumber());
                        errors.push_back(QString("second set defined more than once")+=linenum);
                    }
                    else
                    {
                          wasSecond = true;
                          tmpRobotVect = &second;
                    }
                }
                else
                {
                    wasSecond = true;
                    tmpRobotVect = NULL;
                }
            }*/
           else if(reader->name()=="ROBOT"&&reader->isStartElement())
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
                        char linenum[30];
                        sprintf(linenum,"; line: %lld", reader->lineNumber());
                        errors.push_back(QString("Out of bounds Robot")+=linenum);
                    }
                }
                else
                {
                    char linenum[30];
                    sprintf(linenum,"; line: %lld", reader->lineNumber());
                    errors.push_back(QString("Robot parameter defined outside any set")+=linenum);
                }
            }
            else if (reader->isStartElement())
            {
                char linenum[30];
                sprintf(linenum,"; line: %lld", reader->lineNumber());
                errors.push_back((QString("Unexpected name while reading <SetOfRobots>: ")+=reader->name())+=linenum);
            }
        }
        if(first.size()==0)
        {
            char linenum[30];
            sprintf(linenum,"; line: %lld", reader->lineNumber());
            errors.push_back(QString("Set empty in <SetOfRobots>")+=linenum);
        }
        return errors;
    }

    /**
    *   First set of Robots.
    */
    std::vector<Robot> first;
    /**
    *   Second Set of robots.
    */
    //std::vector<Robot> second;
};

#endif // ROBOTSET_H
