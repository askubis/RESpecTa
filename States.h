#include "globals.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include "RobotSet.h"
#include "Coordinates.h"

#include <stdio.h>
#include <stdlib.h>

#include "genInit.h"
#include "baseState.h"
class QXmlStreamWriter;
class QXmlStreamReader;
#include <QtGui>


#ifndef BASESTATE_H
#define BASESTATE_H

////////////////////////////////////////////////////////////////////////////////////////////////////////////
class StopState:public BaseState
{
    public:
    StopState():BaseState(){}
    StopState(StopState& old):BaseState(old){}

    void Print(QXmlStreamWriter*){}
    std::string Print()
    {
        std::string x;
        x+="Name: ";
        x+=this->stateName.toStdString();
        if(this->getType()<STATE_TYPES_NUMBER)
        {
            x+="\nStateType: ";
            x+=STATE_TYPE_TABLE[this->getType()];
        }
        if(parameters.size()>0)
        {
            x+="\nParameters: ";
            x+=this->parameters.toStdString();
        }
        return x;
    }
    QStringList LoadFromXML(QXmlStreamReader * reader)
    {
        QStringList errors;
        while (!reader->atEnd())
        {
              reader->readNextStartElement();
              std::cout<<"StopState: "<<reader->name().toString().toStdString()<<std::endl;
              if(reader->name()=="State"&&reader->isEndElement())
              {
                  return errors;
              }
              else if(reader->name()=="PosX"&&reader->isStartElement())
              {
                  this->setPos(reader->readElementText().toDouble(), this->pos().y());
              }
              else if(reader->name()=="PosY"&&reader->isStartElement())
              {
                  this->setPos(this->pos().x(),reader->readElementText().toDouble());
              }
              else if (reader->name()!="transition"&&reader->isStartElement())
              {
                  char linenum[30];
                  sprintf(linenum,"; line: %lld", reader->lineNumber());
                  errors.push_back((QString("unexpected name while reading stop generator <State>: ")+=reader->name())+=linenum);
              }

        }
        return errors;
    }
};


////////////////////////////////////////////////////////////////////////////////////////////////////////////
class EmptyGenForSetState:public BaseState
{
public:
    EmptyGenForSetState():BaseState(){}
    EmptyGenForSetState(EmptyGenForSetState& old):BaseState(old)
    {
        this->set = old.set;
    }

    RobotSet getSet() {return set;}
    void setSet(RobotSet newSet) {set=newSet;}
    void Print(QXmlStreamWriter * writer)
    {

        if(parameters.size()>0)
        {
            writer->writeTextElement("Parameters", parameters);
            //x+=this->parameters.toStdString();
        }
        set.Print(writer);
    }
    std::string Print()
    {
        std::string x;
        x+="Name: ";
        x+=this->stateName.toStdString();
        x+="\nStateType: ";
        x+=STATE_TYPE_TABLE[this->getType()];
        if(parameters.size()>0)
        {
            x+="\nParameters: ";
            x+=this->parameters.toStdString();
        }
        x+=set.Print();
        return x;
    }
    QStringList LoadFromXML(QXmlStreamReader * reader)
    {
        bool wasSet = false;
        bool wasParam = false;
        QStringList errors;
        while (!reader->atEnd())
        {
              reader->readNextStartElement();
              std::cout<<"EmptyGenForSetState: "<<reader->name().toString().toStdString()<<std::endl;
              if(reader->name()=="State"&&reader->isEndElement())
              {
                  if(!wasSet)
                  {
                      char linenum[30];
                      sprintf(linenum,"; line: %lld", reader->lineNumber());
                      errors.push_back(QString("The RobotSet parameter was not defined for the EmptyGenForSetState")+=linenum);
                  }
                  return errors;
              }
              else if(reader->name()=="SetOfRobots"&&reader->isStartElement())
              {
                  if(wasSet)
                  {
                      char linenum[30];
                      sprintf(linenum,"; line: %lld", reader->lineNumber());
                      errors.push_back(QString("the RobotSet parameter has already been defined")+=linenum);
                  }
                  else
                  {
                      errors+=set.LoadFromXML(reader);
                      wasSet=true;
                  }
              }
              else if(reader->name()=="PosX"&&reader->isStartElement())
              {
                  this->setPos(reader->readElementText().toDouble(), this->pos().y());
              }
              else if(reader->name()=="PosY"&&reader->isStartElement())
              {
                  this->setPos(this->pos().x(),reader->readElementText().toDouble());
              }
              else if (reader->name()=="Parameters"&&reader->isStartElement())
              {
                  if(wasParam)
                  {
                      char linenum[30];
                      sprintf(linenum,"; line: %lld", reader->lineNumber());
                      errors.push_back(QString("2 or more parameters in empty gen for set state ")+=linenum);
                  }
                  else
                  {
                      parameters=reader->readElementText();
                      wasParam=true;
                  }
              }
              else if (reader->name()!="transition"&&reader->isStartElement())
              {
                  char linenum[30];
                  sprintf(linenum,"; line: %lld", reader->lineNumber());
                  errors.push_back((QString("unexpected name while reading empty generator <State>: ")+=reader->name())+=linenum);
              }
        }
        if(!wasSet)
        {
            char linenum[30];
            sprintf(linenum,"; line: %lld", reader->lineNumber());
            errors.push_back(QString("The RobotSet parameter was not defined for the EmptyGenForSetState")+=linenum);
        }
        return errors;
    }

private:
    RobotSet set;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////
class EmptyGenState:public BaseState
{
public:
    EmptyGenState():BaseState(){robot = (Robot)0;}
    EmptyGenState(EmptyGenState& old):BaseState(old)
    {
        this->robot=old.robot;
    }

