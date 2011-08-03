#ifndef GLOBALS_H
#define GLOBALS_H

#include <QStringList>
#include <iostream>


enum SceneMode { InsertItem, InsertLine, MoveItem };

//***************   STATE TYPES   ***************//
/**
*   Enum Type representing StateTypes.
*/
enum StateType {SYSTEM_INITIALIZATION, RUN_GENERATOR, EMPTY_GEN_FOR_SET, EMPTY_GEN, WAIT, STOP_GEN,
                INITIATE_SENSOR_READING, GET_SENSOR_READING,
                //CUBE_STATE_INIT, CUBE_STATE_WRITING, CUBE_STATE_CHANGE, COMMUNICATE_WITH_SOLVER, MANIPULATION_SEQ_TRANSLATION,
            STATE_TYPES_NUMBER };
/**
*   Table containing all strings representing StateTypes.
*/
static std::string STATE_TYPE_TABLE[STATE_TYPES_NUMBER+1] =
        {"systemInitialization","set_next_ecp_state","wait_for_task_termination","emptyGen","wait_ms","send_end_motion_to_ecps",
         "initiateSensorReading","getSensorReading",""};
/**
*   Function returning list of StateTypes.
*   @returns List containing names of all StateTypes.
*/
static QStringList getStateTypeTable()
{
    QStringList items;
    for (int i=0;i<STATE_TYPES_NUMBER;i++)
    {
        items<<QString().fromStdString(STATE_TYPE_TABLE[i]);
    }
    return items;
}

/**
*   Function checking if given StateType is a proper value of StateTypes.
*   @param  value StateType to check if proper.
*   @returns True if the value is proper.
*/
static bool isProper(StateType value)
{
    return (value>=0 && value<STATE_TYPES_NUMBER);
}

//***************   GENERATOR TYPES   ***************//
/**
*   Enum Type representing GeneratorTypes.
*/
enum GeneratorType {ECP_GEN_TEACH_IN, ECP_GEN_NEWSMOOTH, ECP_GEN_WEIGHT_MEASURE, ECP_GEN_TRANSPARENT, ECP_GEN_TFF_NOSE_RUN,
     ECP_ST_BIAS_EDP_FORCE, ECP_GEN_TFF_RUBIK_GRAB, ECP_GEN_TFF_RUBIK_FACE_ROTATE, ECP_ST_GRIPPER_OPENING,
     ECP_GEN_TFF_GRIPPER_APPROACH,
                GENERATORS_NUMBER};
/**
*   Table containing all strings representing GeneratorTypes(not for initialization).
*/
static std::string GENERATOR_TYPE_TABLE[GENERATORS_NUMBER+1] =
        {"ECP_GEN_TEACH_IN","ECP_GEN_NEWSMOOTH","ECP_GEN_WEIGHT_MEASURE","ECP_GEN_TRANSPARENT","ECP_GEN_TFF_NOSE_RUN",
         "ECP_ST_BIAS_EDP_FORCE","ECP_GEN_TFF_RUBIK_GRAB","ECP_GEN_TFF_RUBIK_FACE_ROTATE","ECP_ST_GRIPPER_OPENING",
         "ECP_GEN_TFF_GRIPPER_APPROACH",""};
/**
*   Table containing all strings representing GeneratorTypes(for initialization).
*/
static std::string GENERATOR_TYPE_TABLE2[GENERATORS_NUMBER+1] =
        {"ecp_teach_in_gen","ecp_smooth_gen","weight_measure_gen","ecp_gen_t","ecp_tff_nose_run_gen",
         "bias_edp_force_st","ecp_tff_rubik_grab_gen","ecp_tff_rubik_face_rotate_gen","gripper_opening",
         "ecp_tff_gripper_approach_gen",""};
/**
*   Function returning list of GeneratorTypes(not for initialization).
*   @returns List containing names of all GeneratorTypes(not for initialization).
*/
static QStringList getGeneratorTypeTable()
{
    QStringList items;
    for (int i=0;i<GENERATORS_NUMBER;i++)
    {
        items<<QString().fromStdString(GENERATOR_TYPE_TABLE[i]);
    }
    return items;
}
/**
*   Function returning list of GeneratorTypes(for initialization).
*   @returns List containing names of all GeneratorTypes(for initialization).
*/
static QStringList getGeneratorTypeTable2()
{
    QStringList items;
    for (int i=0;i<GENERATORS_NUMBER;i++)
    {
        items<<QString().fromStdString(GENERATOR_TYPE_TABLE2[i]);
    }
    return items;
}

/**
*   Function checking if given GeneratorType is a proper value of GeneratorTypes.
*   @param  value GeneratorType to check if proper.
*   @returns True if the value is proper.
*/
static bool isProper(GeneratorType value)
{
    return (value>=0 && value<GENERATORS_NUMBER);
}

//***************   ROBOTS   ***************//
/**
*   Enum Type representing Robots.
*/
enum Robot {ROBOT_UNDEFINED, irp6ot_m, irp6p_m, festival, conveyor,
            ROBOT_ELECTRON, bird_hand, ROBOT_SPEECHRECOGNITION,
      ROBOTS_NUMBER};
