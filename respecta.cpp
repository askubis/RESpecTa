
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
    createToolbars();

    transDial = new TransDialog(this, mod);
    connect(transDial, SIGNAL(reportError(QString)), this, SLOT(reportError(QString)));


    subDialog = new SubtaskDialog(this, mod);
    connect(subDialog, SIGNAL(changed(QString, QString)), this, SLOT(SubtaskChanged(QString, QString)));
    connect(subDialog, SIGNAL(added(QString)), this, SLOT(SubtaskAdded(QString)));
    connect(subDialog, SIGNAL(removed(QString)), this, SLOT(SubtaskRemoved(QString)));
    connect(subDialog, SIGNAL(reportError(QString)), this, SLOT(reportError(QString)));

    editWidget = new EditWidget(this, mod);
    connect(editWidget, SIGNAL(reportError(QString)), this, SLOT(reportError(QString)));
    connect(this, SIGNAL(itemSelectedSig(QGraphicsItem *)), editWidget, SLOT(itemSelected(QGraphicsItem *)));
   // editWidget->setGeometry(QRectF(0, 0, 5000, 5000));
    editWidget->resize(10,800);

    currentSubtask="MAIN";

    scenes[currentSubtask] = new DiagramScene(itemMenu, this, mod);
    scenes[currentSubtask]->setSceneRect(QRectF(0, 0, 5000, 5000));

    connect(scenes[currentSubtask], SIGNAL(itemInserted(BaseState*)),this, SLOT(itemInserted(BaseState*)));
    connect(scenes[currentSubtask], SIGNAL(itemSelected(QGraphicsItem*)),this, SLOT(itemSelected(QGraphicsItem*)));
    connect(scenes[currentSubtask], SIGNAL(lineInserted(Transition *)), this, SLOT(lineInserted(Transition *)));
    connect(scenes[currentSubtask], SIGNAL(reportError(QString)), this, SLOT(reportError(QString)));


    QWidget * mainWidget = new QWidget();


    tabWidget = new QTabWidget;


    QHBoxLayout *layout = new QHBoxLayout;
    layouts[currentSubtask]=new QHBoxLayout;

    //layout->addWidget(toolBox);
    views[currentSubtask] = new QGraphicsView(scenes[currentSubtask]);
    layouts[currentSubtask]->addWidget(views[currentSubtask]);

    treeModel = new TreeModel( this, mod, mod->getMainName());

    QWidget * listWidget = new QWidget(this);
    QHBoxLayout *findLayout = new QHBoxLayout;
    QWidget * findWidget = new QWidget(listWidget);
    QVBoxLayout *listLayout = new QVBoxLayout;
    findLineEdit = new QLineEdit;
    findLayout->addWidget(findLineEdit);
    QPushButton * findButton = new QPushButton("Find");
    findLayout->addWidget(findButton);
    connect(findButton, SIGNAL(clicked()), this, SLOT(FindOnList()));

    findWidget->setLayout(findLayout);
    listLayout->addWidget(findWidget);
    listWidget->setLayout(listLayout);



    TreeView = new myTreeView(listWidget);
    TreeView->setModel(treeModel);
    listLayout->addWidget(TreeView);

    listWidget->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Expanding);
    layout->addWidget(listWidget);
    tabWidget->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    layout->addWidget(tabWidget);
    editWidget->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Expanding);
    layout->addWidget(editWidget);
    mainWidget->setLayout(layout);

    widgets[currentSubtask] = new QWidget;
    widgets[currentSubtask]->setLayout(layouts[currentSubtask]);
    //layouts[currentSubtask]

    tabWidget->addTab(widgets[currentSubtask], "MAIN");
    tabWidget->setMovable(true);


    connect(tabWidget, SIGNAL(currentChanged(int)), this, SLOT(TabChanged(int)));
    setCentralWidget(mainWidget);
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
                                 tr("Send to Bac&k"), this);
    sendBackAction->setShortcut(tr("Ctrl+K"));
    sendBackAction->setStatusTip(tr("Send item to back"));
    connect(sendBackAction, SIGNAL(triggered()),
        this, SLOT(sendToBack()));

    deleteAction = new QAction(QIcon(":/images/delete.png"),
                               tr("Delete"), this);
    deleteAction->setShortcut(tr("Delete"));
    deleteAction->setStatusTip(tr("Delete item from diagram"));
    connect(deleteAction, SIGNAL(triggered()),
        this, SLOT(deleteItem()));

    insertEndStateAction = new QAction(QIcon(":/images/_END_image.jpg"),
                               tr("&End"), this);
    insertEndStateAction->setShortcut(tr("Ctrl+E"));
    insertEndStateAction->setStatusTip(tr("Insert End state for main task or subtask"));
    connect(insertEndStateAction, SIGNAL(triggered()),
        this, SLOT(addEndState()));

    showTransitions = new QAction(tr("&Transitions"), this);
    showTransitions->setShortcut(tr("Ctrl+T"));
    showTransitions->setStatusTip(tr("Show transitions of this State"));
    connect(showTransitions, SIGNAL(triggered()),
        this, SLOT(EditTransitionsOfState()));

    QAction * GoToState = new QAction(tr("&Go To State"), this);
    GoToState->setShortcut(tr("Ctrl+G"));
    GoToState->setStatusTip(tr("Center on the state selected on the list"));
    connect(GoToState, SIGNAL(triggered()),
        this, SLOT(GoToState()));


    itemMenu = menuBar()->addMenu(tr("&Edit"));
    itemMenu->addAction(deleteAction);
    itemMenu->addSeparator();
    itemMenu->addAction(toFrontAction);
    itemMenu->addAction(sendBackAction);
    itemMenu->addAction(showTransitions);
    itemMenu->addAction(GoToState);

}

