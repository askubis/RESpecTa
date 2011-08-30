class StopState;
class StopGenState;
class EmptyGenState;
class EmptyGenForStateState;
class sysInitState;
class RunGenState;
class WaitState;
class GetSensorState;
class InitiateSensorState;

#ifndef STATES_H
#define STATES_H

#include "globals.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include "RobotSet.h"
#include "Coordinates.h"

#include <stdio.h>
#include <stdlib.h>

#include "robotInit.h"
#include "baseState.h"
class QXmlStreamWriter;
class QXmlStreamReader;
#include <QtGui>

class BaseState;

//////////////////////////          Stop State            //////////////////////////////////////////////////////
/**
*   State representing end of a task/subtask.
*/
class StopState:public BaseState
{
    public:
    /**
    *   Empty constructor setting stateType.
    */
    StopState():BaseState(){stateType=STATE_TYPES_NUMBER;}
    /**
    *   Copy constructor copying all date from state old.
    */
    StopState(StopState& old):BaseState(old){}
    /**
    *   Empty destructor.
    */
    ~StopState(){}

    /**
    *   Function checking if the other object is equal to this.
    *   @returns true if objects data is the same.
    */
    bool equals(BaseState* other){return BaseState::equals(other);}
    /**
    *   Function printing the state to XML writer stream.
    */
    void Print(QXmlStreamWriter* writer);

    /**
    *   Function printing the attributes of the state into a String.
    */
    std::string Print();
    /**
    *   Function loading a State from XML reader Stream.
    */
    QStringList LoadFromXML(QXmlStreamReader * reader);

    /**
    *   Function used to count how many children should there be for state's TreeView item.
    */
    int itemCount()
    {
        return 0;//Type selfexplainable
    }
    /**
    *   Returns the i'th children of this state.
    *   @returns NULL, because no children are present.
    */
    TreeItem * getChild(int i, TreeItem * parent)
    {
        return 0;
    }
};

//////////////////////////       Empty Gen for Set State        /////////////////////////////////////////////////
/**
*   State representing sets of robots, of which the first one waits for the second.
*/
class EmptyGenForSetState:public BaseState
{
public:
    /**
    *   Empty constructor setting stateType.
    */
    EmptyGenForSetState():BaseState(){stateType=EMPTY_GEN_FOR_SET;}
    /**
    *   Copy constructor copying all date from state old.
    */
    EmptyGenForSetState(EmptyGenForSetState& old):BaseState(old)
    {
        this->set = old.set;
    }
    /**
    *   Empty destructor.
    */
    ~EmptyGenForSetState(){}

    /**
    *   Function checking if the other object is equal to this.
    *   @returns true if objects data is the same.
    */
    bool equals(BaseState* other);
    /**
    *   Getter function for set.
    */
    RobotSet getSet() {return set;}
    /**
    *   Setter function for set.
    */
    void setSet(RobotSet newSet) {set=newSet;}
    /**
    *   Function printing the state to XML writer stream.
    */
    void Print(QXmlStreamWriter * writer);
    /**
    *   Function printing the attributes of the state into a String.
    */
    std::string Print();
    /**
    *   Function loading a State from XML reader Stream.
    */
    QStringList LoadFromXML(QXmlStreamReader * reader);
    /**
    *   Function used to count how many children should there be for state's TreeView item.
    */
    int itemCount()
    {
        int i=0;//Type
        i++;//set
        if(parameters.size()>0)i++;
        i+= this->outTransitionsCount();
        return i;
    }
    /**
    *   Returns the i'th children of this state.
    */
    TreeItem * getChild(int i, TreeItem * parent);

private:
    /**
    *   Set of robots.
    */
    RobotSet set;
};

//////////////////////////          Empty Gen State           ///////////////////////////////////////////////////
/**
*   State representing empty generator for one robot.
*/
class EmptyGenState:public BaseState
{
public:
    /**
    *   Empty constructor setting stateType.
    */
    EmptyGenState():BaseState(){robot = (Robot)0;stateType=EMPTY_GEN;}
    /**
    *   Copy constructor copying all date from state old.
    */
    EmptyGenState(EmptyGenState& old):BaseState(old)
    {
        this->robot=old.robot;
    }
    /**
    *   Empty destructor.
    */
    ~EmptyGenState(){}

