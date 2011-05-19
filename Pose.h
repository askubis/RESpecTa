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
        for(unsigned int i=0; i<other.a.size();i++)
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

    std::string Print()
    {
        unsigned int i=0;
        std::string x;
        char  w[12];
        std::vector<double> tmp = a;
        x+="\nPOSE:";
        x+="\nAccelerations: ";
        for ( i=0;i<tmp.size();i++)
        {
            sprintf(w, "%lf", tmp[i]);
            x+=w;
            x+=" ";
        }
        tmp = v;
        x+="\nVelocities: ";
        for (i=0;i<tmp.size();i++)
        {
            sprintf(w, "%lf", tmp[i]);
            x+=w;
            x+=" ";
        }
        tmp = coordinates;
        x+="\nCoords: ";
        for (i=0;i<tmp.size();i++)
        {
            sprintf(w, "%lf", tmp[i]);
            x+=w;
            x+=" ";
        }
        return x;
    }

    void Print(QXmlStreamWriter * writer)
    {
        unsigned int i;
        char  w[12];
        std::string x;
        writer->writeStartElement("Pose");
        std::vector<double> tmp = a;
        for (i=0;i<tmp.size();i++)
        {
            sprintf(w, "%lf", tmp[i]);
            x+=w;
            x+=" ";
        }
        writer->writeTextElement("Accelerations", QString().fromStdString(x));
        x.clear();
        tmp = v;
        for (i=0;i<tmp.size();i++)
        {
            sprintf(w, "%lf", tmp[i]);
            x+=w;
            x+=" ";
        }
        writer->writeTextElement("Velocities", QString().fromStdString(x));
        x.clear();
        tmp = coordinates;
        for (i=0;i<tmp.size();i++)
        {
            sprintf(w, "%lf", tmp[i]);
            x+=w;
            x+=" ";
        }
        writer->writeTextElement("Coordinates", QString().fromStdString(x));
        writer->writeEndElement();
    }

    QStringList LoadFromXML(QXmlStreamReader * reader)
    {
        QStringList errors;
        bool wasA=false;
        bool wasC=false;
        bool wasV=false;
        while (!reader->atEnd())
        {
            //get coordinateType and motionType
              reader->readNextStartElement();
              std::cout<<"POSE: "<<reader->name().toString().toStdString()<<std::endl;
            if(reader->name().toString()=="Pose"&&reader->isEndElement())
            {
                if(!wasA||!wasV||!wasC)errors.push_back("no A, C or V in this pose");
                return errors;
            }
            else if (reader->name()=="Accelerations")
            {
                if(wasA)
                {
                    errors.push_back("the accelerations were twice defined");
                }
                else
                {
                    wasA=true;
                    QString tmpString = reader->readElementText();
                    QStringList strList = tmpString.split(QRegExp("\\s+"));
                    foreach(QString str, strList)
                    {
                        a.push_back(str.toDouble());
                    }
                }
            }
            else if (reader->name()=="Velocity")
            {
                if(wasV)
                {
                    errors.push_back("the velocities were twice defined");
                }
                else
                {
                    wasV=true;
                    QString tmpString = reader->readElementText();
                    QStringList strList = tmpString.split(QRegExp("\\s+"));
                    foreach(QString str, strList)
                    {
                        v.push_back(str.toDouble());
                    }
                }
            }
            else if (reader->name()=="Coordinates")
            {
                if(wasC)
                {
                    errors.push_back("the Coordinates were twice defined");
                }
                else
                {
                    wasC=true;
                    QString tmpString = reader->readElementText();
                    QStringList strList = tmpString.split(QRegExp("\\s+"));
                    foreach(QString str, strList)
                    {
                        coordinates.push_back(str.toDouble());
                    }
                }
            }
            else
            {
                QString("unexpected name while reading <pose>: ")+=reader->name()
            }
        }
        if(!wasA||!wasV||!wasC)errors.push_back("no A, C or V in this pose");
            return errors;
    }

private:
    std::vector<double> a;
    std::vector<double> v;
    std::vector<double> coordinates;
};

#endif // POSE_H
