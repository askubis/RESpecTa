#include "globals.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include "RobotSet.h"
#include "Coordinates.h"

#include <stdio.h>
#include <stdlib.h>

#include "baseState.h"

#ifndef BASESTATE_H
#define BASESTATE_H
/*
class BaseState// : public DiagramItem
{
public:



private:


};
*/

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
    std::string Print()
    {
        std::string x;
        x+="\nName ";
        x+=this->getName();
        x+="\nStateType: ";
        x+=STATE_TYPE_TABLE[this->getType()];
        x+="\nParameters ";
        x+=this->getParameters();
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

private:
    RobotSet set;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////
class EmptyGenState:public BaseState
{
public:
    EmptyGenState():BaseState(){}
    EmptyGenState(EmptyGenState& old):BaseState(old)
    {
        this->robot=old.robot;
    }

    Robot getRobot() {return robot;}
    void setRobot(Robot newRobot) {robot=newRobot;}

    std::string Print()
    {
        std::string x;
        x+="\nName ";
        x+=this->getName();
        x+="\nStateType: ";
        x+=STATE_TYPE_TABLE[this->getType()];
        x+="\nParameters ";
        x+=this->getParameters();
        x+="\nROBOT: ";
        x+=ROBOT_TABLE[robot];
        return x;
    }
private:
    Robot robot;
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

    std::string Print()
    {
        std::string x;
        x+="\nName ";
        x+=this->getName();
        x+="\nStateType: ";
        x+=STATE_TYPE_TABLE[this->getType()];
        x+="\nParameters ";
        x+=this->getParameters();
        x+="\nSENSOR: ";
        x+=SENSOR_TABLE[sensor];
        return x;
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

    std::string Print()
    {
        std::string x;
        x+="\nName ";
        x+=this->getName();
        x+="\nStateType: ";
        x+=STATE_TYPE_TABLE[this->getType()];
        x+="\nParameters ";
        x+=this->getParameters();
        x+="\nSENSOR: ";
        x+=SENSOR_TABLE[sensor];
        return x;
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
    std::string getSpeech() {return speech;}
    void setSpeech(std::string newSpeech) {speech = newSpeech;}
    std::string getArgs(){return genArgs;}
    void setArgs(std::string newGenArgs){genArgs=newGenArgs;}

    std::string Print()
    {
        std::string x;
        x+="\nName ";
        x+=this->getName();
        x+="\nStateType: ";
        x+=STATE_TYPE_TABLE[this->getType()];
        x+="\nParameters ";
        x+=this->getParameters();
        return x;
    }
private:
    Robot robot;
    GeneratorType genType;
    Coordinates * coords;
    std::string genArgs;
    std::string speech;
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

    std::string Print()
    {
        std::string x;
        x+="\nName ";
        x+=this->getName();
        x+="\nStateType: ";
        x+=STATE_TYPE_TABLE[this->getType()];
        x+="\nParameters ";
        x+=this->getParameters();
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
private:
    RobotSet set;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct genInit
{
    Robot robot;
    std::vector < std::pair<GeneratorType, int> > init_values;
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

    std::string Print()
    {
        std::string x;
        x+="\nName ";
        x+=this->getName();
        x+="\nStateType: ";
        x+=STATE_TYPE_TABLE[this->getType()];
        x+="\nParameters ";
        x+=this->getParameters();
        x+="\nMP";
        x+="\ntransmitter";
        x+=TRANSMITTER_TABLE[transmitter];
        for(std::vector<Sensor>::iterator it = sensors.begin();it!=sensors.end();it++)
        {
            x+="\nSENSOR: ";
            x+=SENSOR_TABLE[(*it)];
        }
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

        return x;
    }
private:
    std::vector<genInit> inits;//wektor, bo w jednym stanie inicjalizacji moze sie znajdowac wiele robotów
    Transmitter transmitter;
    //bool cubestate;//@TODO:askubis sprawdzić
    std::vector<Sensor> sensors;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////
class WaitState:public BaseState
{
public:
    WaitState():BaseState(){}
    WaitState(WaitState& old):BaseState(old)
    {
        this->Timespan=old.Timespan;
    }

    long long int getTimespan() {return Timespan;}
    void setTimespan(long long int newTimeSpan){Timespan = newTimeSpan;}

    std::string Print()
    {
        std::string x;
        x+="\nName ";
        x+=this->getName();
        x+="\nStateType: ";
        x+=STATE_TYPE_TABLE[this->getType()];
        x+="\nParameters ";
        x+=this->getParameters();
        x+="\nTimespan ";
        char buf[20];
        sprintf(buf,"%d",Timespan);
        x+=buf;
        return x;
    }
private:
    long long int Timespan;
};




#endif // BASESTATE_H