    /**
    *   Function checking if the other object is equal to this.
    *   @returns true if objects data is the same.
    */
    bool equals(BaseState* other);
    /**
    *   Getter function for robot.
    */
    Robot getRobot() {return robot;}
    /**
    *   Setter function for robot.
    */
    void setRobot(Robot newRobot) {robot=newRobot;}
    /**
    *   Getter function for argument.
    */
    QString getArgument() {return argument;}
    /**
    *   Setter function for argument.
    */
    void setArgument(QString newArg) {argument=newArg;}
    /**
    *   Function printing the state to XML writer stream.
    */
    void Print(QXmlStreamWriter * writer);
    /**
    *   Function printing the attributes of the state into a String.
    */
    std::string Print();
    /**
    *   Function loading a State from XML reader Stream.
    */
    QStringList LoadFromXML(QXmlStreamReader * reader);
    /**
    *   Function used to count how many children should there be for state's TreeView item.
    */
    int itemCount()
    {
        int i=0;//Type
        i++;//robot
        if(argument.size()>0)i++;
        if(parameters.size()>0)i++;
        i+= this->outTransitionsCount();
        return i;
    }
    /**
    *   Returns the i'th children of this state.
    */
    TreeItem * getChild(int i, TreeItem * parent);

private:
    /**
    *   Robot, for which the empty generator is called.
    */
    Robot robot;
    //QString argument;
};

//////////////////////////          Get Sensor State           ///////////////////////////////////////////////////
/**
*   State representing downloading data from a sensor.
*/
class GetSensorState:public BaseState
{
public:
    /**
    *   Empty constructor setting stateType.
    */
    GetSensorState():BaseState(){stateType=GET_SENSOR_READING;}
    /**
    *   Copy constructor copying all date from state old.
    */
    GetSensorState(GetSensorState& old):BaseState(old)
    {
        this->sensor=old.sensor;
    }
    /**
    *   Empty destructor.
    */
    ~GetSensorState(){}

    /**
    *   Function checking if the other object is equal to this.
    *   @returns true if objects data is the same.
    */
    bool equals(BaseState* other);
    /**
    *   Getter function for sensor.
    */
    Sensor getSensor() {return sensor;}
    /**
    *   Setter function for sensor.
    */
    void setSensor(Sensor newSensor) {sensor=newSensor;}
    /**
    *   Function printing the state to XML writer stream.
    */
    void Print(QXmlStreamWriter * writer);
    /**
    *   Function printing the attributes of the state into a String.
    */
    std::string Print();
    /**
    *   Function loading a State from XML reader Stream.
    */
    QStringList LoadFromXML(QXmlStreamReader * reader);
    /**
    *   Function used to count how many children should there be for state's TreeView item.
    */
    int itemCount()
    {
        int i=0;//Type
        i++;//sensor
        if(parameters.size()>0)i++;
        i+= this->outTransitionsCount();
        return i;
    }
    /**
    *   Returns the i'th children of this state.
    */
    TreeItem * getChild(int i, TreeItem * parent);

private:
    /**
    *   Sensor, from which the information which be received.
    */
    Sensor sensor;
};

//////////////////////////          Init Sensor State           ///////////////////////////////////////////////////
/**
*   State representing initiating sensor.
*/
class InitiateSensorState:public BaseState
{
public:
    /**
    *   Empty constructor setting stateType.
    */
    InitiateSensorState():BaseState(){stateType=INITIATE_SENSOR_READING;}
    /**
    *   Copy constructor copying all date from state old.
    */
    InitiateSensorState(InitiateSensorState& old):BaseState(old)
    {
        this->sensor=old.sensor;
    }
    /**
    *   Empty destructor.
    */
    ~InitiateSensorState(){}

    /**
    *   Function checking if the other object is equal to this.
    *   @returns true if objects data is the same.
    */
    bool equals(BaseState* other);
    /**
    *   Getter function for sensor.
    */
    Sensor getSensor() {return sensor;}
    /**
    *   Setter function for sensor.
    */
    void setSensor(Sensor newSensor) {sensor=newSensor;}
    /**
    *   Function printing the state to XML writer stream.
    */
    void Print(QXmlStreamWriter * writer);
    /**
    *   Function printing the attributes of the state into a String.
    */
    std::string Print();
    /**
    *   Function loading a State from XML reader Stream.
    */
    QStringList LoadFromXML(QXmlStreamReader * reader);
    /**
    *   Function used to count how many children should there be for state's TreeView item.
    */
    int itemCount()
    {
        int i=0;//Type
        i++;//sensor
        if(parameters.size()>0)i++;
        i+= this->outTransitionsCount();
        return i;
    }
    /**
    *   Returns the i'th children of this state.
    */
    TreeItem * getChild(int i, TreeItem * parent);

private:
    /**
    *   Sensor to be initialized.
    */
    Sensor sensor;
};