void RESpecTa::createOptionsMenu()
{
    editSubtasks = new QAction(tr("E&dit subtasks"), this);
    editSubtasks->setShortcut(tr("Ctrl+D"));
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

void RESpecTa::SubtaskAdded(QString newSubtask)
{

    scenes[newSubtask] = new DiagramScene(itemMenu, this, mod);
    scenes[newSubtask]->setSceneRect(QRectF(0, 0, 5000, 5000));

    connect(scenes[newSubtask], SIGNAL(itemInserted(BaseState*)),this, SLOT(itemInserted(BaseState*)));
    connect(scenes[newSubtask], SIGNAL(itemSelected(QGraphicsItem*)),this, SLOT(itemSelected(QGraphicsItem*)));
    connect(scenes[newSubtask], SIGNAL(lineInserted(Transition *)), this, SLOT(lineInserted(Transition *)));
    connect(scenes[newSubtask], SIGNAL(reportError(QString)), this, SLOT(reportError(QString)));

    layouts[newSubtask] = new QHBoxLayout;
    views[newSubtask] = new QGraphicsView(scenes[newSubtask]);
    layouts[newSubtask]->addWidget(views[newSubtask]);


    widgets[newSubtask] = new QWidget;
    widgets[newSubtask]->setLayout(layouts[newSubtask]);

    tabWidget->addTab(widgets[newSubtask], newSubtask);

    mod->addSubtask(newSubtask);

    emit refreshWidgets();
}

void RESpecTa::SubtaskRemoved(QString oldSubtask)
{
     mod->DeleteTask(oldSubtask);
    if(oldSubtask!=mod->getMainName())
    {
        std::map<QString,QHBoxLayout *>::iterator layoutIt = layouts.find(oldSubtask);
        delete (*layoutIt).second;
        layouts.erase(layoutIt);

        std::map<QString,QGraphicsView *>::iterator viewIt = views.find(oldSubtask);
        delete (*viewIt).second;
        views.erase(viewIt);

        std::map<QString,QWidget *>::iterator widgetIt = widgets.find(oldSubtask);
        delete (*widgetIt).second;
        widgets.erase(widgetIt);

        std::map<QString,DiagramScene *>::iterator sceneIt = scenes.find(oldSubtask);
        delete (*sceneIt).second;
        scenes.erase(sceneIt);


        int i;
        for(i = 0;i<tabWidget->count();i++)
        {
            if(tabWidget->tabText(i)==oldSubtask)
            {
                break;
            }
        }

        tabWidget->removeTab(i);
    }

    emit refreshWidgets();
}

void RESpecTa::SubtaskChanged(QString oldName, QString newName)
{
    if(oldName==currentSubtask)currentSubtask=newName;
    std::map<QString,DiagramScene *>::iterator sceneIt = scenes.find(oldName);
    scenes[newName]=(*sceneIt).second;
    scenes.erase(sceneIt);

    std::map<QString,QWidget *>::iterator widgetIt = widgets.find(oldName);
    widgets[newName]=(*widgetIt).second;
    widgets.erase(widgetIt);

    std::map<QString,QGraphicsView *>::iterator viewIt = views.find(oldName);
    views[newName]=(*viewIt).second;
    views.erase(viewIt);

    std::map<QString,QHBoxLayout *>::iterator layoutIt = layouts.find(oldName);
    layouts[newName]=(*layoutIt).second;
    layouts.erase(layoutIt);

    int i;
    for(i = 0;i<tabWidget->count();i++)
    {
        if(tabWidget->tabText(i)==oldName)
        {
            break;
        }
    }

    tabWidget->removeTab(i);

    tabWidget->addTab(widgets[newName], newName);


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
    if(mod->wasChanged())
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
    }

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
    mod->setBlock(true);
    //mod->deleteAll(); zbędne skoro wykonujemy subtaskRemoved

    for (std::map<QString,DiagramScene *>::iterator it = scenes.begin();it!=scenes.end();it++)
    {
        SubtaskRemoved((*it).first);
        it = scenes.begin();
    }

    QString subName = fileName;
    subName.chop(4);//delete .xml
    QString logPath =SaveFolder+subName;
    logPath.append(".log");
    int ind = subName.lastIndexOf('/');
    subName.remove(0,ind+1);//delete beginning till the last /

    QStringList errors;

    QString oldMain = mod->getMainName();
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

    if(mod->vertNum(oldMain)==0)
    {
        SubtaskRemoved(oldMain);
    }
    this->sceneScaleChanged(sceneScaleCombo->currentText());
    emit refreshWidgets();
    mod->setChanged(false);
    mod->setBlock(false);
}

