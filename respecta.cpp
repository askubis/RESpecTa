
#include <QtGui>
#include <QLabel>

#include "respecta.h"
#include "baseState.h"
#include "diagramscene.h"
#include "Transition.h"
#include <cstdio>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>

#include "editWidget.h"
const int InsertTextButton = 10;

//TODO:
//zapisywanie ustawień widoku (pozycja, skala) - najlepiej do pliku .xml lub innego pliku powiazanego z nazwa

//TODO:
//panel boczny z wypisywaniem wszystkiego

//TODO:
//zmiana stanu kursora przy przesuwaniu/wstawianiu


RESpecTa::RESpecTa(Model * newmod)
{
    mod=newmod;

    createFileMenu();
    createEditMenu();
    createOptionsMenu();
    createHelpMenu();
    //createActions();
    //createToolBox();

    scene = new DiagramScene(itemMenu, this, mod);
    scene->setSceneRect(QRectF(0, 0, 5000, 5000));
    connect(scene, SIGNAL(itemInserted(BaseState*)),this, SLOT(itemInserted(BaseState*)));
    connect(scene, SIGNAL(itemSelected(QGraphicsItem*)),this, SLOT(itemSelected(QGraphicsItem*)));
    connect(scene, SIGNAL(lineInserted(Transition *)), this, SLOT(lineInserted(Transition *)));
    connect(scene, SIGNAL(reportError(QString)), this, SLOT(reportError(QString)));
    createToolbars();

    //myGraph = new MyGraphType();
    //subtasks = new std::map<std::string, MyGraphType*> ();

    //subtasks->insert(std::make_pair<QString, MyGraphType *>("kopytko", NULL));

    transDial = new TransDialog(this, mod);
    connect(transDial, SIGNAL(reportError(QString)), this, SLOT(reportError(QString)));


    subDialog = new SubtaskDialog(this, mod);
    connect(subDialog, SIGNAL(changed()), this, SLOT(SubtasksChanged()));
    connect(subDialog, SIGNAL(reportError(QString)), this, SLOT(reportError(QString)));

    editWidget = new EditWidget(this, mod);
    connect(editWidget, SIGNAL(reportError(QString)), this, SLOT(reportError(QString)));
    connect(this, SIGNAL(itemSelectedSig(QGraphicsItem *)), editWidget, SLOT(itemSelected(QGraphicsItem *)));
   // editWidget->setGeometry(QRectF(0, 0, 5000, 5000));
    editWidget->resize(10,800);


    QHBoxLayout *layout = new QHBoxLayout;
    //layout->addWidget(toolBox);
    view = new QGraphicsView(scene);
    layout->addWidget(view);
    layout->addWidget(editWidget);

    QWidget *widget = new QWidget;
    widget->setLayout(layout);

    setCentralWidget(widget);
    setWindowTitle(tr("RESpecTa"));
    setUnifiedTitleAndToolBarOnMac(true);

    currentSubtask="MAIN";


}


void RESpecTa::createEditMenu()
{
    toFrontAction = new QAction(QIcon(":/images/bringtofront.png"),
                                tr("Bring to &Front"), this);
    toFrontAction->setShortcut(tr("Ctrl+F"));
    toFrontAction->setStatusTip(tr("Bring item to front"));
    connect(toFrontAction, SIGNAL(triggered()),
            this, SLOT(bringToFront()));

    sendBackAction = new QAction(QIcon(":/images/sendtoback.png"),
                                 tr("Send to &Back"), this);
    sendBackAction->setShortcut(tr("Ctrl+B"));
    sendBackAction->setStatusTip(tr("Send item to back"));
    connect(sendBackAction, SIGNAL(triggered()),
        this, SLOT(sendToBack()));

    deleteAction = new QAction(QIcon(":/images/delete.png"),
                               tr("&Delete"), this);
    deleteAction->setShortcut(tr("Delete"));
    deleteAction->setStatusTip(tr("Delete item from diagram"));
    connect(deleteAction, SIGNAL(triggered()),
        this, SLOT(deleteItem()));

    insertEndStateAction = new QAction(QIcon(":/images/_END_image.jpg"),
                               tr("&End"), this);
    insertEndStateAction->setShortcut(tr("End"));
    insertEndStateAction->setStatusTip(tr("Insert End state for main task or subtask"));
    connect(insertEndStateAction, SIGNAL(triggered()),
        this, SLOT(addEndState()));

    showTransitions = new QAction(tr("&Transitions"), this);
    showTransitions->setShortcut(tr("Home"));
    showTransitions->setStatusTip(tr("Show transitions of this State"));
    connect(showTransitions, SIGNAL(triggered()),
        this, SLOT(EditTransitionsOfState()));


    itemMenu = menuBar()->addMenu(tr("&Edit"));
    itemMenu->addAction(deleteAction);
    itemMenu->addSeparator();
    itemMenu->addAction(toFrontAction);
    itemMenu->addAction(sendBackAction);
    itemMenu->addAction(showTransitions);

}

void RESpecTa::createOptionsMenu()
{
    editSubtasks = new QAction(tr("Edit subtasks"), this);
    editSubtasks->setShortcut(tr("Ctrl+E"));
    editSubtasks->setStatusTip(tr("Edit names of the subtasks"));
    connect(editSubtasks, SIGNAL(triggered()),
            this, SLOT(OpenSubtaskEditDialog()));



    itemMenu = menuBar()->addMenu(tr("&Options"));
    itemMenu->addAction(editSubtasks);
}