    Robot getRobot() {return robot;}
    void setRobot(Robot newRobot) {robot=newRobot;}
    QString getArgument() {return argument;}
    void setArgument(QString newArg) {argument=newArg;}
    void Print(QXmlStreamWriter * writer)
    {

        if(parameters.size()>0)
        {
            writer->writeTextElement("Parameters", parameters);
        }
        writer->writeTextElement("ROBOT", QString().fromStdString(ROBOT_TABLE[robot]));
        writer->writeTextElement("AddArg", argument);

    }
    std::string Print()
    {
        std::string x;
        x+="Name: ";
        x+=this->stateName.toStdString();
        x+="\nStateType: ";
        x+=STATE_TYPE_TABLE[this->getType()];
        if(parameters.size()>0)
        {
            x+="\nParameters: ";
            x+=this->parameters.toStdString();
        }
        x+="\nROBOT: ";
        x+=ROBOT_TABLE[robot];
        x+="\nArgument: ";
        x+=argument.toStdString();
        return x;
        x+="\nPositionX";
        x+=this->pos().x();
        x+="\nPositionY";
        x+=this->pos().y();
    }
    QStringList LoadFromXML(QXmlStreamReader * reader)
    {
        bool wasRobot = false;
        bool wasParam = false;
        bool wasArg = false;
        QStringList errors;
        while (!reader->atEnd())
        {
              reader->readNextStartElement();
              std::cout<<"EmptyGenState: "<<reader->name().toString().toStdString()<<std::endl;
              if(reader->name()=="State"&&reader->isEndElement())
              {
                  if(!wasRobot)
                  {
                      robot = (Robot)0;
                      char linenum[30];
                      sprintf(linenum,"; line: %lld", reader->lineNumber());
                      errors.push_back(QString("The Robot parameter was not defined for the EmptyGentate")+=linenum);
                  }
                  return errors;
              }
              else if (reader->name()=="ROBOT"&&reader->isStartElement())
              {
                  if(wasRobot)
                  {
                      char linenum[30];
                      sprintf(linenum,"; line: %lld", reader->lineNumber());
                      errors.push_back(QString("the Robot parameter has already been defined")+=linenum);
                  }
                  else
                  {
                      wasRobot=true;
                      int index = getRobotTable().indexOf(reader->readElementText());
                      if(index<ROBOTS_NUMBER && index>=0)
                      {
                          robot = (Robot)index;
                      }
                      else
                      {
                          char linenum[30];
                          sprintf(linenum,"; line: %lld", reader->lineNumber());
                          errors.push_back(QString("Out of bounds Robot")+=linenum);
                      }
                  }
              }
              else if (reader->name()=="AddArg"&&reader->isStartElement())
              {
                  if(wasArg)
                  {
                      char linenum[30];
                      sprintf(linenum,"; line: %lld", reader->lineNumber());
                      errors.push_back(QString("the Arguments parameter has already been defined")+=linenum);
                  }
                  else
                  {
                      argument=reader->readElementText();
                      wasArg=true;
                  }
              }
              else if (reader->name()=="Parameters")
              {
                  if(wasParam)
                  {
                      char linenum[30];
                      sprintf(linenum,"; line: %lld", reader->lineNumber());
                      errors.push_back(QString("the Parameters parameter has already been defined")+=linenum);
                  }
                  else
                  {
                      parameters=reader->readElementText();
                      wasParam=true;
                  }
              }
              else if(reader->name()=="PosX"&&reader->isStartElement())
              {
                  this->setPos(reader->readElementText().toDouble(), this->pos().y());
              }
              else if(reader->name()=="PosY"&&reader->isStartElement())
              {
                  this->setPos(this->pos().x(),reader->readElementText().toDouble());
              }
              else if (reader->name()!="transition"&&reader->isStartElement())
              {
                  char linenum[30];
                  sprintf(linenum,"; line: %lld", reader->lineNumber());
                  errors.push_back((QString("unexpected name while reading empty generator <State>: ")+=reader->name())+=linenum);
              }
        }
        if(!wasRobot)
        {
            robot = (Robot)0;
            char linenum[30];
            sprintf(linenum,"; line: %lld", reader->lineNumber());
            errors.push_back(QString("The Robot parameter was not defined for the EmptyGentate")+=linenum);
        }
        return errors;
    }
private:
    Robot robot;
    QString argument;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////
class GetSensorState:public BaseState
{
public:
    GetSensorState():BaseState(){}
    GetSensorState(GetSensorState& old):BaseState(old)
    {
        this->sensor=old.sensor;
    }

