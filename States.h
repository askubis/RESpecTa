#ifndef STATES_H
#define STATES_H

class StopState;
class StopGenState;
class EmptyGenState;
class EmptyGenForStateState;
class sysInitState;
class RunGenState;
class WaitState;
class GetSensorState;
class InitiateSensorState;

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

class BaseState;

//////////////////////////          Stop State            //////////////////////////////////////////////////////
class StopState:public BaseState
{
    public:
    StopState():BaseState(){}
    StopState(StopState& old):BaseState(old){}
    ~StopState(){}

    void Print(QXmlStreamWriter*);
    std::string Print();
    QStringList LoadFromXML(QXmlStreamReader * reader);
    int itemCount()
    {
        return 0;//Type selfexplainable
    }
    TreeItem * getChild(int i, TreeItem * parent)
    {
        return 0;
    }
};

//////////////////////////       Empty Gen for Set State        /////////////////////////////////////////////////
class EmptyGenForSetState:public BaseState
{
public:
    EmptyGenForSetState():BaseState(){}
    EmptyGenForSetState(EmptyGenForSetState& old):BaseState(old)
    {
        this->set = old.set;
    }
    ~EmptyGenForSetState(){}

    RobotSet getSet() {return set;}
    void setSet(RobotSet newSet) {set=newSet;}
    void Print(QXmlStreamWriter * writer);
    std::string Print();
    QStringList LoadFromXML(QXmlStreamReader * reader);
    int itemCount()
    {
        int i=0;//Type
        if(set.first.empty()||set.second.empty()) i++;
        else i+=2;//sets
        if(parameters.size()>0)i++;
        i+= this->outTransitionsCount();
        return i;
    }
    TreeItem * getChild(int i, TreeItem * parent);

private:
    RobotSet set;
};

//////////////////////////          Empty Gen State           ///////////////////////////////////////////////////
class EmptyGenState:public BaseState
{
public:
    EmptyGenState():BaseState(){robot = (Robot)0;}
    EmptyGenState(EmptyGenState& old):BaseState(old)
    {
        this->robot=old.robot;
    }
    ~EmptyGenState(){}

    Robot getRobot() {return robot;}
    void setRobot(Robot newRobot) {robot=newRobot;}
    QString getArgument() {return argument;}
    void setArgument(QString newArg) {argument=newArg;}
    void Print(QXmlStreamWriter * writer);
    std::string Print();
    QStringList LoadFromXML(QXmlStreamReader * reader);
    int itemCount()
    {
        int i=0;//Type
        i++;//robot
        if(argument.size()>0)i++;
        if(parameters.size()>0)i++;
        i+= this->outTransitionsCount();
        return i;
    }
    TreeItem * getChild(int i, TreeItem * parent);

private:
    Robot robot;
    QString argument;
};

//////////////////////////          Get Sensor State           ///////////////////////////////////////////////////
class GetSensorState:public BaseState
{
public:
    GetSensorState():BaseState(){}
    GetSensorState(GetSensorState& old):BaseState(old)
    {
        this->sensor=old.sensor;
    }
    ~GetSensorState(){}

    Sensor getSensor() {return sensor;}
    void setSensor(Sensor newSensor) {sensor=newSensor;}
    void Print(QXmlStreamWriter * writer);
    std::string Print();
    QStringList LoadFromXML(QXmlStreamReader * reader);
    int itemCount()
    {
        int i=0;//Type
        i++;//sensor
        if(parameters.size()>0)i++;
        i+= this->outTransitionsCount();
        return i;
    }
    TreeItem * getChild(int i, TreeItem * parent);

private:
    Sensor sensor;
};

//////////////////////////          Init Sensor State           ///////////////////////////////////////////////////
class InitiateSensorState:public BaseState
{
public:
    InitiateSensorState():BaseState(){}
    InitiateSensorState(InitiateSensorState& old):BaseState(old)
    {
        this->sensor=old.sensor;
    }
    ~InitiateSensorState(){}