/**
*   Table containing all strings representing Robots.
*/
static std::string ROBOT_TABLE[ROBOTS_NUMBER+1] =
        {"ROBOT_UNDEFINED","irp6ot_m","irp6p_m","festival","conveyor",
         "ROBOT_ELECTRON","bird_hand","ROBOT_SPEECHRECOGNITION",""};
/**
*   Function returning list of StateTypes.
*   @returns List containing names of all Robots.
*/
static QStringList getRobotTable()
{
    QStringList items;
    for (int i=0;i<ROBOTS_NUMBER;i++)
    {
        items<<QString().fromStdString(ROBOT_TABLE[i]);
    }
    return items;
}

/**
*   Function checking if given Robot is a proper value of Robots.
*   @param  value Robot to check if proper.
*   @returns True if the value is proper.
*/
static bool isProper(Robot value)
{
    return (value>=0 && value<ROBOTS_NUMBER);
}

//***************   SENSORS   ***************//
/**
*   Enum Type representing Sensors.
*/
enum Sensor {SENSOR_CAMERA_ON_TRACK, SENSOR_CAMERA_SA,
        SENSORS_NUMBER};
/**
*   Table containing all strings representing Sensors.
*/
static std::string SENSOR_TABLE[SENSORS_NUMBER+1] =
        {"SENSOR_CAMERA_ON_TRACK","SENSOR_CAMERA_SA",""};
/**
*   Function returning list of StateTypes.
*   @returns List containing names of all Sensors.
*/
static QStringList getSensorTable()
{
    QStringList items;
    for (int i=0;i<SENSORS_NUMBER;i++)
    {
        items<<QString().fromStdString(SENSOR_TABLE[i]);
    }
    return items;
}

/**
*   Function checking if given Sensor is a proper value of Sensors.
*   @param  value Sensor to check if proper.
*   @returns True if the value is proper.
*/
static bool isProper(Sensor value)
{
    return (value>=0 && value<SENSORS_NUMBER);
}

//***************   COORD TYPES   ***************//
/**
*   Enum Type representing CoordTypes.
*/
enum CoordType {ecp_XYZ_ANGLE_AXIS, ecp_XYZ_EULER_ZYZ, JOINT, MOTOR, ECP_PF_VELOCITY,
            COORDTYPES_NUMBER};
/**
*   Table containing all strings representing CoordTypes.
*/
static std::string COORD_TYPE_TABLE[COORDTYPES_NUMBER+1] =
        {"ecp_XYZ_ANGLE_AXIS","ecp_XYZ_EULER_ZYZ","JOINT","MOTOR","ECP_PF_VELOCITY",""};
/**
*   Function returning list of StateTypes.
*   @returns List containing names of all CoordTypes.
*/
static QStringList getCoordTypeTable()
{
    QStringList items;
    for (int i=0;i<COORDTYPES_NUMBER;i++)
    {
        items<<QString().fromStdString(COORD_TYPE_TABLE[i]);
    }
    return items;
}

/**
*   Function checking if given CoordType is a proper value of CoordTypes.
*   @param  value CoordType to check if proper.
*   @returns True if the value is proper.
*/
static bool isProper(CoordType value)
{
    return (value>=0 && value<COORDTYPES_NUMBER);
}

//***************   MOTION TYPES   ***************//
/**
*   Enum Type representing MotionTypes.
*/
enum MotionType {ABSOLUTE, RELATIVE,
             MOTIONTYPES_NUMBER};
/**
*   Table containing all strings representing MotionTypes.
*/
static std::string MOTION_TYPE_TABLE[MOTIONTYPES_NUMBER+1] =
        {"Absolute","Relative",""};
/**
*   Function returning list of StateTypes.
*   @returns List containing names of all MotionTypes.
*/
static QStringList getMotionTypeTable()
{
    QStringList items;
    for (int i=0;i<MOTIONTYPES_NUMBER;i++)
    {
        items<<QString().fromStdString(MOTION_TYPE_TABLE[i]);
    }
    return items;
}

/**
*   Function checking if given MotionType is a proper value of MotionTypes.
*   @param  value MotionType to check if proper.
*   @returns True if the value is proper.
*/
static bool isProper(MotionType value)
{
    return (value>=0 && value<MOTIONTYPES_NUMBER);
}

//***************   TRANSMITTERS   ***************//
/**
*   Enum Type representing TraRobotsnsmitters.
*/
enum Transmitter {TRANSMITTER_RC_WINDOWS,
            TRANSMITTERS_NUMBER};
/**
*   Table containing all strings representing Transmitters.
*/
static std::string TRANSMITTER_TABLE[TRANSMITTERS_NUMBER+1] =
        {"TRANSMITTER_RC_WINDOWS",""};
/**
*   Function returning list of StateTypes.
*   @returns List containing names of all Transmitters.
*/
static QStringList getTransmitterTable()
{
    QStringList items;
    for (int i=0;i<TRANSMITTERS_NUMBER;i++)
    {
        items<<QString().fromStdString(TRANSMITTER_TABLE[i]);
    }
    return items;
}

/**
*   Function checking if given Transmitter is a proper value of Transmitters.
*   @param  value Transmitter to check if proper.
*   @returns True if the value is proper.
*/
static bool isProper(Transmitter value)
{
    return (value>=0 && value<TRANSMITTERS_NUMBER);
}



#endif // GLOBALS_H