    Sensor getSensor() {return sensor;}
    void setSensor(Sensor newSensor) {sensor=newSensor;}

    void Print(QXmlStreamWriter * writer)
    {
        if(parameters.size()>0)
        {
            writer->writeTextElement("Parameters", parameters);
        }
        writer->writeTextElement("SENSOR", QString().fromStdString(SENSOR_TABLE[sensor]));
    }
    std::string Print()
    {
        std::string x;
        x+="Name: ";
        x+=this->stateName.toStdString();
        x+="\nStateType: ";
        x+=STATE_TYPE_TABLE[this->getType()];
        if(parameters.size()>0)
        {
            x+="\nParameters: ";
            x+=this->parameters.toStdString();
        }
        x+="\nSENSOR: ";
        x+=SENSOR_TABLE[sensor];
        return x;
    }
    QStringList LoadFromXML(QXmlStreamReader * reader)
    {
        bool wasParam = false;
        bool wasSensor = false;
        QStringList errors;
        while (!reader->atEnd())
        {
              reader->readNextStartElement();
              std::cout<<"GetSensorState: "<<reader->name().toString().toStdString()<<std::endl;
              if(reader->name()=="State"&&reader->isEndElement())
              {
                  if(!wasSensor)
                  {
                      sensor = (Sensor)0;
                      char linenum[30];
                      sprintf(linenum,"; line: %lld", reader->lineNumber());
                      errors.push_back(QString("The Sensor parameter was not defined for the GetSensorState")+=linenum);
                  }
                  return errors;
              }
              else if (reader->name()=="Sensor"&&reader->isStartElement())
              {
                  if(wasSensor)
                  {
                      char linenum[30];
                      sprintf(linenum,"; line: %lld", reader->lineNumber());
                      errors.push_back(QString("the Sensor parameter has already been defined")+=linenum);
                  }
                  else
                  {
                      wasSensor=true;
                      int index = getSensorTable().indexOf(reader->readElementText());
                      if(index<SENSORS_NUMBER && index>=0)
                      {
                          sensor = (Sensor)index;
                      }
                      else
                      {
                          char linenum[30];
                          sprintf(linenum,"; line: %lld", reader->lineNumber());
                          errors.push_back(QString("Out of bounds Sensor")+=linenum);
                      }
                  }
              }
              else if (reader->name()=="Parameters"&&reader->isStartElement())
              {
                  if(wasParam)
                  {
                      char linenum[30];
                      sprintf(linenum,"; line: %lld", reader->lineNumber());
                      errors.push_back(QString("the Parameters parameter has already been defined")+=linenum);
                  }
                  else
                  {
                      parameters=reader->readElementText();
                      wasParam=true;
                  }
              }
              else if(reader->name()=="PosX"&&reader->isStartElement())
              {
                  this->setPos(reader->readElementText().toDouble(), this->pos().y());
              }
              else if(reader->name()=="PosY"&&reader->isStartElement())
              {
                  this->setPos(this->pos().x(),reader->readElementText().toDouble());
              }
              else if (reader->name()!="transition"&&reader->isStartElement())
              {
                  char linenum[30];
                  sprintf(linenum,"; line: %lld", reader->lineNumber());
                  errors.push_back((QString("unexpected name while reading get sensor <State>: ")+=reader->name())+=linenum);
              }
        }
        if(!wasSensor)
        {
            sensor = (Sensor)0;
            char linenum[30];
            sprintf(linenum,"; line: %lld", reader->lineNumber());
            errors.push_back(QString("The Sensor parameter was not defined for the GetSensorState")+=linenum);
        }
        return errors;
    }
private:
    Sensor sensor;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////
class InitiateSensorState:public BaseState
{
public:
    InitiateSensorState():BaseState(){}
    InitiateSensorState(InitiateSensorState& old):BaseState(old)
    {
        this->sensor=old.sensor;
    }

    Sensor getSensor() {return sensor;}
    void setSensor(Sensor newSensor) {sensor=newSensor;}

