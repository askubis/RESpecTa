class robotInit;

#ifndef ROBOTINIT_H
#define ROBOTINIT_H
#include "globals.h"

/**
*   Class representing the initiation of one robot.
*/
class robotInit
{
public:
    robotInit(){}
    robotInit(const robotInit& other)
    {
        this->robot=other.robot;
        this->init_values=other.init_values;
    }
    bool equals(robotInit other)
    {
        if(this->robot==other.robot)
        {
            if(this->init_values.size()==other.init_values.size())
            {
                for(int i=0;i<init_values.size();i++)
                {
                    if(init_values[i].first!=other.init_values[i].first || init_values[i].second!=other.init_values[i].second)
                        return false;
                }
                return true;
            }
        }
        return false;
    }

    /**
    *   Creates a string describing the coordinates attributes.
    *   @returns String with the description of the Robot initialization
    */
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
    /**
    *   Writes the data of the state to the XML stream.
    *   @param writer Stream to which the data is written
    */
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
    /**
    *   Loads from XML Stream the data.
    *   @param  reader Stream from which the data is read
    *   @returns List of errors, which occured while loading
    */
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

    /**
    *   Robot, which is being initialized
    */
    Robot robot;
    /**
    *   Vector of generators, and their init arguments.
    */
    std::vector < std::pair<GeneratorType, int> > init_values;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif // ROBOTINIT_H