void RESpecTa::OpenSubtaskEditDialog()
{
    subDialog->reloadName();
    subDialog->exec();
}

void RESpecTa::SubtasksChanged()
{
    emit refreshWidgets();
}

void RESpecTa::createFileMenu()
{
    exitAction = new QAction(tr("&Quit"), this);
    exitAction->setShortcuts(QKeySequence::Quit);
    exitAction->setStatusTip(tr("Quit RESpecTa"));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

    saveAction = new QAction(tr("&Save"), this);
    saveAction->setShortcuts(QKeySequence::Save);
    saveAction->setStatusTip(tr("save to file"));
    connect(saveAction, SIGNAL(triggered()), this, SLOT(save()));

    saveAsAction = new QAction(tr("S&ave As"), this);
    saveAsAction->setShortcuts(QKeySequence::SaveAs);
    saveAsAction->setStatusTip(tr("save to specific file"));
    connect(saveAsAction, SIGNAL(triggered()), this, SLOT(SaveAs()));

    loadAction = new QAction(tr("&Load"), this);
    loadAction->setShortcuts(QKeySequence::Open);
    loadAction->setStatusTip(tr("Load a file"));
    connect(loadAction, SIGNAL(triggered()), this, SLOT(Load()));


    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(exitAction);
    fileMenu->addAction(saveAction);
    fileMenu->addAction(saveAsAction);
    fileMenu->addAction(loadAction);
}

void RESpecTa::Load()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, tr("Are you sure?"),
                                    "Do you want to save your work before loading?",
                                    QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
    if (reply == QMessageBox::Yes)
    {
        bool tmp = this->SaveAs();
        if (tmp)
        {

        }
        else
        {
            return;
        }
    }
    else if (reply == QMessageBox::No)
        ;
    else
        return;


    QString tmp;
    QString LoadName = QFileDialog::getOpenFileName(this,
                                tr("Loading file"),
                                tmp,
                                tr("XML Files (*.xml)"));
    if(!LoadName.isEmpty())
    {
        QString tmpName = LoadName;
        int ind = tmpName.lastIndexOf('/');
        tmpName.truncate(ind+1);
        SaveFolder = tmpName;
        mod->setSaveFolder(SaveFolder);
        LoadName.remove(0,ind+1);//delete beginning till the last /
        SaveName = LoadName;
        LoadFile(LoadName);
    }
}

void RESpecTa::LoadFile(QString fileName)
{
    mod->deleteAll();

    QString subName = fileName;
    subName.chop(4);//delete .xml
    QString logPath =SaveFolder+subName;
    logPath.append(".log");
    int ind = subName.lastIndexOf('/');
    subName.remove(0,ind+1);//delete beginning till the last /

    QStringList errors;


    mod->setMainName(subName);

    errors+=LoadStates(fileName);

    errors+=LoadTransitions(fileName);

    errors+=mod->checkIfOK();

    if(errors.size()==0)
    {

    }
    else if (errors.size()<=5)
    {
        foreach(QString x, errors)
        {
           reportError(x);
        }
    }
    else
    {
        char tab[200];
        sprintf(tab, "There were %d errors while loading,\nto see them please see the log:\n%s", errors.size(), logPath.toStdString().c_str());
        reportError(QString(tab));
        QFile file(logPath.toStdString().c_str());
        if(!file.open(QIODevice::WriteOnly))
            qDebug()<<"Error opening the file";
        QTextStream streamToWrite(&file);
        foreach(QString x, errors)
        {
            const char* test = x.toStdString().c_str();
            streamToWrite<<test;
            streamToWrite<<"\n";
        }        
        file.close();
    }


    emit refreshWidgets();
}

