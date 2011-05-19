#ifndef GENINIT_H
#define GENINIT_H
#include "globals.h"
class genInit
{
public:

    Robot robot;
    std::vector < std::pair<GeneratorType, int> > init_values;

    genInit(){}


    std::string Print()
    {
        std::string x;
        x+="\nECP: ";
        x+="\nROBOT: ";
        x+=ROBOT_TABLE[robot];
        for(std::vector < std::pair<GeneratorType, int> >::iterator iter = init_values.begin(); iter!=init_values.end(); iter++)
        {
            x+="\nGENERATOR: ";
            x+=GENERATOR_TYPE_TABLE[(*iter).first];
            char tmp[20];
            sprintf(tmp, "%d", (*iter).second);
            x+=" ";
            x+=tmp;
        }
        return x;
    }

    void Print(QXmlStreamWriter * writer)
    {
        writer->writeStartElement("ecp");
        writer->writeAttribute(QString("name"), QString().fromStdString(ROBOT_TABLE[robot]));
        for(std::vector < std::pair<GeneratorType, int> >::iterator iter = init_values.begin(); iter!=init_values.end(); iter++)
        {
            char tmp[20];
            sprintf(tmp, "%d", (*iter).second);
            writer->writeTextElement(QString().fromStdString(GENERATOR_TYPE_TABLE2[(*iter).first]), QString().fromStdString(tmp));
        }
        writer->writeEndElement();
    }


    QStringList LoadFromXML(QXmlStreamReader * reader)
    {
        QStringList errors;
        if(reader->attributes().hasAttribute("name"))
        {
            int index = (getRobotTable().indexOf(reader->attributes().value("name").toString()));
            if(index<ROBOTS_NUMBER && index>=0)
            {
                 robot = (Robot)index;
            }
            else
            {
                robot = (Robot)0;
                errors.push_back("out of bound robot");
            }
        }
        else
        {
            robot = (Robot)0;
            errors.push_back("no name in ecp");
        }

        while (!reader->atEnd())
        {
              reader->readNextStartElement();
              std::cout<<"GENINIT: "<<reader->name().toString().toStdString()<<std::endl;
              if(reader->name()=="ecp"&&reader->isEndElement())
              {
                  if(init_values.size()==0) errors.push_back(QString("no init values for the Robot: ").append(ROBOT_TABLE(robot)));
                  return errors;
              }
              else
              {
                  int index = getGeneratorTypeTable2().indexOf(reader->name().toString());
                  if(index<GENERATORS_NUMBER && index>=0)
                  {
                      init_values.push_back(std::make_pair((GeneratorType)index,reader->readElementText().toInt()));
                  }
                  else
                  {

                      errors.push_back((QString("unexpected name while reading <ecp>: ")+=reader->name())+=append(ROBOT_TABLE(robot)));
                  }

              }
        }
        if(init_values.size()==0) errors.push_back(QString("no init values for Robot: ").append(ROBOT_TABLE(robot)));
        return errors;
    }

};

////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif // GENINIT_H
