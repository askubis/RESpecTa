#include "globals.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include "RobotSet.h"
#include "Coordinates.h"

#include "diagramitem.h"

#ifndef BASESTATE_H
#define BASESTATE_H

class BaseState// : public DiagramItem
{
public:
    BaseState() {}
    std::string getName() {return stateName;}
    void setName(std::string newName) {stateName=newName;}
    StateType getType() {return type;}
    void setType(StateType newType) {type=newType;}
    int getArgument() {return argument;}
    void setArgument(int newArg){argument = newArg;}
    std::string getParameters() {return parameters;}
    void setParameters(std::string newParams){parameters = newParams;}
    DiagramItem* getItem() {return item;}
    void setItem (DiagramItem * newItem){item=newItem;}
    std::string stateName;

private:
    //std::string stateName;
    StateType type;
    int argument;
    std::string parameters;
    DiagramItem *item;
};


////////////////////////////////////////////////////////////////////////////////////////////////////////////
class EmptyGenForSetState:public BaseState
{
public:
    RobotSet getSet() {return set;}
    void setSet(RobotSet newSet) {set=newSet;}


private:
    RobotSet set;

};

////////////////////////////////////////////////////////////////////////////////////////////////////////////
class EmptyGenState:public BaseState
{
public:
    Robot getRobot() {return robot;}
    void setRobot(Robot newRobot) {robot=newRobot;}
private:
    Robot robot;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////
class GetSensorState:public BaseState
{
public:
    Sensor getSensor() {return sensor;}
    void setSensor(Sensor newSensor) {sensor=newSensor;}

private:
    Sensor sensor;

};

////////////////////////////////////////////////////////////////////////////////////////////////////////////
class InitiateSensorState:public BaseState
{
public:
    Sensor getSensor() {return sensor;}
    void setSensor(Sensor newSensor) {sensor=newSensor;}

private:
    Sensor sensor;

};

////////////////////////////////////////////////////////////////////////////////////////////////////////////
class RunGenState:public BaseState
{
public:

    Robot getRobot() {return robot;}
    void setRobot(Robot newRobot) {robot=newRobot;}
    GeneratorType getGenType() {return genType;}
    void setGenType(GeneratorType newGenType) {genType=newGenType;}
    Coordinates* getCoords() {return coords;}
    void setCoords (Coordinates * newCoords) {coords = newCoords;}
    std::string getSpeech() {return speech;}
    void setSpeech(std::string newSpeech) {speech = newSpeech;}


private:
    Robot robot;
    GeneratorType genType;
    Coordinates * coords;
    float * genArg;
    std::string speech;

};

////////////////////////////////////////////////////////////////////////////////////////////////////////////
class StopGenState:public BaseState
{
public:

    RobotSet getSet() {return set;}
    void setSet(RobotSet newSet) {set=newSet;}

private:
    RobotSet set;

};

////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct genInit
{
    Robot robot;
    int args[GENERATORS_NUMBER];
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////
class sysInitState:public BaseState
{
public:
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
    long long int getTimespan() {return Timespan;}
    void setTimespan(long long int newTimeSpan){Timespan = newTimeSpan;}
private:
    long long int Timespan;

};



#endif // BASESTATE_H