QStringList RESpecTa::LoadStates(QString FileName)
{
QStringList errors;
    QString filename = QString(SaveFolder)+FileName;
    std::cout<<"FILE state load::::::::::::::::::::::::::::;"<<filename.toStdString()<<std::endl;
    //QString subName = filename;
    QString GraphName = FileName;
    GraphName.chop(4);
    QFile* file = new QFile(filename);
    file->open( QIODevice::ReadOnly);
    QXmlStreamReader * reader = new QXmlStreamReader(file);
    while (!reader->atEnd())
    {
          reader->readNextStartElement();
std::string startEnd = "START";
if(reader->isEndElement())startEnd="END";


          std::cout<<startEnd<<" MainLoop State: "<<reader->name().toString().toStdString()<<std::endl;
if(reader->isEndDocument())std::cout<<"ENDDOC"<<std::endl;
          if(reader->name().toString()=="Graphics"&&reader->isStartElement())
          {
              errors+=this->loadGraphics(reader);
          }
          if(reader->name().toString()=="State")
          {
              if(reader->attributes().hasAttribute("id")&&reader->attributes().hasAttribute("type"))
              {
                  BaseState * state=NULL;
                  StateType type;
                  std::cout<<"HasID "<<reader->attributes().value("id").toString().toStdString()<<std::endl;
                  std::cout<<"HasTYPE "<<reader->attributes().value("type").toString().toStdString()<<std::endl;
                  int index = (getStateTypeTable().indexOf(reader->attributes().value("type").toString()));
                  if(index<STATE_TYPES_NUMBER)
                  {
                       type = (StateType)index;
                  }
                  //else - //in switch
                  std::cout<<"TYPE "<<type<<std::endl;
                  switch (type)
                  {
                      case 0:
                          state = new sysInitState();
                          break;
                      case 1:
                          state = new RunGenState();
                          break;
                      case 2:
                          state = new EmptyGenForSetState();
                          break;
                      case 3:
                          state = new EmptyGenState();
                          break;
                      case 4:
                          state = new WaitState();
                          break;
                      case 5:
                          state = new StopGenState();
                          break;
                      case 6:
                          state = new InitiateSensorState();
                          break;
                      case 7:
                          state = new GetSensorState();
                          break;
                      default:
                        if(reader->attributes().value("type").toString()==QString(""))
                         {
                            state = new StopState();
                         }
                        else
                        {
                            char linenum[30];
                            sprintf(linenum,"; line: %lld", reader->lineNumber());
                            errors.push_back(QString("Unknown type of State")+=linenum);
                        }
                      break;
                  };
                  if(state!=NULL)
                  {
                      QString stateName = reader->attributes().value("id").toString();
if(!mod->checkNameAvailable(stateName) && stateName.toLower()!="_end_")
{
    char linenum[30];
    sprintf(linenum,"; line: %lld", reader->lineNumber());
    errors+=(QString("This state name is already taken: ")+=stateName)+=linenum;
    reader->readElementText();
    delete state;
    continue;
}
if(stateName.toLower()=="init" ^ type==SYSTEM_INITIALIZATION)
{
    char linenum[30];
    sprintf(linenum,"; line: %lld", reader->lineNumber());
    errors+=QString("Only the SYSTEM INITIALIZATION statetype can have name INIT")+=linenum;
    reader->readElementText();
    delete state;
    continue;
}
if(stateName.contains("<<"))
{
    char linenum[30];
    sprintf(linenum,"; line: %lld", reader->lineNumber());
    errors+=(QString("The StateName cannot contain \"<<\""))+=linenum;
    reader->readElementText();
    delete state;
    continue;
}
if(stateName.contains("/"))
{
    char linenum[30];
    sprintf(linenum,"; line: %lld", reader->lineNumber());
    errors+=(QString("The StateName cannot contain \"/\""))+=linenum;
    reader->readElementText();
    delete state;
    continue;
}
if(type==-1)
{
    if(stateName.toLower()=="_stop_"||stateName.toLower()=="_end_")
    {
        state->setType((StateType)STATE_TYPES_NUMBER);//STOPSTATE
    }
    else
    {
        char linenum[30];
        sprintf(linenum,"; line: %lld", reader->lineNumber());
        errors+=QString("Bad State ID for stopState or unknown State Type")+=linenum;
        reader->readElementText();
        delete state;
        continue;
    }
}
else
{
    state->setType(type);
}

                    state->setName(stateName);
std::cout<<"LOADING STATE: "<<state->getName().toStdString()<<std::endl;
                    errors+= state->LoadFromXML(reader);
                    scene->setItemParams(state);
                    state->setToolTip(QString().fromStdString(state->Print()));
                    mod->addState(state, GraphName.toStdString());
                  }
                  else
                  {

                  }
              }
              else
              {

                  char linenum[30];
                  sprintf(linenum,"; line: %lld", reader->lineNumber());
                  errors.push_back(QString("No ID or Type in <State>")+=linenum);
                  reader->readElementText();

              }
          }
          else if (reader->name()=="include"&&reader->isStartElement())
          {
                   QString subtaskName = reader->attributes().value("href").toString();
if(subtaskName.contains("/"))
{
    int ind = subtaskName.lastIndexOf('/');
    subtaskName.remove(0,ind+1);//delete beginning till the last /
}
std::cout<<"subtask found "<<subtaskName.toStdString()<<std::endl;
                   subtaskName.chop(4);
                   mod->addSubtask(subtaskName);
                   subtaskName.append(".xml");
                   errors+=LoadStates(subtaskName);
          }
    }
    //errors+=reader->errorString();
    //std::cout<<"error "<<reader->lineNumber()<<std::endl;
    file->close();
    return errors;
}