//////////////////////////          Run Gen State           ///////////////////////////////////////////////////
/**
*   State representing movement of one robot.
*/
class RunGenState:public BaseState
{
public:
    /**
    *   Empty constructor setting stateType.
    */
    RunGenState():BaseState(){coords = new Coordinates();stateType==RUN_GENERATOR;}
    /**
    *   Copy constructor copying all date from state old.
    */
    RunGenState(RunGenState& old):BaseState(old)
    {
        this->robot=old.robot;
        this->genType=old.genType;
        this->filePath=old.filePath;
        this->genArgs=old.genArgs;
        this->coords=new Coordinates(*(old.coords));
        this->speech=old.speech;
    }
    /**
    *   Destructor, which deletes coords.
    */
    ~RunGenState(){if(coords)delete coords;}

    /**
    *   Function checking if the other object is equal to this.
    *   @returns true if objects data is the same.
    */
    bool equals(BaseState* other);
    /**
    *   Getter function for robot.
    */
    Robot getRobot() {return robot;}
    /**
    *   Setter function for robot.
    */
    void setRobot(Robot newRobot) {robot=newRobot;}
    /**
    *   Getter function for genType.
    */
    GeneratorType getGenType() {return genType;}
    /**
    *   Setter function for genType.
    */
    void setGenType(GeneratorType newGenType) {genType=newGenType;}
    /**
    *   Getter function for coords.
    */
    Coordinates* getCoords() {return coords;}
    /**
    *   Setter function for coords.
    */
    void setCoords (Coordinates * newCoords) {coords = newCoords;}
    /**
    *   Getter function for speech.
    */
    QString getSpeech() {return speech;}
    /**
    *   Setter function for speech.
    */
    void setSpeech(QString newSpeech) {speech = newSpeech;}
    /**
    *   Getter function for genArgs.
    */
    QString getArgs(){return genArgs;}
    /**
    *   Setter function for genArgs.
    */
    void setArgs(QString newGenArgs){genArgs=newGenArgs;}
    /**
    *   Getter function for filePath.
    */
    QString getFilePath() {return filePath;}
    /**
    *   Setter function for filePath.
    */
    void setFilePath(QString newPath) {filePath=newPath;}
    /**
    *   Function printing the state to XML writer stream.
    */
    void Print(QXmlStreamWriter * writer);
    /**
    *   Function printing the attributes of the state into a String.
    */
    std::string Print();
    /**
    *   Function loading a State from XML reader Stream.
    */
    QStringList LoadFromXML(QXmlStreamReader * reader);
    /**
    *   Function used to count how many children should there be for state's TreeView item.
    */
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
    /**
    *   Returns the i'th children of this state.
    */
    TreeItem * getChild(int i, TreeItem * parent);

private:
    /**
    *   Path to the trajectory file.
    */
    QString filePath;
    /**
    *   Robot which executes the generator.
    */
    Robot robot;
    /**
    *   Generator, which is executed.
    */
    GeneratorType genType;
    /**
    *   Coordinates holding poses and pose specification.
    */
    Coordinates * coords;
    /**
    *   Additional argument for generator execution.
    */
    QString genArgs;
    /**
    *   Speech which will be used by a speech generator.
    */
    QString speech;
};

//////////////////////////          Stop Gen State           ///////////////////////////////////////////////////
/**
*   State representing stopping movement of a set of robots.
*/
class StopGenState:public BaseState
{
public:
    /**
    *   Empty constructor setting stateType.
    */
    StopGenState():BaseState(){stateType==STOP_GEN;}
    /**
    *   Copy constructor copying all date from state old.
    */
    StopGenState(StopGenState& old):BaseState(old)
    {
        this->set=old.set;
    }
    /**
    *   Empty destructor.
    */
    ~StopGenState(){}

    /**
    *   Function checking if the other object is equal to this.
    *   @returns true if objects data is the same.
    */
    bool equals(BaseState* other);
    /**
    *   Getter function for set.
    */
    RobotSet getSet() {return set;}
    /**
    *   Setter function for set.
    */
    void setSet(RobotSet newSet) {set=newSet;}
    /**
    *   Function printing the state to XML writer stream.
    */
    void Print(QXmlStreamWriter * writer);
    /**
    *   Function printing the attributes of the state into a String.
    */
    std::string Print();
    /**
    *   Function loading a State from XML reader Stream.
    */
    QStringList LoadFromXML(QXmlStreamReader * reader);
    /**
    *   Function used to count how many children should there be for state's TreeView item.
    */
    int itemCount()
    {
        int i=0;//Type
        i++;//set
        if(parameters.size()>0)i++;
        i+= this->outTransitionsCount();
        return i;
    }
    /**
    *   Returns the i'th children of this state.
    */
    TreeItem * getChild(int i, TreeItem * parent);

private:
    /**
    *   Set of robots.
    */
    RobotSet set;
};