    void Print(QXmlStreamWriter * writer)
    {
        if(parameters.size()>0)
        {
            writer->writeTextElement("Parameters", parameters);
        }
        writer->writeTextElement("SENSOR", QString().fromStdString(SENSOR_TABLE[sensor]));
    }
    std::string Print()
    {
        std::string x;
        x+="Name: ";
        x+=this->stateName.toStdString();
        x+="\nStateType: ";
        x+=STATE_TYPE_TABLE[this->getType()];
        if(parameters.size()>0)
        {
            x+="\nParameters: ";
            x+=this->parameters.toStdString();
        }
        x+="\nSENSOR: ";
        x+=SENSOR_TABLE[sensor];
        return x;
    }
    QStringList LoadFromXML(QXmlStreamReader * reader)
    {
        bool wasParam = false;
        bool wasSensor = false;
        QStringList errors;
        while (!reader->atEnd())
        {
              reader->readNextStartElement();
              std::cout<<"InitiateSensorState: "<<reader->name().toString().toStdString()<<std::endl;
              if(reader->name()=="State"&&reader->isEndElement())
              {
                  if(!wasSensor)
                  {
                      sensor = (Sensor)0;
                      char linenum[30];
                      sprintf(linenum,"; line: %lld", reader->lineNumber());
                      errors.push_back(QString("The Sensor parameter was not defined for the InitaiteSensorState")+=linenum);
                  }
                  return errors;
              }
              else if (reader->name()=="Sensor"&&reader->isStartElement())
              {
                  if(wasSensor)
                  {
                      char linenum[30];
                      sprintf(linenum,"; line: %lld", reader->lineNumber());
                      errors.push_back(QString("the Sensor parameter has already been defined")+=linenum);
                  }
                  else
                  {
                      wasSensor=true;
                      int index = getSensorTable().indexOf(reader->readElementText());
                      if(index<SENSORS_NUMBER && index>=0)
                      {
                          sensor = (Sensor)index;
                      }
                      else
                      {
                          char linenum[30];
                          sprintf(linenum,"; line: %lld", reader->lineNumber());
                          errors.push_back(QString("Out of bounds Sensor")+=linenum);
                      }
                  }
              }
              else if (reader->name()=="Parameters"&&reader->isStartElement())
              {
                  if(wasParam)
                  {
                      char linenum[30];
                      sprintf(linenum,"; line: %lld", reader->lineNumber());
                      errors.push_back(QString("the Parameters parameter has already been defined")+=linenum);
                  }
                  else
                  {
                      parameters=reader->readElementText();
                      wasParam=true;
                  }
              }
              else if(reader->name()=="PosX"&&reader->isStartElement())
              {
                  this->setPos(reader->readElementText().toDouble(), this->pos().y());
              }
              else if(reader->name()=="PosY"&&reader->isStartElement())
              {
                  this->setPos(this->pos().x(),reader->readElementText().toDouble());
              }
              else if (reader->name()!="transition"&&reader->isStartElement())
              {
                  char linenum[30];
                  sprintf(linenum,"; line: %lld", reader->lineNumber());
                  errors.push_back((QString("unexpected name while reading initiate sensor <State>: ")+=reader->name())+=linenum);
              }
        }
        if(!wasSensor)
        {
            sensor = (Sensor)0;
            char linenum[30];
            sprintf(linenum,"; line: %lld", reader->lineNumber());
            errors.push_back(QString("The Sensor parameter was not defined for the InitaiteSensorState")+=linenum);
        }
        return errors;
    }
private:
    Sensor sensor;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////
class RunGenState:public BaseState
{
public:
    RunGenState():BaseState(){coords = new Coordinates();}
    RunGenState(RunGenState& old):BaseState(old)
    {
        this->robot=old.robot;
        this->genType=old.genType;
        this->filePath=old.filePath;
        this->genArgs=old.genArgs;
        this->coords=new Coordinates(*(old.coords));
        this->speech=old.speech;
    }

    Robot getRobot() {return robot;}
    void setRobot(Robot newRobot) {robot=newRobot;}
    GeneratorType getGenType() {return genType;}
    void setGenType(GeneratorType newGenType) {genType=newGenType;}
    Coordinates* getCoords() {return coords;}
    void setCoords (Coordinates * newCoords) {coords = newCoords;}
    QString getSpeech() {return speech;}
    void setSpeech(QString newSpeech) {speech = newSpeech;}
    QString getArgs(){return genArgs;}
    void setArgs(QString newGenArgs){genArgs=newGenArgs;}
    QString getFilePath() {return filePath;}
    void setFilePath(QString newPath) {filePath=newPath;}

    void Print(QXmlStreamWriter * writer)
    {
        writer->writeTextElement("ROBOT", QString().fromStdString(ROBOT_TABLE[robot]));
        writer->writeTextElement("ECPGeneratorType", QString().fromStdString(GENERATOR_TYPE_TABLE[genType]));
        if(this->speech.size()>0)
        {
            writer->writeTextElement("Speech", speech);
        }
        if(this->genArgs.size()>0)
        {
            writer->writeTextElement("AddArg", genArgs);
        }
        writer->writeTextElement("TrajectoryFilePath", getFilePath());
        if(this->coords->getPoses().size()==0)return;
        coords->Print(writer);
    }