QStringList RESpecTa::LoadTransitions(QString FileName)
{
    QString filename = QString(SaveFolder);
    filename+=FileName;
    QStringList errors;
    std::cout<<"FILE trans load::::::::::::::::::::::::::::;"<<filename.toStdString()<<std::endl;
    QFile* file = new QFile(filename);
    QString subName = filename;
    if(subName.endsWith(".xml"))subName.chop(4);//delete .xml
    int ind = subName.lastIndexOf('/');
    subName.remove(0,ind+1);//delete beginning till the last /
    file->open( QIODevice::ReadOnly);
    QXmlStreamReader * reader = new QXmlStreamReader(file);
    QString StateName;
    while (!reader->atEnd())
    {
          reader->readNextStartElement();
          std::cout<<"MainLoop Transition: "<<reader->name().toString().toStdString()<<std::endl;
          if(reader->name().toString()=="State"&&reader->isStartElement() && !mod->checkNameAvailable(reader->attributes().value("id").toString()))
          {
              StateName = reader->attributes().value("id").toString();
          }
          else if(reader->name().toString()=="State"&&reader->isEndElement())
          {
              StateName = "";
          }
          else if(reader->name().toString()=="transition"&&reader->isStartElement())
          {
              std::cout<<"LOADING TRANS"<<std::endl;
              if(StateName=="")
              {
                  char linenum[30];
                  sprintf(linenum,"; line: %lld", reader->lineNumber());
                  errors.push_back(QString("Unknown State while loading Transition")+=linenum);
              }
              else
              {
                  if(reader->attributes().hasAttribute("condition")&&reader->attributes().hasAttribute("target"))
                  {
                      QString subtask;
                      QString condition = reader->attributes().value("condition").toString();
                      QString target = reader->attributes().value("target").toString();
                      QStringList strList = target.split(">>");
                      if(strList.size()>1)
                      {
                          subtask = strList[0];
                          target = strList[1];
                      }
                      else
                      {
                          target = strList[0];
                      }
                      std::cout<<"SUBTASKNAME WITHOUT XML:"<<subName.toStdString()<<std::endl;
                      BaseState * sourceState = mod->getState(StateName, subName.toStdString());
                      BaseState * targetState = mod->getState(target, subName.toStdString());
                      std::cout<<sourceState<<" "<<targetState<<std::endl;
                      if(sourceState!=NULL&&targetState!=NULL)
                      {
                          Transition * trans = new Transition(sourceState, targetState);
                          trans->setCondition(condition);
                          trans->setSubtask(subtask.toStdString());
if(mod->checkTransCondAvailabe(trans, condition))
{
    delete trans;
    char linenum[30];
    sprintf(linenum,"; line: %lld", reader->lineNumber());
    errors.push_back(QString("Transition condition is already used for the sourceState")+=linenum);
    continue;
}
                          if(mod->checkTransCondAvailabe(sourceState, condition))
                          {
                            scene->addItem(trans);
                            mod->tryInsertTransition(trans);
                            trans->updatePosition();
                            scene->setMode(DiagramScene::MoveItem);
                            trans->setToolTip(QString().fromStdString(trans->Print()));
                            trans->setZValue(-1000.0);
                            sourceState->addTransition(trans);
                            targetState->addTransition(trans);
                          }
                          else
                          {
                              delete trans;
                              char linenum[30];
                              sprintf(linenum,"; line: %lld", reader->lineNumber());
                              errors.push_back(QString("Transition between States in different subtasks")+=linenum);
                          }
                      }
                      else
                      {
                          char linenum[30];
                          sprintf(linenum,"; line: %lld", reader->lineNumber());
                          errors.push_back(QString("Start or End State not found in the map while loading transition")+=linenum);
                      }
                  }
                  else
                  {
                      char linenum[30];
                      sprintf(linenum,"; line: %lld", reader->lineNumber());
                      errors.push_back(QString("No condition or target in Transition")+=linenum);
                  }
              }
          }
          else if (reader->name()=="include")
          {
              QString subtaskName = reader->attributes().value("href").toString();
              int ind = subtaskName.lastIndexOf('/');
              subtaskName.remove(0,ind+1);//delete beginning till the last /
              errors+=LoadTransitions(subtaskName);
          }
    }
    return errors;
}




void RESpecTa::save()
{
    //get path
    if(SaveName.isEmpty())
    {
        SaveAs();
    }
    else
    {
        mod->setSaveFolder(SaveFolder);
        mod->save(SaveName);
    }
}

bool RESpecTa::SaveAs()
{
    QString tmp;
    SaveName = QFileDialog::getSaveFileName(this,
                                tr("Save to file"),
                                tmp,
                                tr("XML Files (*.xml)"));
    if (!SaveName.isEmpty())
    {
        QString tmpName = SaveName;
        int ind = tmpName.lastIndexOf('/');
        tmpName.truncate(ind+1);
        SaveFolder = tmpName;
        mod->setSaveFolder(SaveFolder);

        if(SaveName.endsWith(".xml"))
            mod->save(SaveName);
        else
        {
            SaveName.append(".xml");
            QFile * tmp = new QFile(SaveName);
            if(tmp->exists())
            {
                QMessageBox::StandardButton reply;
                reply = QMessageBox::question(this, tr("Warning"),
                                                QString("The file exists,\nare you sure want\nto overwrite it"),
                                                QMessageBox::Yes | QMessageBox::Abort);
                if(reply==QMessageBox::Abort)
                {
                    return false;
                }

            }
            mod->save(SaveName);
        }
    }
    else
    {
        return false;
    }
    emit refreshWidgets();
    return true;
}

void RESpecTa::createHelpMenu()
{

    aboutAction = new QAction(tr("A&bout"), this);
    aboutAction->setShortcut(tr("Ctrl+B"));
    connect(aboutAction, SIGNAL(triggered()),
            this, SLOT(about()));

    aboutMenu = menuBar()->addMenu(tr("&Help"));
    aboutMenu->addAction(aboutAction);

}


void RESpecTa::buttonGroupClicked(int id)
{
    QList<QAbstractButton *> buttons = buttonGroup->buttons();
    foreach (QAbstractButton *button, buttons) {
    if (buttonGroup->button(id) != button)
        button->setChecked(false);
    }
    if (id == InsertTextButton) {
        scene->setMode(DiagramScene::InsertText);
    } else {
        //scene->setItemType(BaseState::DiagramType(id));
        scene->setMode(DiagramScene::InsertItem);
    }
}

void RESpecTa::deleteItem()
{

    //check why there's a bug with deleting transitions attached to a deleted node
    foreach (QGraphicsItem *item, scene->selectedItems())
    {
        if (item->type() == Transition::Type)
        {
            Transition *transition = qgraphicsitem_cast<Transition *>(item);
            deleteTrans(transition);

        }
    }

    foreach (QGraphicsItem *item, scene->selectedItems())
    {
         if (item->type() == BaseState::Type)
         {
             BaseState * state = qgraphicsitem_cast<BaseState *>(item);
             deleteState(state);
         }
     }
    emit SignalDeleted();
}


