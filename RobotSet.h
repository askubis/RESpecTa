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

    std::string Print()
    {
        std::string x;
        x+="\nFIRST SET:";
        for(std::vector<Robot>::iterator it = first.begin();it!=first.end();it++)
        {
            x+="\nROBOT: ";
            x+=ROBOT_TABLE[(*it)];
        }
        x+="\nSECOND SET:";
        for(std::vector<Robot>::iterator it = second.begin();it!=second.end();it++)
        {
            x+="\nROBOT: ";
            x+=ROBOT_TABLE[(*it)];
        }
        return x;
    }

    void Print(QXmlStreamWriter * writer)
    {
        writer->writeStartElement("SetOfRobots");
        writer->writeStartElement("FirstSet");
        for(std::vector<Robot>::iterator it = first.begin();it!=first.end();it++)
        {
            writer->writeTextElement("ROBOT", QString().fromStdString(ROBOT_TABLE[(*it)]));
        }
        writer->writeEndElement();

        if(second.size()>0)
        {
            writer->writeStartElement("SecSet");
            for(std::vector<Robot>::iterator it = second.begin();it!=second.end();it++)
            {
                writer->writeTextElement("ROBOT", QString().fromStdString(ROBOT_TABLE[(*it)]));
            }//*/
            writer->writeEndElement();
        }
        writer->writeEndElement();
    }

    QStringList LoadFromXML(QXmlStreamReader * reader)
    {
        QStringList errors;
        bool wasFirst = false;
        bool wasSecond = false;
        std::vector<Robot> * tmpRobotVect;
        while (!reader->atEnd())
        {
              reader->readNextStartElement();
              std::cout<<"ROBOTSET: "<<reader->name().toString().toStdString()<<std::endl;
            if(reader->name().toString()=="SetOfRobots"&&reader->isEndElement())
            {
                if(first.size()==0&&second.size()==0)
                {
                    char linenum[30];
                    sprintf(linenum,"; line: %lld", reader->lineNumber());
                    errors.push_back(QString("both sets empty in robotset")+=linenum);
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
            else if(reader->name()=="SecSet")
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
            }
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
                    errors.push_back(QString("robot outside any set")+=linenum);
                }
            }
            else if (reader->isStartElement())
            {
                char linenum[30];
                sprintf(linenum,"; line: %lld", reader->lineNumber());
                errors.push_back((QString("unexpected name while reading <SetOfRobots>: ")+=reader->name())+=linenum);
            }
        }
        if(first.size()==0&&second.size()==0)
        {
            char linenum[30];
            sprintf(linenum,"; line: %lld", reader->lineNumber());
            errors.push_back(QString("both sets empty in <SetOfRobots>")+=linenum);
        }
        return errors;
    }


};

#endif // ROBOTSET_H