    Sensor getSensor() {return sensor;}
    void setSensor(Sensor newSensor) {sensor=newSensor;}
    void Print(QXmlStreamWriter * writer);
    std::string Print();
    QStringList LoadFromXML(QXmlStreamReader * reader);
    int itemCount()
    {
        int i=0;//Type
        i++;//sensor
        if(parameters.size()>0)i++;
        i+= this->outTransitionsCount();
        return i;
    }
    TreeItem * getChild(int i, TreeItem * parent);

private:
    Sensor sensor;
};

//////////////////////////          Run Gen State           ///////////////////////////////////////////////////
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
    ~RunGenState(){if(coords)delete coords;}

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
    void Print(QXmlStreamWriter * writer);
    std::string Print();
    QStringList LoadFromXML(QXmlStreamReader * reader);
    int itemCount()
    {
        int i=0;//Type
        i++;//robot
        i++;//genType
        if(genArgs.size()>0)i++;
        if(filePath.size()>0)i++;
        if(speech.size()>0)i++;
        if(coords->getPoses().size()>0)i++;//to oznacza ze coords ma sens
        if(parameters.size()>0)i++;
        i+= this->outTransitionsCount();
        return i;
    }
    TreeItem * getChild(int i, TreeItem * parent);

private:
    QString filePath;
    Robot robot;
    GeneratorType genType;
    Coordinates * coords;
    QString genArgs;
    QString speech;
};

//////////////////////////          Stop Gen State           ///////////////////////////////////////////////////
class StopGenState:public BaseState
{
public:
    StopGenState():BaseState(){}
    StopGenState(StopGenState& old):BaseState(old)
    {
        this->set=old.set;
    }
    ~StopGenState(){}

    RobotSet getSet() {return set;}
    void setSet(RobotSet newSet) {set=newSet;}
    void Print(QXmlStreamWriter * writer);
    std::string Print();
    QStringList LoadFromXML(QXmlStreamReader * reader);
    int itemCount()
    {
        int i=0;//Type
        if(set.first.empty()||set.second.empty()) i++;
        else i+=2;//sets
        if(parameters.size()>0)i++;
        i+= this->outTransitionsCount();
        return i;
    }
    TreeItem * getChild(int i, TreeItem * parent);

private:
    RobotSet set;
};

/////////////////////////          Sys Ini State           ///////////////////////////////////////////////////
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
    ~sysInitState(){}

    std::vector<genInit> getInits() {return inits;}
    void setInits (std::vector<genInit> newInits) {inits=newInits;}
    Transmitter getTransmitter() {return transmitter;}
    void setTransmitter(Transmitter newTrans) {transmitter=newTrans;}
    std::vector<Sensor> getSensors() {return sensors;}
    void setSensors(std::vector<Sensor> newSensors) {sensors=newSensors;}
    void Print(QXmlStreamWriter * writer);
    std::string Print();
    QStringList LoadFromXML(QXmlStreamReader * reader);
    int itemCount()
    {
        int i=0;//Type
        if(isProper(transmitter))i++;
        i+=sensors.size();
        i+=inits.size();
        if(parameters.size()>0)i++;
        i+= this->outTransitionsCount();
        return i;
    }
    TreeItem * getChild(int i, TreeItem * parent);

private:
    std::vector<genInit> inits;//wektor, bo w jednym stanie inicjalizacji moze sie znajdowac wiele robotów
    Transmitter transmitter;
    std::vector<Sensor> sensors;
};

/////////////////////////          Wait State           ///////////////////////////////////////////////////
class WaitState:public BaseState
{
public:
    WaitState():BaseState(){Timespan=0;}
    WaitState(WaitState& old):BaseState(old)
    {
        this->Timespan=old.Timespan;
    }
    ~WaitState(){}

    long long int getTimespan() {return Timespan;}
    void setTimespan(long long int newTimeSpan){Timespan = newTimeSpan;}
    void Print(QXmlStreamWriter * writer);
    std::string Print();
    QStringList LoadFromXML(QXmlStreamReader * reader);
    int itemCount()
    {
        int i=0;//Type
        i++;//timespan
        if(parameters.size()>0)i++;
        i+= this->outTransitionsCount();
        return i;
    }
    TreeItem * getChild(int i, TreeItem * parent);

private:
    unsigned long long int Timespan;
};


#endif