void RESpecTa::deleteState(BaseState * state)
{
    foreach(Transition * transition, state->getTransitions())
    {
        deleteTrans(transition);
    }

    state->removeTransitions();

    mod->deleteState(state);

    scene->removeItem(state);

    delete state;
}

void RESpecTa::deleteTrans(Transition * trans)
{
    mod->deleteTransition(trans);

    scene->removeItem(trans);
    delete trans;

}



void RESpecTa::pointerGroupClicked(int)
{
    scene->setMode(DiagramScene::Mode(pointerTypeGroup->checkedId()));
}

void RESpecTa::bringToFront()
{
    if (scene->selectedItems().isEmpty())
        return;

    QGraphicsItem *selectedItem = scene->selectedItems().first();
    QList<QGraphicsItem *> overlapItems = selectedItem->collidingItems();

    qreal zValue = 0;
    foreach (QGraphicsItem *item, overlapItems) {
        if (item->zValue() >= zValue &&
            item->type() == BaseState::Type)
            zValue = item->zValue() + 0.1;
    }
    selectedItem->setZValue(zValue);
    if(selectedItem->type()==BaseState::Type)
    {
        BaseState * state = (BaseState*) selectedItem;
        state->getNameTextItem()->setZValue(zValue+0.1);
    }
}

void RESpecTa::sendToBack()
{
    if (scene->selectedItems().isEmpty())
        return;

    QGraphicsItem *selectedItem = scene->selectedItems().first();
    QList<QGraphicsItem *> overlapItems = selectedItem->collidingItems();

    qreal zValue = 0;
    foreach (QGraphicsItem *item, overlapItems) {
        if (item->zValue() <= zValue &&
            item->type() == BaseState::Type)
            zValue = item->zValue() - 0.2;
    }
    selectedItem->setZValue(zValue);
    if(selectedItem->type()==BaseState::Type)
    {
        BaseState * state = (BaseState*) selectedItem;
        state->getNameTextItem()->setZValue(zValue+0.1);
    }
}

void RESpecTa::itemInserted(BaseState *item)
{

    pointerTypeGroup->button(int(DiagramScene::MoveItem))->setChecked(true);
    scene->setMode(DiagramScene::Mode(pointerTypeGroup->checkedId()));
    //Vertex v_new;

    //item->setSubtaskName(currentSubtask);
    if(currentSubtask.toStdString()==mod->getMainName() && item->getName().toLower()==QString("_end_"))
    {
        item->setName(QString("_STOP_"));
    }
    bool check = mod->addState(item, currentSubtask.toStdString());
    if(check)
    {
        item->setToolTip(QString().fromStdString(item->Print()));
    }
    else
    {
        scene->removeItem(item);
        delete item;
    }

    //item->setStatusTip(item->Print());


    //boost::remove_vertex(v_new, (*myGraph));
/*  property_map<MyGraphType, state_t>::type State = get(state_t(), (*myGraph));
    BaseState * tmp = boost::get(State, ((boost::vertices((*myGraph))).first)[v_new]);
    delete tmp;
    boost::remove_vertex(v_new, (*myGraph));
    DELETING THE VERTEX
    */



    //buttonGroup->button(int(item->diagramType()))->setChecked(false);
}

bool RESpecTa::lineInserted(Transition *line)
{

    bool test = mod->tryInsertTransition(line);
    if(test)
    {
        emit itemSelectedSig(line);
    }
    return test;
}

void RESpecTa::sceneScaleChanged(const QString &scale)
{
    double newScale = scale.left(scale.indexOf(tr("%"))).toDouble() / 100.0;
    QMatrix oldMatrix = view->matrix();
    view->resetMatrix();
    view->translate(oldMatrix.dx(), oldMatrix.dy());
    view->scale(newScale, newScale);
}

void RESpecTa::itemColorChanged()
{
    fillAction = qobject_cast<QAction *>(sender());
    fillColorToolButton->setIcon(createColorToolButtonIcon(
                 ":/images/floodfill.png",
                 qVariantValue<QColor>(fillAction->data())));
    fillButtonTriggered();
}

void RESpecTa::lineColorChanged()
{
    lineAction = qobject_cast<QAction *>(sender());
    lineColorToolButton->setIcon(createColorToolButtonIcon(
                 ":/images/linecolor.png",
                 qVariantValue<QColor>(lineAction->data())));
    lineButtonTriggered();
}

void RESpecTa::fillButtonTriggered()
{
    scene->setItemColor(qVariantValue<QColor>(fillAction->data()));
}

void RESpecTa::lineButtonTriggered()
{
    scene->setLineColor(qVariantValue<QColor>(lineAction->data()));
}


void RESpecTa::itemSelected(QGraphicsItem *item)
{
    if(item->type()==BaseState::Type)
    {
        BaseState * state = qgraphicsitem_cast<BaseState *>(item);
        if(state->getName().toLower()=="_stop_"||state->getName().toLower()=="_end_")
        {
            emit SignalDeleted();
        }
        else
        {
            emit itemSelectedSig(item);
        }
    }
    else
    {
        emit itemSelectedSig(item);
    }
}

void RESpecTa::about()
{
    QMessageBox::about(this, tr("About Diagram Scene"),
                       tr("The <b>Diagram Scene</b> example shows "
                          "use of the graphics framework."));
}