    std::string Print()
    {
        std::string x;
        x+="Name: ";
        x+=this->stateName.toStdString();
        x+="\nStateType: ";
        x+=STATE_TYPE_TABLE[this->getType()];
        if(parameters.size()>0)
        {
            x+="\nParameters: ";
            x+=this->parameters.toStdString();
        }
        x+="\nROBOT: ";
        x+=ROBOT_TABLE[robot];
        x+="\nGENERATOR: ";
        x+=GENERATOR_TYPE_TABLE[genType];
        if(this->speech.size()>0)
        {
            x+="Speech: ";
            x+=this->speech.toStdString();
        }
        if(this->genArgs.size()>0)
        {
            x+="\nGenArgs: ";
            x+=this->genArgs.toStdString();
        }
        x+="\nFilePath:";
        x+=getFilePath().toStdString();
        x+=coords->Print();
        return x;
    }
    QStringList LoadFromXML(QXmlStreamReader * reader)
    {
        bool wasParam=false;
        bool wasSpeech=false;
        bool wasArgs=false;
        bool wasRobot=false;
        bool wasTrj=false;
        bool wasGenType=false;
        bool wasFile=false;
        QStringList errors;
        while (!reader->atEnd())
        {
              reader->readNextStartElement();
              std::cout<<"RunGenState: "<<reader->name().toString().toStdString()<<std::endl;
              if(reader->name()=="State"&&reader->isEndElement())
              {
                  if(!wasRobot)
                  {
                      robot = (Robot)0;
                      char linenum[30];
                      sprintf(linenum,"; line: %lld", reader->lineNumber());
                      errors.push_back(QString("The Robot parameter was not defined for the RunGeneratorState")+=linenum);
                  }
                  if(!wasGenType)
                  {
                      genType = (GeneratorType)0;
                      char linenum[30];
                      sprintf(linenum,"; line: %lld", reader->lineNumber());
                      errors.push_back(QString("The GeneratorType parameter was not defined for the RunGeneratorState")+=linenum);
                  }
                  return errors;
              }
              else if (reader->name()=="ROBOT"&&reader->isStartElement())
              {
                  if(wasRobot)
                  {
                      char linenum[30];
                      sprintf(linenum,"; line: %lld", reader->lineNumber());
                      errors.push_back(QString("the Robot parameter has already been defined")+=linenum);
                  }
                  else
                  {
                      wasRobot=true;
                      int index = getRobotTable().indexOf(reader->readElementText());
                      if(index<ROBOTS_NUMBER && index>=0)
                      {
                          robot = (Robot)index;
                      }
                      else
                      {
                          robot = (Robot)0;
                          char linenum[30];
                          sprintf(linenum,"; line: %lld", reader->lineNumber());
                          errors.push_back(QString("Out of bounds Robot")+=linenum);
                      }
                  }
              }
              else if (reader->name()=="TrajectoryFilePath"&&reader->isStartElement())
              {
                  if(wasFile)
                  {
                      char linenum[30];
                      sprintf(linenum,"; line: %lld", reader->lineNumber());
                      errors.push_back(QString("the TrajectoryFilePath parameter has already been defined")+=linenum);
                  }
                  else
                  {
                      setFilePath(reader->readElementText());
                      wasFile=true;
                  }
              }
              else if (reader->name()=="Parameters"&&reader->isStartElement())
              {
                  if(wasParam)
                  {
                      char linenum[30];
                      sprintf(linenum,"; line: %lld", reader->lineNumber());
                      errors.push_back(QString("the Parameters parameter has already been defined")+=linenum);
                  }
                  else
                  {
                      parameters=reader->readElementText();
                      wasParam=true;
                  }
              }
              else if (reader->name()=="Speech"&&reader->isStartElement())
              {
                  if(wasSpeech)
                  {
                      char linenum[30];
                      sprintf(linenum,"; line: %lld", reader->lineNumber());
                      errors.push_back(QString("the Speech parameter has already been defined")+=linenum);
                  }
                  else
                  {
                      speech=reader->readElementText();
                      wasSpeech=true;
                  }
              }
              else if (reader->name()=="AddArg"&&reader->isStartElement())
              {
                  if(wasArgs)
                  {
                      char linenum[30];
                      sprintf(linenum,"; line: %lld", reader->lineNumber());
                      errors.push_back(QString("the Arguments parameter has already been defined")+=linenum);
                  }
                  else
                  {
                      genArgs=reader->readElementText();
                      wasArgs=true;
                  }
              }
              else if(reader->name()=="ECPGeneratorType"&&reader->isStartElement())
              {
                  if(wasGenType)
                  {
                      char linenum[30];
                      sprintf(linenum,"; line: %lld", reader->lineNumber());
                      errors.push_back(QString("the Generator type parameter has already been defined")+=linenum);
                  }
                  else
                  {
                      int index = getGeneratorTypeTable().indexOf(reader->readElementText());
                      if(index<GENERATORS_NUMBER && index>=0)
                      {
                          wasGenType=true;
                          genType=(GeneratorType)index;
                      }
                      else
                      {
                          genType=(GeneratorType)0;
                          char linenum[30];
                          sprintf(linenum,"; line: %lld", reader->lineNumber());
                          errors.push_back(QString("Out of bounds GeneratorType")+=linenum);
                      }
                  }
              }
              else if(reader->name()=="Trajectory"&&reader->isStartElement())
              {
                  if(wasTrj)
                  {
                      char linenum[30];
                      sprintf(linenum,"; line: %lld", reader->lineNumber());
                      errors.push_back(QString("the Trajectory parameter has already been defined")+=linenum);
                  }
                  else
                  {
                      wasTrj=true;
                      errors+=coords->LoadFromXML(reader);
                  }
              }
              else if(reader->name()=="PosX"&&reader->isStartElement())
              {
                  this->setPos(reader->readElementText().toDouble(), this->pos().y());
              }
              else if(reader->name()=="PosY"&&reader->isStartElement())
              {
                  this->setPos(this->pos().x(),reader->readElementText().toDouble());
              }
              else if (reader->name()!="transition"&&reader->isStartElement())
              {
                  char linenum[30];
                  sprintf(linenum,"; line: %lld", reader->lineNumber());
                  errors.push_back((QString("unexpected name while reading run generator <State>: ")+=reader->name())+=linenum);
              }
        }
        if(!wasRobot)
        {
            robot = (Robot)0;
            char linenum[30];
            sprintf(linenum,"; line: %lld", reader->lineNumber());
            errors.push_back(QString("The Robot parameter was not defined for the RunGeneratorState")+=linenum);
        }
        if(!wasGenType)
        {
            genType = (GeneratorType)0;
            char linenum[30];
            sprintf(linenum,"; line: %lld", reader->lineNumber());
            errors.push_back(QString("The GeneratorType parameter was not defined for the RunGeneratorState")+=linenum);
        }
        return errors;
    }

private:
    QString filePath;
    Robot robot;
    GeneratorType genType;
    Coordinates * coords;
    QString genArgs;
    QString speech;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////
class StopGenState:public BaseState
{
public:
    StopGenState():BaseState(){}
    StopGenState(StopGenState& old):BaseState(old)
    {
        this->set=old.set;
    }

