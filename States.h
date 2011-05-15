#include "globals.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include "RobotSet.h"
#include "Coordinates.h"

#include <stdio.h>
#include <stdlib.h>

#include "baseState.h"
class QXmlStreamWriter;
class QXmlStreamReader;
#include <QtGui>


#ifndef BASESTATE_H
#define BASESTATE_H
/*
class BaseState// : public DiagramItem
{
public:



private:


};
*/
//TODO change print to xml functions to print good robots

//TODO flags when reading about what already was read
//check in the ENUM structs if it's not outside of bonds

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
              std::cout<<reader->name().toString().toStdString()<<std::endl;
              if(reader->name()=="State"&&reader->isEndElement())
              {
                  return errors;
              }
              else if(reader->name()=="PosX")
              {
                  this->setPos(reader->readElementText().toDouble(), this->pos().y());
              }
              else if(reader->name()=="PosY")
              {
                  this->setPos(this->pos().x(),reader->readElementText().toDouble());
              }
              else
              {
                  //error - unexpeected node
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
        writer->writeStartElement("SetOfRobots");
        writer->writeStartElement("FirstSet");
        for(std::vector<Robot>::iterator it = set.first.begin();it!=set.first.end();it++)
        {
            writer->writeTextElement("ROBOT", QString().fromStdString(ROBOT_TABLE[(*it)]));
        }
        writer->writeEndElement();
        writer->writeStartElement("SecSet");
        for(std::vector<Robot>::iterator it = set.second.begin();it!=set.second.end();it++)
        {
            writer->writeTextElement("ROBOT", QString().fromStdString(ROBOT_TABLE[(*it)]));
        }//*/
        writer->writeEndElement();
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
        x+="\nFIRST SET:";
        for(std::vector<Robot>::iterator it = set.first.begin();it!=set.first.end();it++)
        {
            x+="\nROBOT: ";
            x+=ROBOT_TABLE[(*it)];
        }
        x+="\nSECOND SET:";
        for(std::vector<Robot>::iterator it = set.second.begin();it!=set.second.end();it++)
        {
            x+="\nROBOT: ";
            x+=ROBOT_TABLE[(*it)];
        }
        return x;
    }
    QStringList LoadFromXML(QXmlStreamReader * reader)
    {
        bool wasSet = false;
        bool wasParam = false;
        std::cout<<"LOADING EGFS"<<std::endl;
        QStringList errors;
        while (!reader->atEnd())
        {
              reader->readNextStartElement();
              std::cout<<reader->name().toString().toStdString()<<std::endl;
              if(reader->name()=="State"&&reader->isEndElement())
              {
                  return errors;
              }
              else if(reader->name()=="SetOfRobots")
              {
                  if(wasSet)
                  {
                      //error
                  }
                  else
                  {
                      set.LoadFromXML(reader);
                      wasSet=true;
                  }
              }
              else if(reader->name()=="PosX")
              {
                  this->setPos(reader->readElementText().toDouble(), this->pos().y());
              }
              else if(reader->name()=="PosY")
              {
                  this->setPos(this->pos().x(),reader->readElementText().toDouble());
              }
              else if (reader->name()=="Parameters")
              {
                  if(wasParam)
                  {
                      //error
                  }
                  else
                  {
                      parameters=reader->readElementText();
                      wasParam=true;
                  }
              }
              else
              {
                  //unknown parameter
              }

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
        std::cout<<"LOADING EG"<<std::endl;
        QStringList errors;
        while (!reader->atEnd())
        {
              reader->readNextStartElement();
              std::cout<<reader->name().toString().toStdString()<<std::endl;
              if(reader->name()=="State"&&reader->isEndElement())
              {
                  return errors;
              }
              else if (reader->name()=="ROBOT"&&reader->isStartElement())
              {
                  if(wasRobot)
                  {
                      //error
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
                          //error out of bounds robot
                      }
                  }
              }
              else if (reader->name()=="AddArg")
              {
                  if(wasArg)
                  {
                      //error
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
                      //error
                  }
                  else
                  {
                      parameters=reader->readElementText();
                      wasParam=true;
                  }
              }
              else
              {
                  //error - unexpected node
              }
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
        std::cout<<"LOADING GS"<<std::endl;
        QStringList errors;
        while (!reader->atEnd())
        {
              reader->readNextStartElement();
              std::cout<<reader->name().toString().toStdString()<<std::endl;
              if(reader->name()=="State"&&reader->isEndElement())
              {
                  return errors;
              }
              else if (reader->name()=="Sensor")
              {
                  if(wasSensor)
                  {
                      //error
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
                          //error out of bounds sensor
                      }
                  }
              }
              else if (reader->name()=="Parameters")
              {
                  if(wasParam)
                  {
                      //error
                  }
                  else
                  {
                      parameters=reader->readElementText();
                      wasParam=true;
                  }
              }
              else
              {
                  //error - unexpected node
              }
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
        std::cout<<"LOADING IS"<<std::endl;
        QStringList errors;
        while (!reader->atEnd())
        {
              reader->readNextStartElement();
              std::cout<<reader->name().toString().toStdString()<<std::endl;
              if(reader->name()=="State"&&reader->isEndElement())
              {
                  return errors;
              }
              else if (reader->name()=="Sensor")
              {
                  if(wasSensor)
                  {
                      //error
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
                          //error out of bounds sensor
                      }
                  }
              }
              else if (reader->name()=="Parameters")
              {
                  if(wasParam)
                  {
                      //error
                  }
                  else
                  {
                      parameters=reader->readElementText();
                      wasParam=true;
                  }
              }
              else
              {
                  //error - unexpected node
              }
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
        writer->writeStartElement("Trajectory");
        writer->writeAttribute(QString("coordinateType"), QString().fromStdString(COORD_TYPE_TABLE[coords->getCoordType()]));
        writer->writeAttribute(QString("motionType"), QString().fromStdString(MOTION_TYPE_TABLE[coords->getMotionType()]));
        std::vector<Pose *>::iterator it;
        char  w[12];
        std::string x;
        std::vector<Pose *> posesCopy = this->coords->getPoses();
        for(it = posesCopy.begin(); it!=posesCopy.end();it++)
        {
            writer->writeStartElement("Pose");
            std::vector<double> tmp = (*(it))->getA();
            for (int i=0;i<tmp.size();i++)
            {
                sprintf(w, "%lf", tmp[i]);
                x+=w;
                x+=" ";
            }
            writer->writeTextElement("Accelerations", QString().fromStdString(x));
            x.clear();
            tmp = (*(it))->getV();
            for (int i=0;i<tmp.size();i++)
            {
                sprintf(w, "%lf", tmp[i]);
                x+=w;
                x+=" ";
            }
            writer->writeTextElement("Velocities", QString().fromStdString(x));
            x.clear();
            tmp = (*(it))->getC();
            for (int i=0;i<tmp.size();i++)
            {
                sprintf(w, "%lf", tmp[i]);
                x+=w;
                x+=" ";
            }
            writer->writeTextElement("Coordinates", QString().fromStdString(x));
            x.clear();
            writer->writeEndElement();
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
        x+="\nMotion Type:";
        x+=MOTION_TYPE_TABLE[coords->getMotionType()];
        x+="\nCoord Type:";
        x+=COORD_TYPE_TABLE[coords->getCoordType()];
        std::vector<Pose *>::iterator it;
        char  w[12];
        std::vector<Pose *> posesCopy = this->coords->getPoses();
        for(it = posesCopy.begin(); it!=posesCopy.end();it++)
        {
            std::vector<double> tmp = (*(it))->getA();
            x+="\nPOSE:";
            x+="\nAccelerations: ";
            for (int i=0;i<tmp.size();i++)
            {
                sprintf(w, "%lf", tmp[i]);
                x+=w;
                x+=" ";
            }
            tmp = (*(it))->getV();
            x+="\nVelocities: ";
            for (int i=0;i<tmp.size();i++)
            {
                sprintf(w, "%lf", tmp[i]);
                x+=w;
                x+=" ";
            }
            tmp = (*(it))->getC();
            x+="\nCoords: ";
            for (int i=0;i<tmp.size();i++)
            {
                sprintf(w, "%lf", tmp[i]);
                x+=w;
                x+=" ";
            }
        }
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
        std::cout<<"LOADING RGS"<<std::endl;
        QStringList errors;
        while (!reader->atEnd())
        {
              reader->readNextStartElement();
              std::cout<<reader->name().toString().toStdString()<<std::endl;
              if(reader->name()=="State"&&reader->isEndElement())
              {
                  std::cout<<"TEST "<<stateName.toStdString()<< " poses: "<<coords->getPoses().size()<<std::endl;
                  return errors;
              }
              else if (reader->name()=="ROBOT")
              {
                  if(wasRobot)
                  {
                      //error
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
                          //error out of bounds sensor
                      }
                  }
              }
              else if (reader->name()=="TrajectoryFilePath")
              {
                  if(wasFile)
                  {
                      //error
                  }
                  else
                  {
                      setFilePath(reader->readElementText());
                      wasFile=true;
                  }
              }
              else if (reader->name()=="Parameters")
              {
                  if(wasParam)
                  {
                      //error
                  }
                  else
                  {
                      parameters=reader->readElementText();
                      wasParam=true;
                  }
              }
              else if (reader->name()=="Speech")
              {
                  if(wasSpeech)
                  {
                      //error
                  }
                  else
                  {
                      speech=reader->readElementText();
                      wasSpeech=true;
                  }
              }
              else if (reader->name()=="AddArg")
              {
                  if(wasArgs)
                  {
                      //error
                  }
                  else
                  {
                      genArgs=reader->readElementText();
                      wasArgs=true;
                  }
              }
              else if(reader->name()=="ECPGeneratorType")
              {
                  if(wasGenType)
                  {
                      //error
                  }
                  else
                  {
                      int index = getGeneratorTypeTable().indexOf(reader->readElementText());
                      if(index<GENERATORS_NUMBER && index>=0)
                      {
                          genType=(GeneratorType)index;
                      }
                      else
                      {
                          genType=(GeneratorType)0;
                          //out of bounds error
                      }
                  }
              }
              else if(reader->name()=="Trajectory")
              {
                  if(wasTrj)
                  {
                      //error
                  }
                  else
                  {
                      wasTrj=true;
                      coords->LoadFromXML(reader);
                  }
              }
              else
              {
                  //error - unexpected node
              }
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
        writer->writeStartElement("SetOfRobots");
        writer->writeStartElement("FirstSet");
        for(std::vector<Robot>::iterator it = set.first.begin();it!=set.first.end();it++)
        {
            writer->writeTextElement("ROBOT", QString().fromStdString(ROBOT_TABLE[(*it)]));
        }
        writer->writeEndElement();
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
        x+="\nFIRST SET:";
        for(std::vector<Robot>::iterator it = set.first.begin();it!=set.first.end();it++)
        {
            x+="\nROBOT: ";
            x+=ROBOT_TABLE[(*it)];
        }
        return x;
    }
    QStringList LoadFromXML(QXmlStreamReader * reader)
    {
        bool wasSet = false;
        bool wasParam = false;
        std::cout<<"LOADING SGS"<<std::endl;
        QStringList errors;
        while (!reader->atEnd())
        {
              reader->readNextStartElement();
              std::cout<<reader->name().toString().toStdString()<<std::endl;
              if(reader->name()=="State"&&reader->isEndElement())
              {
                  return errors;
              }
              else if(reader->name()=="SetOfRobots")
              {
                  if(wasSet)
                  {
                      //error
                  }
                  else
                  {
                      set.LoadFromXML(reader);
                      wasSet=true;
                  }
              }
              else if(reader->name()=="PosX")
              {
                  this->setPos(reader->readElementText().toDouble(), this->pos().y());
              }
              else if(reader->name()=="PosY")
              {
                  this->setPos(this->pos().x(),reader->readElementText().toDouble());
              }
              else if (reader->name()=="Parameters")
              {
                  if(wasParam)
                  {
                      //error
                  }
                  else
                  {
                      parameters=reader->readElementText();
                      wasParam=true;
                  }
              }
              else
              {
                  //unknown parameter
              }

        }
        if(set.second.size()>0)
        {
            //error
        }

        return errors;
    }
private:
    RobotSet set;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////
class genInit
{
public:

    Robot robot;
    std::vector < std::pair<GeneratorType, int> > init_values;

    genInit(){}
    QStringList LoadFromXML(QXmlStreamReader * reader)
    {
        if(reader->attributes().hasAttribute("name"))
        {
            int index = (getRobotTable().indexOf(reader->attributes().value("name").toString()));
            if(index<ROBOTS_NUMBER && index>=0)
            {
                 robot = (Robot)index;
            }
            else
            {
                //error - out of bounds type
            }
        }
        std::cout<<"LOADING SIS"<<std::endl;
        QStringList errors;
        while (!reader->atEnd())
        {
              reader->readNextStartElement();
              std::cout<<reader->name().toString().toStdString()<<std::endl;
              if(reader->name()=="ecp"&&reader->isEndElement())
              {
                  return errors;
              }
              else
              {
                  int index = getGeneratorTypeTable2().indexOf(reader->name().toString());
                  if(index<GENERATORS_NUMBER && index>=0)
                  {
                      init_values.push_back(std::make_pair((GeneratorType)index,reader->readElementText().toInt()));
                  }

              }
        }
        return errors;
    }

};

////////////////////////////////////////////////////////////////////////////////////////////////////////////
class sysInitState:public BaseState
{
public:
    sysInitState():BaseState(){}
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
        writer->writeStartElement("TaskInit");
        if(transmitter<TRANSMITTERS_NUMBER||sensors.size()>0)
        {
            writer->writeStartElement("mp");
            if(transmitter<TRANSMITTERS_NUMBER)
            {
                writer->writeTextElement("Transmitter", QString().fromStdString(TRANSMITTER_TABLE[transmitter]));
            }
            for(std::vector<Sensor>::iterator it = sensors.begin();it!=sensors.end();it++)
            {
                writer->writeTextElement("SENSOR", QString().fromStdString(SENSOR_TABLE[(*it)]));
            }

        }
        if(inits.size()>0)
        {
            for(std::vector<genInit>::iterator it = inits.begin();it!=inits.end();it++)
            {
                writer->writeStartElement("ecp");
                writer->writeAttribute(QString("name"), QString().fromStdString(ROBOT_TABLE[(*it).robot]));
                for(std::vector < std::pair<GeneratorType, int> >::iterator iter = (*it).init_values.begin(); iter!=(*it).init_values.end(); iter++)
                {
                    char tmp[20];
                    sprintf(tmp, "%d", (*iter).second);
                    writer->writeTextElement(QString().fromStdString(GENERATOR_TYPE_TABLE2[(*iter).first]), QString().fromStdString(tmp));
                }
                writer->writeEndElement();
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
                x+="\nECP: ";
                x+="\nROBOT: ";
                x+=ROBOT_TABLE[(*it).robot];
                for(std::vector < std::pair<GeneratorType, int> >::iterator iter = (*it).init_values.begin(); iter!=(*it).init_values.end(); iter++)
                {
                    x+="\nGENERATOR: ";
                    x+=GENERATOR_TYPE_TABLE[(*iter).first];
                    char tmp[20];
                    sprintf(tmp, "%d", (*iter).second);
                    x+=" ";
                    x+=tmp;
                }
            }
        }

        return x;
    }
    QStringList LoadFromXML(QXmlStreamReader * reader)
    {
        bool wasParameters = false;
        bool wasTransmitter = false;
        bool inMP = false;
        std::cout<<"LOADING SIS"<<std::endl;
        QStringList errors;
        int index;
        while (!reader->atEnd())
        {
              reader->readNextStartElement();
              std::cout<<reader->name().toString().toStdString()<<std::endl;
              if(reader->name()=="State"&&reader->isEndElement())
              {
                  return errors;
              }
              else if(reader->name()=="PosX")
              {
                  this->setPos(reader->readElementText().toDouble(), this->pos().y());
              }
              else if(reader->name()=="PosY")
              {
                  this->setPos(this->pos().x(),reader->readElementText().toDouble());
              }
              else if (reader->name()=="Parameters")
              {
                  if(wasParameters)
                  {
                      //error
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
              else if (reader->name()=="Transmitter")
              {
                  if(!inMP)
                  {
                      //error
                  }
                  if(wasTransmitter)
                  {
                      //error
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
                          //error
                      }
                  }
              }
              else if (reader->name()=="Sensor")
              {
                  if(!inMP)
                  {
                      //error
                  }
                  index = getSensorTable().indexOf(reader->readElementText());
                  if(index<SENSORS_NUMBER && index>=0)
                  {
                      sensors.push_back((Sensor)index);
                  }
                  else
                  {
                      //error
                  }
              }
              else if (reader->name()=="ecp")
              {
                  genInit tmp;
                  tmp.LoadFromXML(reader);
                  inits.push_back(tmp);
              }
              else
              {
                  //error - unexpeected node
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
        std::cout<<"LOADING WS"<<std::endl;
        QStringList errors;
        while (!reader->atEnd())
        {
              reader->readNextStartElement();
              std::cout<<reader->name().toString().toStdString()<<std::endl;
              if(reader->name()=="State"&&reader->isEndElement())
              {
                  return errors;
              }
              else if(reader->name()=="PosX")
              {
                  this->setPos(reader->readElementText().toDouble(), this->pos().y());
              }
              else if(reader->name()=="PosY")
              {
                  this->setPos(this->pos().x(),reader->readElementText().toDouble());
              }
              else if (reader->name()=="Parameters")
              {
                  if(wasParameters)
                  {
                      //error
                  }
                  else
                  {
                      parameters=reader->readElementText();
                      wasParameters=true;
                  }
              }
              else if (reader->name()=="TimeSpan")
              {
                  if(wasTimespan)
                  {
                      //error
                  }
                  else
                  {
                      Timespan=reader->readElementText().toULongLong();
                      wasTimespan=true;
                  }
              }
              else
              {
                  //error - unexpeected node
              }

        }
        return errors;
    }
private:
    unsigned long long int Timespan;
};




#endif // BASESTATE_H