void RESpecTa::createToolBox()
{
    //buttonGroup = new QButtonGroup(this);
    //buttonGroup->setExclusive(false);
    //connect(buttonGroup, SIGNAL(buttonClicked(int)),
    //        this, SLOT(buttonGroupClicked(int)));
    //QGridLayout *layout = new QGridLayout;
    //layout->addWidget(createCellWidget(tr("Conditional"),
    //                           BaseState::Conditional), 0, 0);
    //layout->addWidget(createCellWidget(tr("State")),0, 1);
    //layout->addWidget(createCellWidget(tr("Input/Output"),
    //                  BaseState::Io), 1, 0);


   /* QToolButton *textButton = new QToolButton;
    textButton->setCheckable(true);
    buttonGroup->addButton(textButton, InsertTextButton);
    textButton->setIcon(QIcon(QPixmap(":/images/textpointer.png")
                        .scaled(30, 30)));
    textButton->setIconSize(QSize(50, 50));*/
    /*QGridLayout *textLayout = new QGridLayout;
    textLayout->addWidget(textButton, 0, 0, Qt::AlignHCenter);
    textLayout->addWidget(new QLabel(tr("Text")), 1, 0, Qt::AlignCenter);*/
    /*QWidget *textWidget = new QWidget;
    textWidget->setLayout(textLayout);
    layout->addWidget(textWidget, 1, 1);*/

    //layout->setRowStretch(3, 10);
    //layout->setColumnStretch(2, 10);

    //QWidget *itemWidget = new QWidget;
    //itemWidget->setLayout(layout);

   /* backgroundButtonGroup = new QButtonGroup(this);
    connect(backgroundButtonGroup, SIGNAL(buttonClicked(QAbstractButton*)),
            this, SLOT(backgroundButtonGroupClicked(QAbstractButton*)));

    QGridLayout *backgroundLayout = new QGridLayout;
    backgroundLayout->addWidget(createBackgroundCellWidget(tr("Blue Grid"),
                ":/images/background1.png"), 0, 0);
    backgroundLayout->addWidget(createBackgroundCellWidget(tr("White Grid"),
                ":/images/background2.png"), 0, 1);
    backgroundLayout->addWidget(createBackgroundCellWidget(tr("Gray Grid"),
                    ":/images/background3.png"), 1, 0);
    backgroundLayout->addWidget(createBackgroundCellWidget(tr("No Grid"),
                ":/images/background4.png"), 1, 1);

    backgroundLayout->setRowStretch(2, 10);
    backgroundLayout->setColumnStretch(2, 10);

    QWidget *backgroundWidget = new QWidget;
    backgroundWidget->setLayout(backgroundLayout);*/



    //toolBox = new QToolBox;
    //toolBox->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Ignored));
    //toolBox->setMinimumWidth(itemWidget->sizeHint().width());
    //toolBox->addItem(itemWidget, tr("Basic Flowchart Shapes"));
    //toolBox->addItem(backgroundWidget, tr("Backgrounds"));
}

void RESpecTa::createActions()
{

    /*boldAction = new QAction(QIcon(":images/bold.png"),
                             tr("Bold"), this);
    boldAction->setCheckable(true);
    boldAction->setShortcut(tr("Ctrl+G"));
    connect(boldAction, SIGNAL(triggered()),
            this, SLOT(handleFontChange()));

    italicAction = new QAction(QIcon(":/images/italic.png"),
                               tr("Italic"), this);
    italicAction->setCheckable(true);
    italicAction->setShortcut(tr("Ctrl+I"));
    connect(italicAction, SIGNAL(triggered()),
            this, SLOT(handleFontChange()));

    underlineAction = new QAction(QIcon(":/images/underline.png"),
                                  tr("Underline"), this);
    underlineAction->setCheckable(true);
    underlineAction->setShortcut(tr("Ctrl+U"));
    connect(underlineAction, SIGNAL(triggered()),
            this, SLOT(handleFontChange()));*/


}