    RobotSet getSet() {return set;}
    void setSet(RobotSet newSet) {set=newSet;}

    void Print(QXmlStreamWriter * writer)
    {

        if(parameters.size()>0)
        {
            writer->writeTextElement("Parameters", parameters);
            //x+=this->parameters.toStdString();
        }
        set.Print();
    }
    std::string Print()
    {
        std::string x;
        x+="Name: ";
        x+=this->stateName.toStdString();
        x+="\nStateType: ";
        x+=STATE_TYPE_TABLE[this->getType()];
        if(parameters.size()>0)
        {
            x+="\nParameters: ";
            x+=this->parameters.toStdString();
        }
        x+=set.Print();
        return x;
    }
    QStringList LoadFromXML(QXmlStreamReader * reader)
    {
        bool wasSet = false;
        bool wasParam = false;
        QStringList errors;
        while (!reader->atEnd())
        {
              reader->readNextStartElement();
              std::cout<<"StopGenState: "<<reader->name().toString().toStdString()<<std::endl;
              if(reader->name()=="State"&&reader->isEndElement())
              {
                  if(!wasSet)
                  {
                      char linenum[30];
                      sprintf(linenum,"; line: %lld", reader->lineNumber());
                      errors.push_back(QString("The RobotSet parameter was not defined for the StopGeneratorState")+=linenum);
                  }
                  else if(set.second.size()>0)
                  {
                      char linenum[30];
                      sprintf(linenum,"; line: %lld", reader->lineNumber());
                      errors.push_back(QString("SecondSet defined for stopGenState")+=linenum);
                  }
                  return errors;
              }
              else if(reader->name()=="SetOfRobots"&&reader->isStartElement())
              {
                  if(wasSet)
                  {
                      char linenum[30];
                      sprintf(linenum,"; line: %lld", reader->lineNumber());
                      errors.push_back(QString("the RobotSet parameter has already been defined")+=linenum);
                  }
                  else
                  {
                      errors+=set.LoadFromXML(reader);
                      wasSet=true;
                  }
              }
              else if(reader->name()=="PosX"&&reader->isStartElement())
              {
                  this->setPos(reader->readElementText().toDouble(), this->pos().y());
              }
              else if(reader->name()=="PosY"&&reader->isStartElement())
              {
                  this->setPos(this->pos().x(),reader->readElementText().toDouble());
              }
              else if (reader->name()=="Parameters"&&reader->isStartElement())
              {
                  if(wasParam)
                  {
                      char linenum[30];
                      sprintf(linenum,"; line: %lld", reader->lineNumber());
                      errors.push_back(QString("the Parameter parameter has already been defined")+=linenum);
                  }
                  else
                  {
                      parameters=reader->readElementText();
                      wasParam=true;
                  }
              }
              else if (reader->name()!="transition"&&reader->isStartElement())
              {
                  char linenum[30];
                  sprintf(linenum,"; line: %lld", reader->lineNumber());
                  errors.push_back((QString("unexpected name while reading stop generator <State>: ")+=reader->name())+=linenum);
              }

        }
        if(!wasSet)
        {
            char linenum[30];
            sprintf(linenum,"; line: %lld", reader->lineNumber());
            errors.push_back(QString("The RobotSet parameter was not defined for the StopGeneratorState")+=linenum);
        }
        else if(set.second.size()>0)
        {
            char linenum[30];
            sprintf(linenum,"; line: %lld", reader->lineNumber());
            errors.push_back(QString("SecondSet defined for stopGenState")+=linenum);
        }
        return errors;
    }
private:
    RobotSet set;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

class sysInitState:public BaseState
{
public:
    sysInitState():BaseState(){transmitter=(Transmitter)-1;}
    sysInitState(sysInitState& old):BaseState(old)
    {
        this->inits=old.inits;
        this->transmitter=old.transmitter;
        this->sensors=old.sensors;
    }

    std::vector<genInit> getInits() {return inits;}
    void setInits (std::vector<genInit> newInits) {inits=newInits;}
    Transmitter getTransmitter() {return transmitter;}
    void setTransmitter(Transmitter newTrans) {transmitter=newTrans;}
    std::vector<Sensor> getSensors() {return sensors;}
    void setSensors(std::vector<Sensor> newSensors) {sensors=newSensors;}