/////////////////////////          Sys Ini State           ///////////////////////////////////////////////////
/**
*   State representing system initialization.
*/
class sysInitState:public BaseState
{
public:
    /**
    *   Empty constructor setting stateType.
    */
    sysInitState():BaseState(){transmitter=(Transmitter)-1;stateType==SYSTEM_INITIALIZATION;}
    /**
    *   Copy constructor copying all date from state old.
    */
    sysInitState(sysInitState& old):BaseState(old)
    {
        this->inits=old.inits;
        this->transmitter=old.transmitter;
        this->sensors=old.sensors;
    }
    /**
    *   Empty destructor.
    */
    ~sysInitState(){}

    /**
    *   Function checking if the other object is equal to this.
    *   @returns true if objects data is the same.
    */
    bool equals(BaseState* other);
    /**
    *   Getter function for inits.
    */
    std::vector<robotInit> getInits() {return inits;}
    /**
    *   Setter function for inits.
    */
    void setInits (std::vector<robotInit> newInits) {inits=newInits;}
    /**
    *   Getter function for transmitter.
    */
    Transmitter getTransmitter() {return transmitter;}
    /**
    *   Setter function for transmitter.
    */
    void setTransmitter(Transmitter newTrans) {transmitter=newTrans;}
    /**
    *   Getter function for sensors.
    */
    std::vector<Sensor> getSensors() {return sensors;}
    /**
    *   Setter function for sensors.
    */
    void setSensors(std::vector<Sensor> newSensors) {sensors=newSensors;}
    /**
    *   Function printing the state to XML writer stream.
    */
    void Print(QXmlStreamWriter * writer);
    /**
    *   Function printing the attributes of the state into a String.
    */
    std::string Print();
    /**
    *   Function loading a State from XML reader Stream.
    */
    QStringList LoadFromXML(QXmlStreamReader * reader);
    /**
    *   Function used to count how many children should there be for state's TreeView item.
    */
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
    /**
    *   Returns the i'th children of this state.
    */
    TreeItem * getChild(int i, TreeItem * parent);

private:
    /**
    *   Vector of robotInits, representing initializations of generators for robots (1 robot only in each element).
    */
    std::vector<robotInit> inits;
    /**
    *   Object representing transmitter to be initialized.
    */
    Transmitter transmitter;
    /**
    *   Vector of Sensors to be initialized.
    */
    std::vector<Sensor> sensors;
};

/////////////////////////          Wait State           ///////////////////////////////////////////////////
/**
*   State representing a time delay in the system.
*/
class WaitState:public BaseState
{
public:
    /**
    *   Empty constructor setting stateType.
    */
    WaitState():BaseState(){Timespan=0;stateType==WAIT;}
    /**
    *   Copy constructor copying all date from state old.
    */
    WaitState(WaitState& old):BaseState(old)
    {
        this->Timespan=old.Timespan;
    }
    /**
    *   Empty destructor.
    */
    ~WaitState(){}

    /**
    *   Function checking if the other object is equal to this.
    *   @returns true if objects data is the same.
    */
    bool equals(BaseState* other);
    /**
    *   Getter function for Timespan.
    */
    long long int getTimespan() {return Timespan;}
    /**
    *   Setter function for Timespan.
    */
    void setTimespan(long long int newTimeSpan){Timespan = newTimeSpan;}
    /**
    *   Function printing the state to XML writer stream.
    */
    void Print(QXmlStreamWriter * writer);
    /**
    *   Function printing the attributes of the state into a String.
    */
    std::string Print();
    /**
    *   Function loading a State from XML reader Stream.
    */
    QStringList LoadFromXML(QXmlStreamReader * reader);
    /**
    *   Function used to count how many children should there be for state's TreeView item.
    */
    int itemCount()
    {
        int i=0;//Type
        i++;//timespan
        if(parameters.size()>0)i++;
        i+= this->outTransitionsCount();
        return i;
    }
    /**
    *   Returns the i'th children of this state.
    */
    TreeItem * getChild(int i, TreeItem * parent);

private:
    /**
    *   Time, for which the system will stop (in ms).
    */
    unsigned long long int Timespan;
};


#endif