void RESpecTa::createToolbars()
{
    editToolBar = addToolBar(tr("Edit"));
    editToolBar->addAction(deleteAction);
    editToolBar->addAction(toFrontAction);
    editToolBar->addAction(sendBackAction);

    editToolBar->addAction(insertEndStateAction);
    /*fontCombo = new QFontComboBox();
    connect(fontCombo, SIGNAL(currentFontChanged(QFont)),
            this, SLOT(currentFontChanged(QFont)));

    fontSizeCombo = new QComboBox;
    fontSizeCombo->setEditable(true);
    for (int i = 8; i < 30; i = i + 2)
        fontSizeCombo->addItem(QString().setNum(i));
    QIntValidator *validator = new QIntValidator(2, 64, this);
    fontSizeCombo->setValidator(validator);
    connect(fontSizeCombo, SIGNAL(currentIndexChanged(QString)),
            this, SLOT(fontSizeChanged(QString)));

    fontColorToolButton = new QToolButton;
    fontColorToolButton->setPopupMode(QToolButton::MenuButtonPopup);
    fontColorToolButton->setMenu(createColorMenu(SLOT(textColorChanged()),
                                                 Qt::black));
    textAction = fontColorToolButton->menu()->defaultAction();
    fontColorToolButton->setIcon(createColorToolButtonIcon(
    ":/images/textpointer.png", Qt::black));
    fontColorToolButton->setAutoFillBackground(true);
    connect(fontColorToolButton, SIGNAL(clicked()),
            this, SLOT(textButtonTriggered()));
*/
    /*fillColorToolButton = new QToolButton;
    fillColorToolButton->setPopupMode(QToolButton::MenuButtonPopup);
    fillColorToolButton->setMenu(createColorMenu(SLOT(itemColorChanged()),
                         Qt::white));
    fillAction = fillColorToolButton->menu()->defaultAction();
    fillColorToolButton->setIcon(createColorToolButtonIcon(
    ":/images/floodfill.png", Qt::white));
    connect(fillColorToolButton, SIGNAL(clicked()),
            this, SLOT(fillButtonTriggered()));*/


    /*lineColorToolButton = new QToolButton;
    lineColorToolButton->setPopupMode(QToolButton::MenuButtonPopup);
    lineColorToolButton->setMenu(createColorMenu(SLOT(lineColorChanged()),
                                 Qt::black));
    lineAction = lineColorToolButton->menu()->defaultAction();
    lineColorToolButton->setIcon(createColorToolButtonIcon(
        ":/images/linecolor.png", Qt::black));
    connect(lineColorToolButton, SIGNAL(clicked()),
            this, SLOT(lineButtonTriggered()));*/

    //textToolBar = addToolBar(tr("Font"));
    //textToolBar->addWidget(fontCombo);
    //textToolBar->addWidget(fontSizeCombo);
    //textToolBar->addAction(boldAction);
    //textToolBar->addAction(italicAction);
    //textToolBar->addAction(underlineAction);

    /*colorToolBar = addToolBar(tr("Color"));
    //colorToolBar->addWidget(fontColorToolButton);
    colorToolBar->addWidget(fillColorToolButton);
    colorToolBar->addWidget(lineColorToolButton);*/

    QToolButton *pointerButton = new QToolButton;
    pointerButton->setCheckable(true);
    pointerButton->setChecked(true);
    pointerButton->setIcon(QIcon(":/images/pointer.png"));
    //QToolButton *linePointerButton = new QToolButton;
    //linePointerButton->setCheckable(true);
    //linePointerButton->setIcon(QIcon(":/images/linepointer.png"));

    pointerTypeGroup = new QButtonGroup(this);
    pointerTypeGroup->addButton(pointerButton, int(DiagramScene::MoveItem));
    //pointerTypeGroup->addButton(linePointerButton,
    //                            int(DiagramScene::InsertLine));
    connect(pointerTypeGroup, SIGNAL(buttonClicked(int)),
            this, SLOT(pointerGroupClicked(int)));

    sceneScaleCombo = new QComboBox;
    QStringList scales;
    scales << tr("50%") << tr("75%") << tr("100%") << tr("125%") << tr("150%");
    sceneScaleCombo->addItems(scales);
    sceneScaleCombo->setCurrentIndex(2);
    connect(sceneScaleCombo, SIGNAL(currentIndexChanged(QString)),
            this, SLOT(sceneScaleChanged(QString)));

    pointerToolbar = addToolBar(tr("Pointer type"));
    pointerToolbar->addWidget(pointerButton);
    //pointerToolbar->addWidget(linePointerButton);
    pointerToolbar->addWidget(sceneScaleCombo);
}

QWidget *RESpecTa::createBackgroundCellWidget(const QString &text,
                        const QString &image)
{
    QToolButton *button = new QToolButton;
    button->setText(text);
    button->setIcon(QIcon(image));
    button->setIconSize(QSize(50, 50));
    button->setCheckable(true);
    backgroundButtonGroup->addButton(button);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(button, 0, 0, Qt::AlignHCenter);
    layout->addWidget(new QLabel(text), 1, 0, Qt::AlignCenter);

    QWidget *widget = new QWidget;
    widget->setLayout(layout);

    return widget;
}

QWidget *RESpecTa::createCellWidget(const QString &text)
{

    BaseState item;
    QIcon icon(item.image());

    QToolButton *button = new QToolButton;
    button->setIcon(icon);
    button->setIconSize(QSize(50, 50));
    button->setCheckable(true);
    buttonGroup->addButton(button);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(button, 0, 0, Qt::AlignHCenter);
    layout->addWidget(new QLabel(text), 1, 0, Qt::AlignCenter);

    QWidget *widget = new QWidget;
    widget->setLayout(layout);

    return widget;
}

QMenu *RESpecTa::createColorMenu(const char *slot, QColor defaultColor)
{
    QList<QColor> colors;
    colors << Qt::black << Qt::white << Qt::red << Qt::blue << Qt::yellow;
    QStringList names;
    names << tr("black") << tr("white") << tr("red") << tr("blue")
          << tr("yellow");

    QMenu *colorMenu = new QMenu(this);
    for (int i = 0; i < colors.count(); ++i) {
        QAction *action = new QAction(names.at(i), this);
        action->setData(colors.at(i));
        action->setIcon(createColorIcon(colors.at(i)));
        connect(action, SIGNAL(triggered()),
                this, slot);
        colorMenu->addAction(action);
        if (colors.at(i) == defaultColor) {
            colorMenu->setDefaultAction(action);
        }
    }
    return colorMenu;
}

QIcon RESpecTa::createColorToolButtonIcon(const QString &imageFile,
                        QColor color)
{
    QPixmap pixmap(50, 80);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    QPixmap image(imageFile);
    QRect target(0, 0, 50, 60);
    QRect source(0, 0, 42, 42);
    painter.fillRect(QRect(0, 60, 50, 80), color);
    painter.drawPixmap(target, image, source);

    return QIcon(pixmap);
}

QIcon RESpecTa::createColorIcon(QColor color)
{
    QPixmap pixmap(20, 20);
    QPainter painter(&pixmap);
    painter.setPen(Qt::NoPen);
    painter.fillRect(QRect(0, 0, 20, 20), color);

    return QIcon(pixmap);
}