    void Print(QXmlStreamWriter * writer)
    {
        if(parameters.size()>0)
        {
            writer->writeTextElement("Parameters", parameters);
        }
        writer->writeStartElement("taskInit");
        if(transmitter<TRANSMITTERS_NUMBER||sensors.size()>0)
        {
            writer->writeStartElement("mp");
            if(transmitter<TRANSMITTERS_NUMBER&&transmitter>=0)
            {
                writer->writeTextElement("Transmitter", QString().fromStdString(TRANSMITTER_TABLE[transmitter]));
            }
            for(std::vector<Sensor>::iterator it = sensors.begin();it!=sensors.end();it++)
            {
                writer->writeTextElement("Sensor", QString().fromStdString(SENSOR_TABLE[(*it)]));
            }
            writer->writeEndElement();

        }
        if(inits.size()>0)
        {
            for(std::vector<genInit>::iterator it = inits.begin();it!=inits.end();it++)
            {
                (*it).Print(writer);
            }
        }


        writer->writeEndElement();

    }
    std::string Print()
    {
        std::string x;
        x+="Name: ";
        x+=this->stateName.toStdString();
        x+="\nStateType: ";
        x+=STATE_TYPE_TABLE[this->getType()];
        if(parameters.size()>0)
        {
            x+="\nParameters: ";
            x+=this->parameters.toStdString();
        }
        if(transmitter<TRANSMITTERS_NUMBER||sensors.size()>0)
        {
            x+="\nMP";
            if(transmitter<TRANSMITTERS_NUMBER)
            {
                x+="\ntransmitter: ";
                x+=TRANSMITTER_TABLE[transmitter];
            }
            for(std::vector<Sensor>::iterator it = sensors.begin();it!=sensors.end();it++)
            {
                x+="\nSENSOR: ";
                x+=SENSOR_TABLE[(*it)];
            }
        }
        if(inits.size()>0)
        {
            for(std::vector<genInit>::iterator it = inits.begin();it!=inits.end();it++)
            {
                x+=(*it).Print();
            }
        }

        return x;
    }
    QStringList LoadFromXML(QXmlStreamReader * reader)
    {
        bool wasParameters = false;
        bool wasTransmitter = false;
        bool inMP = false;
        QStringList errors;
        int index;
        while (!reader->atEnd())
        {
            if(reader->name()=="State"&&reader->isEndElement())
            {
                return errors;
            }
              reader->readNextStartElement();
              std::cout<<"SysIniState: "<<reader->name().toString().toStdString()<<std::endl;
              if(reader->name()=="State"&&reader->isEndElement())
              {
                  return errors;
              }
              else if(reader->name()=="PosX"&&reader->isStartElement())
              {
                  this->setPos(reader->readElementText().toDouble(), this->pos().y());
              }
              else if(reader->name()=="PosY"&&reader->isStartElement())
              {
                  this->setPos(this->pos().x(),reader->readElementText().toDouble());
              }
              else if (reader->name()=="Parameters"&&reader->isStartElement())
              {
                  if(wasParameters)
                  {
                      char linenum[30];
                      sprintf(linenum,"; line: %lld", reader->lineNumber());
                      errors.push_back(QString("the Parameters parameter has already been defined")+=linenum);
                  }
                  else
                  {
                      parameters=reader->readElementText();
                      wasParameters=true;
                  }
              }
              else if (reader->name()=="mp")
              {
                  if(reader->isStartElement())
                  {
                      inMP=true;
                  }
                  else
                  {
                      inMP=false;
                  }
              }
              else if (reader->name()=="Transmitter"&&reader->isStartElement())
              {
                  if(!inMP)
                  {
                      char linenum[30];
                      sprintf(linenum,"; line: %lld", reader->lineNumber());
                      errors.push_back(QString("Transmitter defined in system initialization state outside of MP")+=linenum);
                  }
                  if(wasTransmitter)
                  {
                      char linenum[30];
                      sprintf(linenum,"; line: %lld", reader->lineNumber());
                      errors.push_back(QString("the Transmitter parameter has already been defined")+=linenum);
                  }
                  else
                  {
                      index = getTransmitterTable().indexOf(reader->readElementText());
                      if(index<TRANSMITTERS_NUMBER&&index>=0)
                      {
                          transmitter=(Transmitter)index;
                          wasTransmitter=true;
                      }
                      else
                      {
                          char linenum[30];
                          sprintf(linenum,"; line: %lld", reader->lineNumber());
                          errors.push_back(QString("Out of bounds Transmitter")+=linenum);
                      }
                  }
              }
              else if (reader->name()=="Sensor"&&reader->isStartElement())
              {
                  if(!inMP)
                  {
                      char linenum[30];
                      sprintf(linenum,"; line: %lld", reader->lineNumber());
                      errors.push_back(QString("Sensor defined in system initialization state outside of MP")+=linenum);
                  }
                  index = getSensorTable().indexOf(reader->readElementText());
                  if(index<SENSORS_NUMBER && index>=0)
                  {
                      sensors.push_back((Sensor)index);
                  }
                  else
                  {
                      char linenum[30];
                      sprintf(linenum,"; line: %lld", reader->lineNumber());
                      errors.push_back(QString("Out of bounds Sensor")+=linenum);
                  }
              }
              else if (reader->name()=="ecp"&&reader->isStartElement())
              {
                  genInit tmp;
                  errors+=tmp.LoadFromXML(reader);
                  bool mark = true;
                  if(inits.size()>0)
                  {
                      foreach(genInit init, inits)
                      {
                          if(init.robot==tmp.robot)
                          {
                              char linenum[30];
                              sprintf(linenum,"; line: %lld", reader->lineNumber());
                              errors.push_back(QString("Robot in new init is the same as in one of the previous")+=linenum);
                          }
                      }
                  }
                  if(mark)
                  {
                    inits.push_back(tmp);
                  }
              }
              else if (reader->name()!="transition"&& reader->name()!="taskInit"&&reader->isStartElement())
              {
                  char linenum[30];
                  sprintf(linenum,"; line: %lld", reader->lineNumber());
                  errors.push_back((QString("unexpected name while reading system initialization <State>: ")+=reader->name())+=linenum);
              }
        }
        return errors;
    }
private:
    std::vector<genInit> inits;//wektor, bo w jednym stanie inicjalizacji moze sie znajdowac wiele robotów
    Transmitter transmitter;
    std::vector<Sensor> sensors;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////
class WaitState:public BaseState
{
public:
    WaitState():BaseState(){Timespan=0;}
    WaitState(WaitState& old):BaseState(old)
    {
        this->Timespan=old.Timespan;
    }