QStringList RESpecTa::LoadStates(QString FileName)
{
QStringList errors;
    QString filename = QString(SaveFolder)+FileName;
    //QString subName = filename;
    QString GraphName = FileName;
    GraphName.chop(4);
    if(scenes.find(GraphName)==scenes.end())
    {
        this->SubtaskAdded(GraphName);
    }
    QFile* file = new QFile(filename);
    file->open( QIODevice::ReadOnly);
    QXmlStreamReader * reader = new QXmlStreamReader(file);
    while (!reader->atEnd())
    {
          reader->readNextStartElement();
std::string startEnd = "START";
if(reader->isEndElement())startEnd="END";


          if(reader->name().toString()=="Graphics"&&reader->isStartElement())
          {
              errors+=this->loadGraphics(reader, GraphName);
          }
          if(reader->name().toString()=="State")
          {
              if(reader->attributes().hasAttribute("id")&&reader->attributes().hasAttribute("type"))
              {
                  BaseState * state=NULL;
                  StateType type;
                  int index = (getStateTypeTable().indexOf(reader->attributes().value("type").toString()));
                  if(index<STATE_TYPES_NUMBER)
                  {
                       type = (StateType)index;
                  }
                  //else - //in switch
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
                    errors+= state->LoadFromXML(reader);
                    scenes[GraphName]->setItemParams(state);
                    state->setToolTip(QString().fromStdString(state->Print()));
                    mod->addState(state, GraphName);
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
        if(subtaskName.contains("/"))//TODO: a co jeśli jest subtask w innym folderze?
        {
            int ind = subtaskName.lastIndexOf('/');
            subtaskName.remove(0,ind+1);//delete beginning till the last /
        }
                   //subtaskName.chop(4);
                   //mod->addSubtask(subtaskName);
                   //subtaskName.append(".xml");
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
                      BaseState * sourceState = mod->getState(StateName, subName);
                      BaseState * targetState = mod->getState(target, subName);
                      if(sourceState!=NULL&&targetState!=NULL)
                      {
                          Transition * trans = new Transition(sourceState, targetState);
                          trans->setCondition(condition);
                          trans->setSubtask(subtask);
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
                            scenes[subName]->addItem(trans);
                            mod->tryInsertTransition(trans);
                            trans->updatePosition();
                            scenes[subName]->setMode(DiagramScene::MoveItem);
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
        QString subName =SaveName;
        subName.chop(4);
        int ind = subName.lastIndexOf('/');
        subName.remove(0,ind+1);//delete beginning till the last /
        if(mod->getMainName()!= subName)SubtaskChanged(mod->getMainName(), subName);
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
            QString subName =SaveName;
            subName.chop(4);
            int ind = subName.lastIndexOf('/');
            subName.remove(0,ind+1);//delete beginning till the last /
            if(mod->getMainName()!= subName)SubtaskChanged(mod->getMainName(), subName);
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
    /*QList<QAbstractButton *> buttons = buttonGroup->buttons();
    foreach (QAbstractButton *button, buttons) {
    if (buttonGroup->button(id) != button)
        button->setChecked(false);
    }
    if (id == InsertTextButton) {
        scenes[0]->setMode(DiagramScene::InsertText);
    } else {
        //scene->setItemType(BaseState::DiagramType(id));
        scenes[0]->setMode(DiagramScene::InsertItem);
    }*/
}

void RESpecTa::deleteItem()
{
    QString index = tabWidget->tabText(tabWidget->currentIndex());

    //check why there's a bug with deleting transitions attached to a deleted node
    foreach (QGraphicsItem *item, scenes[index]->selectedItems())
    {
        if (item->type() == Transition::Type)
        {
            Transition *transition = qgraphicsitem_cast<Transition *>(item);
            deleteTrans(transition);

        }
    }

    foreach (QGraphicsItem *item, scenes[index]->selectedItems())
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

    QString sub = mod->getSubtaskName(state->getName());
    mod->deleteState(state);

    scenes[sub]->removeItem(state);

    delete state;
}

void RESpecTa::deleteTrans(Transition * trans)
{
    QString sub = mod->getSubNameOfTrans(trans);
    mod->deleteTransition(trans);

    scenes[sub]->removeItem(trans);
    delete trans;
}

void RESpecTa::pointerGroupClicked(int)
{
    //scenes[0]->setMode(DiagramScene::Mode(pointerTypeGroup->checkedId()));
}

void RESpecTa::bringToFront()
{
    QString index = tabWidget->tabText(tabWidget->currentIndex());
    if (scenes[index]->selectedItems().isEmpty())
        return;

    QGraphicsItem *selectedItem = scenes[index]->selectedItems().first();
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
    QString index = tabWidget->tabText(tabWidget->currentIndex());

    if (scenes[index]->selectedItems().isEmpty())
        return;

    QGraphicsItem *selectedItem = scenes[index]->selectedItems().first();
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
    QString index = tabWidget->tabText(tabWidget->currentIndex());
    pointerTypeGroup->button(int(DiagramScene::MoveItem))->setChecked(true);
    scenes[index]->setMode(DiagramScene::Mode(pointerTypeGroup->checkedId()));

    if(currentSubtask==mod->getMainName() && item->getName().toLower()==QString("_end_"))
    {
        item->setName(QString("_STOP_"));
    }
    if((currentSubtask==mod->getMainName()&& item->getName()=="INIT") ||item->getName()!="INIT")
    {
        bool check = mod->addState(item, currentSubtask);
        if(check)
        {
            item->setToolTip(QString().fromStdString(item->Print()));
        }
        else
        {
            scenes[index]->removeItem(item);
            delete item;
        }
    }
    else
    {
        scenes[index]->removeItem(item);
        delete item;
        reportError(QString("Only Main task can have INIT state"));
    }
    for (std::map<QString,DiagramScene *>::iterator it = scenes.begin();it!=scenes.end();it++)
    {
        (*it).second->setMode(DiagramScene::MoveItem);
    }
}

bool RESpecTa::lineInserted(Transition *line)
{

    bool test = mod->tryInsertTransition(line);
    if(test)
    {
        emit itemSelectedSig(line);
    }
    for (std::map<QString,DiagramScene *>::iterator it = scenes.begin();it!=scenes.end();it++)
    {
        (*it).second->setMode(DiagramScene::MoveItem);
    }
    return test;
}

void RESpecTa::sceneScaleChanged(const QString &scale)
{
    double newScale = scale.left(scale.indexOf(tr("%"))).toDouble() / 100.0;
    for(std::map<QString,QGraphicsView *>::iterator it = views.begin();it!=views.end();it++)
    {
        QMatrix oldMatrix = (*it).second->matrix();
        (*it).second->resetMatrix();
        (*it).second->translate(oldMatrix.dx(), oldMatrix.dy());
        (*it).second->scale(newScale, newScale);
    }
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
    //scenes[0]->setItemColor(qVariantValue<QColor>(fillAction->data()));
}

void RESpecTa::lineButtonTriggered()
{
    //scenes[0]->setLineColor(qVariantValue<QColor>(lineAction->data()));
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
        for(std::map<QString, DiagramScene *>::iterator it = scenes.begin();it!=scenes.end();it++)
        {
            (*it).second->setMode(DiagramScene::InsertItem);
            (*it).second->setToInsertState(newState);
        }
    }
}

void RESpecTa::insertTransition(std::pair<QString,QString> thePair)
{
    for (std::map<QString,DiagramScene *>::iterator it = scenes.begin();it!=scenes.end();it++)
    {
        (*it).second->setMode(DiagramScene::InsertLine);
        (*it).second->setTransitionAttributes(thePair);
    }
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
    QString index = tabWidget->tabText(tabWidget->currentIndex());
    StopState * tmp = new StopState();
    tmp->setType(StateType(STATE_TYPES_NUMBER));
    tmp->setName("_END_");
    scenes[index]->setMode(DiagramScene::InsertItem);
    scenes[index]->setToInsertState(tmp);
}
void RESpecTa::EditTransitionsOfState()
{
    QString index = tabWidget->tabText(tabWidget->currentIndex());
    if(scenes[index]->selectedItems().isEmpty())return;
    if(scenes[index]->selectedItems().first()->type()==BaseState::Type)
    {
        BaseState * state = qgraphicsitem_cast<BaseState *>(scenes[index]->selectedItems().first());
        transDial->openForAState(state);
        //transDial->setModal(true);
        transDial->exec();
    }
    return;
}

void RESpecTa::ReplaceState(BaseState * oldState, BaseState * newState, QString oldStateName)
{
    QString index = mod->getSubtaskName(oldStateName);
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
        scenes[index]->removeItem(oldState);
        scenes[index]->setItemParams(newState);
        newState->setToolTip(QString().fromStdString(newState->Print()));
        delete oldState;
        scenes[index]->selectedItems().clear();
        scenes[index]->selectedItems().push_back(newState);
        newState->setSelected(true);
        emit itemSelected(newState);
    }
}


void RESpecTa::closeEvent(QCloseEvent *event)
{
    if(mod->wasChanged())
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
}




void RESpecTa::SaveGraphicsAttributes(QXmlStreamWriter * writer, QString SubName)
{

    writer->writeStartElement("Graphics");
    char tab[20];
    QString scale = sceneScaleCombo->currentText();
    int newScale = scale.left(scale.indexOf(tr("%"))).toInt();

    sprintf(tab, "%d", (int)(views[SubName]->mapFromScene(0,0)).x()*100/newScale);
    writer->writeTextElement("PosX", QString(tab));
    sprintf(tab, "%d", (views[SubName]->mapFromScene(0,0)).y()*100/newScale);
    writer->writeTextElement("PosY", QString(tab));

    if(SubName ==mod->getMainName())
    {
        sprintf(tab, "%d", newScale);
        writer->writeTextElement("Scale", QString(tab));
    }

    writer->writeEndElement();
    return;
}

QStringList RESpecTa::loadGraphics(QXmlStreamReader * reader, QString subName)
{
    bool wasX = false;
    bool wasY = false;
    bool wasScale = false;
    int X, Y;
    int scaleInt;
    QStringList errors;
    while (!reader->atEnd())
    {
          reader->readNextStartElement();
          if(reader->name()=="Graphics"&&reader->isEndElement())
          {
              if(!wasX||!wasY)
              {
                  char linenum[30];
                  sprintf(linenum,"; line: %lld", reader->lineNumber());
                  errors.push_back(QString("The X, Y or Sacle parameter was not defined for the Graphics")+=linenum);
              }
              else
              {
                  if(!wasScale)
                  {
                      QString scaleTmpString = sceneScaleCombo->currentText();
                      scaleTmpString.chop(1);
                      scaleInt = scaleTmpString.toInt();
                  }
                  views[subName]->centerOn(-X+(views[subName]->size().width()*50/scaleInt), -Y+(views[subName]->size().height()*50/scaleInt));
              }
              return errors;
          }
          else if(reader->name()=="PosX"&&reader->isStartElement())
          {
              wasX=true;
              X = reader->readElementText().toInt();
          }
          else if(reader->name()=="PosY"&&reader->isStartElement())
          {
              wasY=true;
              Y = reader->readElementText().toInt();
          }
          else if (reader->name()=="Scale"&&reader->isStartElement())
          {
              wasScale=true;
              QString ScaleString = reader->readElementText();
              scaleInt =(int) ScaleString.toDouble();
              char tmp[10];
              sprintf (tmp,"%d",scaleInt);
              ScaleString = QString(tmp);
              ScaleString.append("%");
              this->sceneScaleChanged(ScaleString);
              QStringList tmpScales = scales;
              if(tmpScales.contains(ScaleString))
              {
                  sceneScaleCombo->setCurrentIndex(tmpScales.indexOf(ScaleString));
              }
              else
              {
                tmpScales<<ScaleString;
                sceneScaleCombo->clear();
                sceneScaleCombo->addItems(tmpScales);
                sceneScaleCombo->setCurrentIndex(tmpScales.indexOf(ScaleString));
              }
          }

          else if (reader->isStartElement())
          {
              char linenum[30];
              sprintf(linenum,"; line: %lld", reader->lineNumber());
              errors.push_back((QString("unexpected name while reading wait <State>: ")+=reader->name())+=linenum);
          }

    }
    if(!wasX||!wasY)
    {
        char linenum[30];
        sprintf(linenum,"; line: %lld", reader->lineNumber());
        errors.push_back(QString("The X, Y or Sacle parameter was not defined for the Graphics")+=linenum);
    }
    else
    {
        if(!wasScale)
        {
            QString scaleTmpString = sceneScaleCombo->currentText();
            scaleTmpString.chop(1);
            scaleInt = scaleTmpString.toInt();
        }
        views[subName]->centerOn(-X+(views[subName]->size().width()*50/scaleInt), -Y+(views[subName]->size().height()*50/scaleInt));
    }
    return errors;
}


void RESpecTa::TabChanged(int newIndex)
{
    setCurrentSubtask(tabWidget->tabText(newIndex));

    TreeModel * newModel = new TreeModel(this, mod, currentSubtask);
    TreeView->setModel(newModel);
    delete treeModel;
    treeModel = newModel;

}

void RESpecTa::WasChanged()
{
    TreeModel * newModel = new TreeModel(this, mod, currentSubtask);
    TreeView->setModel(newModel);
    delete treeModel;
    treeModel = newModel;
    emit SignalDeleted();//żeby nie było problemu, gdyedytujemy coś i zmienimy podzadanie
}

void RESpecTa::GoToState()
{
    if(TreeView->getSelectedIndexes().size()<=0)
        return;
    if(TreeView->getSelectedIndexes().size()<=2)//why
    {
        QModelIndex ind = TreeView->getSelectedIndexes().first();
        QGraphicsItem * it = treeModel->getItemOrParent(ind);
        views[currentSubtask]->centerOn(it);
        foreach(QGraphicsItem * grIt, scenes[currentSubtask]->selectedItems())
        {
            grIt->setSelected(false);
        }
        scenes[currentSubtask]->selectedItems().clear();
        scenes[currentSubtask]->selectedItems().push_back(it);
        it->setSelected(true);
        this->itemSelected(it);
        return ;
    }
}

void RESpecTa::FindOnList()
{
    QString textToFind = findLineEdit->text();
    TreeView->keyboardSearch(textToFind);
}




