#include "States.h"
#include "TreeItem.h"


void StopState::Print(QXmlStreamWriter*){}
std::string StopState::Print()
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
QStringList StopState::LoadFromXML(QXmlStreamReader * reader)
{
    QStringList errors;
    while (!reader->atEnd())
    {
          reader->readNextStartElement();
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


void EmptyGenForSetState::Print(QXmlStreamWriter * writer)
{

    if(parameters.size()>0)
    {
        writer->writeTextElement("Parameters", parameters);
        //x+=this->parameters.toStdString();
    }
    set.Print(writer);
}
std::string EmptyGenForSetState::Print()
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
QStringList EmptyGenForSetState::LoadFromXML(QXmlStreamReader * reader)
{
    bool wasSet = false;
    bool wasParam = false;
    QStringList errors;
    while (!reader->atEnd())
    {
          reader->readNextStartElement();
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

TreeItem * EmptyGenForSetState::getChild(int i, TreeItem * parent)
{
    int index = i;
    if(!set.first.empty())
    {
        if(index==0)
        {
            TreeRobotSetItem * tmp = new TreeRobotSetItem(i, parent->getModel(), parent);
            tmp->setSet(set.first, true);
            return tmp;
        }
        else
        {
            index--;
        }
    }
    if(!set.second.empty())
    {
        if(index==0)
        {
            TreeRobotSetItem * tmp = new TreeRobotSetItem(i, parent->getModel(), parent);
            tmp->setSet(set.second, false);
            return tmp;
        }
        else
        {
            index--;
        }
    }
    if (parameters.size()>0)
    {
        if(index==0)
        {
            TreeTextItem * tmp = new TreeTextItem(i, parent->getModel(), parent);
            tmp->setNameAttr("Parameters", parameters);
            return tmp;
        }
        else
        {
            index--;
        }
    }
    foreach (Transition * tr, Transitions)
    {
        if (tr->startItem()==this)
        {
            if(index==0)
            {
                TreeTransItem * tmp = new TreeTransItem(i, parent->getModel(), parent);
                tmp->setTrans(tr);
                return tmp;
            }
            else
            {
                index--;
            }
        }
    }
    return NULL;
}

void EmptyGenState::Print(QXmlStreamWriter * writer)
{

    if(parameters.size()>0)
    {
        writer->writeTextElement("Parameters", parameters);
    }
    writer->writeTextElement("ROBOT", QString().fromStdString(ROBOT_TABLE[robot]));
    writer->writeTextElement("AddArg", argument);

}
std::string EmptyGenState::Print()
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
QStringList EmptyGenState::LoadFromXML(QXmlStreamReader * reader)
{
    bool wasRobot = false;
    bool wasParam = false;
    bool wasArg = false;
    QStringList errors;
    while (!reader->atEnd())
    {
          reader->readNextStartElement();
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
                  Robot index = (Robot)(getRobotTable().indexOf(reader->readElementText()));
                  if(isProper(index))
                  {
                      robot = index;
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
TreeItem * EmptyGenState::getChild(int i, TreeItem * parent)
{
    int index = i;
    if(index==0)
    {

            TreeTextItem * tmp = new TreeTextItem(i, parent->getModel(), parent);
            tmp->setNameAttr("Robot", QString().fromStdString(ROBOT_TABLE[robot]));
            return tmp;
    }
    else
    {
        index--;
    }
    if(argument.size()>0)
    {
        if(index==0)
        {
            TreeTextItem * tmp = new TreeTextItem(i, parent->getModel(), parent);
            tmp->setNameAttr("Argument", argument);
            return tmp;
        }
        else
        {
            index--;
        }
    }
    if (parameters.size()>0)
    {
        if(index==0)
        {
            TreeTextItem * tmp = new TreeTextItem(i, parent->getModel(), parent);
            tmp->setNameAttr("Parameters", parameters);
            return tmp;
        }
        else
        {
            index--;
        }
    }
    foreach (Transition * tr, Transitions)
    {
        if (tr->startItem()==this)
        {
            if(index==0)
            {
                TreeTransItem * tmp = new TreeTransItem(i, parent->getModel(), parent);
                tmp->setTrans(tr);
                return tmp;
            }
            else
            {
                index--;
            }
        }
    }
    return NULL;
}

void GetSensorState::Print(QXmlStreamWriter * writer)
{
    if(parameters.size()>0)
    {
        writer->writeTextElement("Parameters", parameters);
    }
    writer->writeTextElement("SENSOR", QString().fromStdString(SENSOR_TABLE[sensor]));
}
std::string GetSensorState::Print()
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
QStringList GetSensorState::LoadFromXML(QXmlStreamReader * reader)
{
    bool wasParam = false;
    bool wasSensor = false;
    QStringList errors;
    while (!reader->atEnd())
    {
          reader->readNextStartElement();
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
                  Sensor index = (Sensor)(getSensorTable().indexOf(reader->readElementText()));
                  if(isProper(index))
                  {
                      sensor = index;
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
TreeItem * GetSensorState::getChild(int i, TreeItem * parent)
{
    int index = i;
    if(index==0)
    {
            TreeTextItem * tmp = new TreeTextItem(i, parent->getModel(), parent);
            tmp->setNameAttr("Sensor", QString().fromStdString(SENSOR_TABLE[sensor]));
            return tmp;
    }
    else
    {
        index--;
    }
    if (parameters.size()>0)
    {
        if(index==0)
        {
            TreeTextItem * tmp = new TreeTextItem(i, parent->getModel(), parent);
            tmp->setNameAttr("Parameters", parameters);
            return tmp;
        }
        else
        {
            index--;
        }
    }
    foreach (Transition * tr, Transitions)
    {
        if (tr->startItem()==this)
        {
            if(index==0)
            {
                TreeTransItem * tmp = new TreeTransItem(i, parent->getModel(), parent);
                tmp->setTrans(tr);
                return tmp;
            }
            else
            {
                index--;
            }
        }
    }
    return NULL;
}

void InitiateSensorState::Print(QXmlStreamWriter * writer)
{
    if(parameters.size()>0)
    {
        writer->writeTextElement("Parameters", parameters);
    }
    writer->writeTextElement("SENSOR", QString().fromStdString(SENSOR_TABLE[sensor]));
}
std::string InitiateSensorState::Print()
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
QStringList InitiateSensorState::LoadFromXML(QXmlStreamReader * reader)
{
    bool wasParam = false;
    bool wasSensor = false;
    QStringList errors;
    while (!reader->atEnd())
    {
          reader->readNextStartElement();
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
                  Sensor index = (Sensor)(getSensorTable().indexOf(reader->readElementText()));
                  if(isProper(index))
                  {
                      sensor = index;
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

TreeItem * InitiateSensorState::getChild(int i, TreeItem * parent)
{
    int index = i;
    if(index==0)
    {
            TreeTextItem * tmp = new TreeTextItem(i, parent->getModel(), parent);
            tmp->setNameAttr("Sensor", QString().fromStdString(SENSOR_TABLE[sensor]));
            return tmp;
    }
    else
    {
        index--;
    }
    if (parameters.size()>0)
    {
        if(index==0)
        {
            TreeTextItem * tmp = new TreeTextItem(i, parent->getModel(), parent);
            tmp->setNameAttr("Parameters", parameters);
            return tmp;
        }
        else
        {
            index--;
        }
    }
    foreach (Transition * tr, Transitions)
    {
        if (tr->startItem()==this)
        {
            if(index==0)
            {
                TreeTransItem * tmp = new TreeTransItem(i, parent->getModel(), parent);
                tmp->setTrans(tr);
                return tmp;
            }
            else
            {
                index--;
            }
        }
    }
    return NULL;
}

void RunGenState::Print(QXmlStreamWriter * writer)
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

std::string RunGenState::Print()
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
QStringList RunGenState::LoadFromXML(QXmlStreamReader * reader)
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
                  Robot index = (Robot)(getRobotTable().indexOf(reader->readElementText()));
                  if(isProper(index))
                  {
                      robot = index;
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
                  GeneratorType index = (GeneratorType)(getGeneratorTypeTable().indexOf(reader->readElementText()));
                  if(isProper(index))
                  {
                      wasGenType=true;
                      genType=index;
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

TreeItem * RunGenState::getChild(int i, TreeItem * parent)
{
    int index = i;
    if(index==0)
    {
            TreeTextItem * tmp = new TreeTextItem(i, parent->getModel(), parent);
            tmp->setNameAttr("Robot", QString().fromStdString(ROBOT_TABLE[robot]));
            return tmp;
    }
    else
    {
        index--;
    }
    if(index==0)
    {
            TreeTextItem * tmp = new TreeTextItem(i, parent->getModel(), parent);
            tmp->setNameAttr("GenType", QString().fromStdString(GENERATOR_TYPE_TABLE[genType]));
            return tmp;
    }
    else
    {
        index--;
    }
    if (genArgs.size()>0)
    {
        if(index==0)
        {
            TreeTextItem * tmp = new TreeTextItem(i, parent->getModel(), parent);
            tmp->setNameAttr("GenArgs", genArgs);
            return tmp;
        }
        else
        {
            index--;
        }
    }
    if (filePath.size()>0)
    {
        if(index==0)
        {
            TreeTextItem * tmp = new TreeTextItem(i, parent->getModel(), parent);
            tmp->setNameAttr("filePath", filePath);
            return tmp;
        }
        else
        {
            index--;
        }
    }
    if (speech.size()>0)
    {
        if(index==0)
        {
            TreeTextItem * tmp = new TreeTextItem(i, parent->getModel(), parent);
            tmp->setNameAttr("Speech", speech);
            return tmp;
        }
        else
        {
            index--;
        }
    }
    if(coords->getPoses().size()>0)
    {
        if(index==0)
        {
            TreeCoordItem * tmp = new TreeCoordItem(i, parent->getModel(), parent);
            tmp->setCoords(coords);
            return tmp;
        }
        else
        {
            index--;
        }
    }
    if (parameters.size()>0)
    {
        if(index==0)
        {
            TreeTextItem * tmp = new TreeTextItem(i, parent->getModel(), parent);
            tmp->setNameAttr("Parameters", parameters);
            return tmp;
        }
        else
        {
            index--;
        }
    }
    foreach (Transition * tr, Transitions)
    {
        if (tr->startItem()==this)
        {
            if(index==0)
            {
                TreeTransItem * tmp = new TreeTransItem(i, parent->getModel(), parent);
                tmp->setTrans(tr);
                return tmp;
            }
            else
            {
                index--;
            }
        }
    }
    return NULL;
}

void StopGenState::Print(QXmlStreamWriter * writer)
{

    if(parameters.size()>0)
    {
        writer->writeTextElement("Parameters", parameters);
        //x+=this->parameters.toStdString();
    }
    set.Print();
}
std::string StopGenState::Print()
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
QStringList StopGenState::LoadFromXML(QXmlStreamReader * reader)
{
    bool wasSet = false;
    bool wasParam = false;
    QStringList errors;
    while (!reader->atEnd())
    {
          reader->readNextStartElement();
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

TreeItem * StopGenState::getChild(int i, TreeItem * parent)
{
    int index = i;
    if(!set.first.empty())
    {
        if(index==0)
        {
            TreeRobotSetItem * tmp = new TreeRobotSetItem(i, parent->getModel(), parent);
            tmp->setSet(set.first, true);
            return tmp;
        }
        else
        {
            index--;
        }
    }
    if(!set.second.empty())
    {
        if(index==0)
        {
            TreeRobotSetItem * tmp = new TreeRobotSetItem(i, parent->getModel(), parent);
            tmp->setSet(set.second, false);
            return tmp;
        }
        else
        {
            index--;
        }
    }
    if (parameters.size()>0)
    {
        if(index==0)
        {
            TreeTextItem * tmp = new TreeTextItem(i, parent->getModel(), parent);
            tmp->setNameAttr("Parameters", parameters);
            return tmp;
        }
        else
        {
            index--;
        }
    }
    foreach (Transition * tr, Transitions)
    {
        if (tr->startItem()==this)
        {
            if(index==0)
            {
                TreeTransItem * tmp = new TreeTransItem(i, parent->getModel(), parent);
                tmp->setTrans(tr);
                return tmp;
            }
            else
            {
                index--;
            }
        }
    }
    return NULL;
}

void sysInitState::Print(QXmlStreamWriter * writer)
{
    if(parameters.size()>0)
    {
        writer->writeTextElement("Parameters", parameters);
    }
    writer->writeStartElement("taskInit");
    if(transmitter<TRANSMITTERS_NUMBER||sensors.size()>0)
    {
        writer->writeStartElement("mp");
        if(isProper(transmitter))
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
std::string sysInitState::Print()
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
QStringList sysInitState::LoadFromXML(QXmlStreamReader * reader)
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
                  Transmitter index = (Transmitter)(getTransmitterTable().indexOf(reader->readElementText()));
                  if(isProper(index))
                  {
                      transmitter=index;
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


TreeItem * sysInitState::getChild(int i, TreeItem * parent)
{
    int index = i;
    if(isProper(transmitter))
    {
        if(index==0)
        {
            TreeTextItem * tmp = new TreeTextItem(i, parent->getModel(), parent);
            tmp->setNameAttr("Transmiter", QString().fromStdString(TRANSMITTER_TABLE[transmitter]));
            return tmp;
        }
        else
        {
            index--;
        }
    }
    foreach (Sensor sen, sensors)
    {
        if(index==0)
        {
            TreeTextItem * tmp = new TreeTextItem(i, parent->getModel(), parent);
            tmp->setNameAttr("Sensor", QString().fromStdString(SENSOR_TABLE[sen]));
            return tmp;
        }
        else
        {
            index--;
        }
    }
    foreach (genInit ini, inits)
    {
        if(index==0)
        {
            TreeInitItem * tmp = new TreeInitItem(i, parent->getModel(), parent);
            tmp->setInit(ini);
            return tmp;
        }
        else
        {
            index--;
        }
    }
    if (parameters.size()>0)
    {
        if(index==0)
        {
            TreeTextItem * tmp = new TreeTextItem(i, parent->getModel(), parent);
            tmp->setNameAttr("Parameters", parameters);
            return tmp;
        }
        else
        {
            index--;
        }
    }
    foreach (Transition * tr, Transitions)
    {
        if (tr->startItem()==this)
        {
            if(index==0)
            {
                TreeTransItem * tmp = new TreeTransItem(i, parent->getModel(), parent);
                tmp->setTrans(tr);
                return tmp;
            }
            else
            {
                index--;
            }
        }
    }
    return NULL;
}

void WaitState::Print(QXmlStreamWriter * writer)
{
    if(parameters.size()>0)
    {
        writer->writeTextElement("Parameters", parameters);
    }
    char tim[15];
    sprintf (tim, "%lld", Timespan);
    writer->writeTextElement("TimeSpan", QString().fromStdString(tim));
}

std::string WaitState::Print()
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
QStringList WaitState::LoadFromXML(QXmlStreamReader * reader)
{
    bool wasTimespan = false;
    bool wasParameters = false;
    QStringList errors;
    while (!reader->atEnd())
    {
          reader->readNextStartElement();
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

TreeItem * WaitState::getChild(int i, TreeItem * parent)
{
    int index = i;
    if(index==0)
    {
        TreeTextItem * tmp = new TreeTextItem(i, parent->getModel(), parent);
        char table[20];
        sprintf(table,"%lld", Timespan);
        tmp->setNameAttr("TimeSpan", table);
        return tmp;
    }
    else
    {
        index--;
    }
    foreach (Transition * tr, Transitions)
    {
        if (tr->startItem()==this)
        {
            if(index==0)
            {
                TreeTransItem * tmp = new TreeTransItem(i, parent->getModel(), parent);
                tmp->setTrans(tr);
                return tmp;
            }
            else
            {
                index--;
            }
        }
    }
    return NULL;
}