    long long int getTimespan() {return Timespan;}
    void setTimespan(long long int newTimeSpan){Timespan = newTimeSpan;}

    void Print(QXmlStreamWriter * writer)
    {
        if(parameters.size()>0)
        {
            writer->writeTextElement("Parameters", parameters);
        }
        char tim[15];
        sprintf (tim, "%lld", Timespan);
        writer->writeTextElement("TimeSpan", QString().fromStdString(tim));
    }

    std::string Print()
    {
        std::string x;
        x+="Name: ";
        x+=this->stateName.toStdString();
        x+="\nStateType: ";
        x+=STATE_TYPE_TABLE[this->getType()];
        if(parameters.size()>0)
        {
            x+="\nParameters: ";
            x+=this->parameters.toStdString();
        }
        x+="\nTimespan: ";
        char buf[20];
        sprintf(buf,"%lld",Timespan);
        x+=buf;
        return x;
    }
    QStringList LoadFromXML(QXmlStreamReader * reader)
    {
        bool wasTimespan = false;
        bool wasParameters = false;
        QStringList errors;
        while (!reader->atEnd())
        {
              reader->readNextStartElement();
              std::cout<<"WaitState: "<<reader->name().toString().toStdString()<<std::endl;
              if(reader->name()=="State"&&reader->isEndElement())
              {
                  if(!wasTimespan)
                  {
                      Timespan=0;
                      char linenum[30];
                      sprintf(linenum,"; line: %lld", reader->lineNumber());
                      errors.push_back(QString("The Timespan parameter was not defined for the WaitState")+=linenum);
                  }
                  return errors;
              }
              else if(reader->name()=="PosX"&&reader->isStartElement())
              {
                  this->setPos(reader->readElementText().toDouble(), this->pos().y());
              }
              else if(reader->name()=="PosY"&&reader->isStartElement())
              {
                  this->setPos(this->pos().x(),reader->readElementText().toDouble());
              }
              else if (reader->name()=="Parameters"&&reader->isStartElement())
              {
                  if(wasParameters)
                  {
                      char linenum[30];
                      sprintf(linenum,"; line: %lld", reader->lineNumber());
                      errors.push_back(QString("the Parameters parameter has already been defined")+=linenum);
                  }
                  else
                  {
                      parameters=reader->readElementText();
                      wasParameters=true;
                  }
              }
              else if (reader->name()=="TimeSpan"&&reader->isStartElement())
              {
                  if(wasTimespan)
                  {
                      char linenum[30];
                      sprintf(linenum,"; line: %lld", reader->lineNumber());
                      errors.push_back(QString("the Timespan parameter has already been defined")+=linenum);
                  }
                  else
                  {
                      Timespan=reader->readElementText().toULongLong();
                      wasTimespan=true;
                  }
              }
              else if (reader->name()!="transition"&&reader->isStartElement())
              {
                  char linenum[30];
                  sprintf(linenum,"; line: %lld", reader->lineNumber());
                  errors.push_back((QString("unexpected name while reading wait <State>: ")+=reader->name())+=linenum);
              }

        }
        if(!wasTimespan)
        {
            Timespan=0;
            char linenum[30];
            sprintf(linenum,"; line: %lld", reader->lineNumber());
            errors.push_back(QString("The Timespan parameter was not defined for the WaitState")+=linenum);
        }
        return errors;
    }
private:
    unsigned long long int Timespan;
};




#endif // BASESTATE_H
