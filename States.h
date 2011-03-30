#include "globals.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include "RobotSet.h"
#include "Coordinates.h"

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
    EmptyGenForSetState(){}
    RobotSet getSet() {return set;}
    void setSet(RobotSet newSet) {set=newSet;}


private:
    RobotSet set;

};

////////////////////////////////////////////////////////////////////////////////////////////////////////////
class EmptyGenState:public BaseState
{
public:
    EmptyGenState() {}
    Robot getRobot() {return robot;}
    void setRobot(Robot newRobot) {robot=newRobot;}
private:
    Robot robot;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////
class GetSensorState:public BaseState
{
public:
    GetSensorState(){}
    Sensor getSensor() {return sensor;}
    void setSensor(Sensor newSensor) {sensor=newSensor;}

private:
    Sensor sensor;

};

////////////////////////////////////////////////////////////////////////////////////////////////////////////
class InitiateSensorState:public BaseState
{
public:
    InitiateSensorState(){}
    Sensor getSensor() {return sensor;}
    void setSensor(Sensor newSensor) {sensor=newSensor;}

private:
    Sensor sensor;

};

////////////////////////////////////////////////////////////////////////////////////////////////////////////
class RunGenState:public BaseState
{
public:
    RunGenState(){coords = new Coordinates();}
    Robot getRobot() {return robot;}
    void setRobot(Robot newRobot) {robot=newRobot;}
    GeneratorType getGenType() {return genType;}
    void setGenType(GeneratorType newGenType) {genType=newGenType;}
    Coordinates* getCoords() {return coords;}
    void setCoords (Coordinates * newCoords) {coords = newCoords;}
    std::string getSpeech() {return speech;}
    void setSpeech(std::string newSpeech) {speech = newSpeech;}
    std::string gerArgs(){return genArgs;}
    void setArgs(std::string newGenArgs){genArgs=newGenArgs;}


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
    StopGenState(){}
    RobotSet getSet() {return set;}
    void setSet(RobotSet newSet) {set=newSet;}

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
    sysInitState(){}
    std::vector<genInit> getInits() {return inits;}
    void setInits (std::vector<genInit> newInits) {inits=newInits;}
    Transmitter getTransmitter() {return transmitter;}
    void setTransmitter(Transmitter newTrans) {transmitter=newTrans;}
    std::vector<Sensor> getSensors() {return sensors;}
    void setSensor(std::vector<Sensor> newSensors) {sensors=newSensors;}
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
    WaitState(){}
    long long int getTimespan() {return Timespan;}
    void setTimespan(long long int newTimeSpan){Timespan = newTimeSpan;}
private:
    long long int Timespan;

};




#endif // BASESTATE_H
