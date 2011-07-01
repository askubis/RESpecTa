#ifndef GENINIT_H
#define GENINIT_H
#include "globals.h"
class genInit
{
public:

    Robot robot;
    std::vector < std::pair<GeneratorType, int> > init_values;

    genInit(){}
    genInit(const genInit& other)
    {
        this->robot=other.robot;
        this->init_values=other.init_values;
    }

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
            Robot index = (Robot)(getRobotTable().indexOf(reader->attributes().value("name").toString()));
            if(isProper(index))
            {
                 robot = index;
            }
            else
            {
                robot = (Robot)0;
                char linenum[30];
                sprintf(linenum,"; line: %lld", reader->lineNumber());
                errors.push_back(QString("Out of bound Robot")+=linenum);
            }
        }
        else
        {
            robot = (Robot)0;
            char linenum[30];
            sprintf(linenum,"; line: %lld", reader->lineNumber());
            errors.push_back(QString("no name in ecp")+=linenum);
        }

        while (!reader->atEnd())
        {
              reader->readNextStartElement();
              if(reader->name()=="ecp"&&reader->isEndElement())
              {
                  if(init_values.size()==0)
                  {
                      char linenum[30];
                      sprintf(linenum,"; line: %lld", reader->lineNumber());
                      errors.push_back(QString("no init values for the Robot: ").append(QString().fromStdString(ROBOT_TABLE[robot])));
                  }
                  return errors;
              }
              else if (reader->isStartElement())
              {
                  GeneratorType index = (GeneratorType)(getGeneratorTypeTable2().indexOf(reader->name().toString()));
                  if(isProper(index))
                  {
                      init_values.push_back(std::make_pair(index,reader->readElementText().toInt()));
                  }
                  else
                  {
                      char linenum[30];
                      sprintf(linenum,"; line: %lld", reader->lineNumber());
                      errors.push_back(QString("Out of bounds GeneratorType")+=linenum);
                  }

              }
        }
        if(init_values.size()==0)
        {
            char linenum[30];
            sprintf(linenum,"; line: %lld", reader->lineNumber());
            errors.push_back(QString("no init values for Robot: ").append(QString().fromStdString(ROBOT_TABLE[robot]))+=linenum);
        }
        return errors;
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif // GENINIT_H