void RESpecTa::InsertState(BaseState * newState)
{

    bool not_abort = mod->checkNameAvailable(newState->getName());

    if(!not_abort)
    {
        reportError(QString("State with that name already exists"));
    }
    else
    {
        scene->setMode(DiagramScene::InsertItem);
        scene->setToInsertState(newState);
    }
}

void RESpecTa::insertTransition(std::pair<QString,QString> thePair)
{
    scene->setMode(DiagramScene::InsertLine);
    scene->setTransitionAttributes(thePair);
}


void RESpecTa::NewSubtaskInserted(QString newName)
{
    mod->addSubtask(newName);
}

void RESpecTa::selectedSubtaskName(QString newString)
{
    currentSubtask=newString;
}

void RESpecTa::reportError(QString msgString)
{
    QMessageBox::information(this, QString("Error"), msgString);
}

void RESpecTa::addEndState()
{
    StopState * tmp = new StopState();
    tmp->setType(StateType(STATE_TYPES_NUMBER));
    tmp->setName("_END_");
    scene->setMode(DiagramScene::InsertItem);
    scene->setToInsertState(tmp);
}
void RESpecTa::EditTransitionsOfState()
{
    if(scene->selectedItems().isEmpty())return;
    if(scene->selectedItems().first()->type()==BaseState::Type)
    {
        BaseState * state = qgraphicsitem_cast<BaseState *>(scene->selectedItems().first());
        transDial->openForAState(state);
        //transDial->setModal(true);
        transDial->exec();
    }
    return;
}

void RESpecTa::ReplaceState(BaseState * oldState, BaseState * newState, QString oldStateName)
{
    bool check = mod->ReplaceState(oldState,newState, oldStateName);//need to use oldStateName given, cannot check it if the state was deleted
    if(check)
    {
        QList<Transition *> TranList = oldState->getTransitions();
        foreach(Transition * T, TranList)
        {
            if(T->startItem() == oldState)T->setStartItem(newState);
            if(T->endItem() == oldState)T->setEndItem(newState);
            newState->addTransition(T);
        }
        newState->setPos(oldState->pos().x(), oldState->pos().y());
        scene->removeItem(oldState);
        scene->setItemParams(newState);
        newState->setToolTip(QString().fromStdString(newState->Print()));
        delete oldState;
        scene->selectedItems().clear();
        scene->selectedItems().push_back(newState);
        newState->setSelected(true);
        emit itemSelected(newState);
    }

    //state could be somehow chosen to be edited...
}


void RESpecTa::closeEvent(QCloseEvent *event)
{

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, tr("Are you sure?"),
                                    "Do you want to save your work before closing?",
                                    QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
    if (reply == QMessageBox::Yes)
    {
        bool tmp = this->SaveAs();
        if (tmp)
        {

        }
        else
        {
            event->ignore();
        }
    }
    else if (reply == QMessageBox::No)
        ;
    else
        event->ignore();
}


void RESpecTa::SaveGraphicsAttributes(QXmlStreamWriter * writer)
{

    writer->writeStartElement("Graphics");
    char tab[20];

    sprintf(tab, "%d", view->x());
    writer->writeTextElement("PosX", QString(tab));
    sprintf(tab, "%d", view->y());
    writer->writeTextElement("PosY", QString(tab));
    QString scale = sceneScaleCombo->currentText();
    double newScale = scale.left(scale.indexOf(tr("%"))).toDouble();
    sprintf(tab, "%lf", newScale);
    writer->writeTextElement("Scale", QString(tab));

    writer->writeEndElement();
    return;
}

QStringList RESpecTa::loadGraphics(QXmlStreamReader * reader)
{
    bool wasX = false;
    bool wasY = false;
    bool wasScale = false;
    QStringList errors;
    while (!reader->atEnd())
    {
          reader->readNextStartElement();
          std::cout<<"Graphics: "<<reader->name().toString().toStdString()<<std::endl;
          if(reader->name()=="Graphics"&&reader->isEndElement())
          {
              if(!wasScale||!wasX||!wasY)
              {
                  char linenum[30];
                  sprintf(linenum,"; line: %lld", reader->lineNumber());
                  errors.push_back(QString("The X, Y or Sacle parameter was not defined for the Graphics")+=linenum);
              }
              return errors;
          }
          else if(reader->name()=="PosX"&&reader->isStartElement())
          {
              wasX=true;
              double X = reader->readElementText().toDouble();
              view->setGeometry(X, view->y(), view->width(), view->height());

          }
          else if(reader->name()=="PosY"&&reader->isStartElement())
          {
              wasY=true;
              double Y = reader->readElementText().toDouble();
              view->setGeometry(view->x(), Y, view->width(), view->height());
          }
          else if (reader->name()=="Scale"&&reader->isStartElement())
          {
              wasScale=true;
              this->sceneScaleChanged(reader->readElementText());
              //TODO: change combo
          }

          else if (reader->isStartElement())
          {
              char linenum[30];
              sprintf(linenum,"; line: %lld", reader->lineNumber());
              errors.push_back((QString("unexpected name while reading wait <State>: ")+=reader->name())+=linenum);
          }

    }
    if(!wasScale||!wasX||!wasY)
    {
        char linenum[30];
        sprintf(linenum,"; line: %lld", reader->lineNumber());
        errors.push_back(QString("The X, Y or Sacle parameter was not defined for the Graphics")+=linenum);
    }
    return errors;
}


