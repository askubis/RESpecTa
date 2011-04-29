#ifndef GLOBALS_H
#define GLOBALS_H
#include <QStringList>
#include <iostream>

//QT_BEGIN_NAMESPACE
//class QStringList;
//QT_END_NAMESPACE




//***************   STATE TYPES   ***************//
enum StateType {SYSTEM_INITIALIZATION, RUN_GENERATOR, EMPTY_GEN_FOR_SET, EMPTY_GEN, WAIT, STOP_GEN,
                INITIATE_SENSOR_READING, GET_SENSOR_READING,
                //CUBE_STATE_INIT, CUBE_STATE_WRITING, CUBE_STATE_CHANGE, COMMUNICATE_WITH_SOLVER, MANIPULATION_SEQ_TRANSLATION,
            STATE_TYPES_NUMBER };
static std::string STATE_TYPE_TABLE[STATE_TYPES_NUMBER+1] =
        {"systemInitialization","runGenerator","emptyGenForSet","emptyGen","wait","stopGen",
         "initiateSensorReading","getSensorReading",""};
static QStringList getStateTypeTable()
{
    QStringList items;
    for (int i=0;i<STATE_TYPES_NUMBER;i++)
    {
        items<<QString().fromStdString(STATE_TYPE_TABLE[i]);
    }
    return items;
}

//***************   GENERATOR TYPES   ***************//
enum GeneratorType {ECP_GEN_TEACH_IN, ECP_GEN_NEWSMOOTH, ECP_GEN_WEIGHT_MEASURE, ECP_GEN_TRANSPARENT, ECP_GEN_TFF_NOSE_RUN,
     ECP_GEN_BIAS_EDP_FORCE, ECP_GEN_TFF_RUBIK_GRAB, ECP_GEN_TFF_RUBIK_FACE_ROTATE, ECP_ST_GRIPPER_OPENING,
     ECP_GRIPPER_APPROACH_GEN,
                GENERATORS_NUMBER};
static std::string GENERATOR_TYPE_TABLE[GENERATORS_NUMBER+1] =
        {"ECP_GEN_TEACH_IN","ECP_GEN_NEWSMOOTH","ECP_GEN_WEIGHT_MEASURE","ECP_GEN_TRANSPARENT","ECP_GEN_TFF_NOSE_RUN",
         "ECP_GEN_BIAS_EDP_FORCE","ECP_GEN_TFF_RUBIK_GRAB","ECP_GEN_TFF_RUBIK_FACE_ROTATE","ECP_ST_GRIPPER_OPENING",
         "ECP_GIRPPER_APPROACH_GEN",""};
static std::string GENERATOR_TYPE_TABLE2[GENERATORS_NUMBER+1] =
        {"ecp_teach_in_gen","ecp_smooth_gen","weight_measure_gen","ecp_gen_t","ecp_tff_nose_run_gen",
         "bias_edp_force_gen","ecp_tff_rubik_grab_gen","ecp_tff_rubik_face_rotate_gen","gripper_opening",
         "ecp_tff_gripper_approach_gen",""};
static QStringList getGeneratorTypeTable()
{
    QStringList items;
    for (int i=0;i<GENERATORS_NUMBER;i++)
    {
        items<<QString().fromStdString(GENERATOR_TYPE_TABLE[i]);
    }
    return items;
}

//***************   ROBOTS   ***************//
enum Robot {ROBOT_UNDEFINED, ROBOT_IRP6OT_M, ROBOT_IRP6P_M, ROBOT_FESTIVAL, ROBOT_CONVEYOR, ROBOT_SPEAKER,
            ROBOT_IRP6_MECHATRONIKA, ROBOT_ELECTRON, ROBOT_HAND, ROBOT_SPEECHRECOGNITION,
      ROBOTS_NUMBER};
static std::string ROBOT_TABLE[ROBOTS_NUMBER+1] =
        {"ROBOT_UNDEFINED","ROBOT_IRP6OT_M","ROBOT_IRP6P_M","ROBOT_FESTIVAL","ROBOT_CONVEYOR","ROBOT_SPEAKER",
         "ROBOT_IRP6_MECHATRONIKA","ROBOT_ELECTRON","ROBOT_HAND","ROBOT_SPEECHRECOGNITION",""};
static QStringList getRobotTable()
{
    QStringList items;
    for (int i=0;i<ROBOTS_NUMBER;i++)
    {
        items<<QString().fromStdString(ROBOT_TABLE[i]);
    }
    return items;
}

//***************   SENSORS   ***************//
enum Sensor {SENSOR_CAMERA_ON_TRACK, SENSOR_CAMERA_SA,
        SENSORS_NUMBER};
static std::string SENSOR_TABLE[SENSORS_NUMBER+1] =
        {"SENSOR_CAMERA_ON_TRACK","SENSOR_CAMERA_SA",""};
static QStringList getSensorTable()
{
    QStringList items;
    for (int i=0;i<SENSORS_NUMBER;i++)
    {
        items<<QString().fromStdString(SENSOR_TABLE[i]);
    }
    return items;
}

//***************   COORD TYPES   ***************//
enum CoordType {ECP_INVALID_END_EFFECTOR, ECP_XYZ_ANGLE_AXIS, ECP_XYZ_EULER_ZYZ, ECP_JOINT, ECP_MOTOR, ECP_PF_VELOCITY,
            COORDTYPES_NUMBER};
static std::string COORD_TYPE_TABLE[COORDTYPES_NUMBER+1] =
        {"ECP_INVALID_END_EFFECTOR","ECP_XYZ_ANGLE_AXIS","ECP_XYZ_EULER_ZYZ","ECP_JOINT","ECP_MOTOR","ECP_PF_VELOCITY",""};
static QStringList getCoordTypeTable()
{
    QStringList items;
    for (int i=0;i<COORDTYPES_NUMBER;i++)
    {
        items<<QString().fromStdString(COORD_TYPE_TABLE[i]);
    }
    return items;
}

//***************   MOTION TYPES   ***************//
enum MotionType {ABSOLUTE, RELATIVE,
             MOTIONTYPES_NUMBER};
static std::string MOTION_TYPE_TABLE[MOTIONTYPES_NUMBER+1] =
        {"ABSOLUTE","RELATIVE",""};
static QStringList getMotionTypeTable()
{
    QStringList items;
    for (int i=0;i<MOTIONTYPES_NUMBER;i++)
    {
        items<<QString().fromStdString(MOTION_TYPE_TABLE[i]);
    }
    return items;
}

//***************   TRANSMITTERS   ***************//
enum Transmitter {TRANSMITTER_RC_WINDOWS,
            TRANSMITTERS_NUMBER};
static std::string TRANSMITTER_TABLE[TRANSMITTERS_NUMBER+1] =
        {"TRANSMITTER_RC_WINDOWS",""};
static QStringList getTransmitterTable()
{
    QStringList items;
    for (int i=0;i<TRANSMITTERS_NUMBER;i++)
    {
        items<<QString().fromStdString(TRANSMITTER_TABLE[i]);
    }
    return items;
}



#endif // GLOBALS_H
