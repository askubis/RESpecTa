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


//TODO:
//zmiana stanu kursora przy przesuwaniu/wstawianiu

RESpecTa::RESpecTa(Model * newmod)
{
    mod=newmod;

    createFileMenu();
    createEditMenu();
    createHelpMenu();
    createToolbars();

    transDial = new TransDialog(this, mod);
    connect(transDial, SIGNAL(reportError(QString)), this, SLOT(reportError(QString)));

    editWidget = new EditWidget(this, mod);
    connect(editWidget, SIGNAL(reportError(QString)), this, SLOT(reportError(QString)));
    connect(this, SIGNAL(itemSelectedSig(QGraphicsItem *)), editWidget, SLOT(itemSelected(QGraphicsItem *)));
    connect(this, SIGNAL(EditTasksSig()), editWidget, SLOT(EditTasks()));
    editWidget->resize(10,800);

    currentSubtask="MAIN";

    scenes[currentSubtask] = new DiagramScene(itemMenu, this, mod);
    scenes[currentSubtask]->setSceneRect(QRectF(0, 0, 5000, 5000));

    connect(scenes[currentSubtask], SIGNAL(itemInserted(BaseState*)),this, SLOT(stateInserted(BaseState*)));
    connect(scenes[currentSubtask], SIGNAL(itemSelected(QGraphicsItem*)),this, SLOT(itemSelected(QGraphicsItem*)));
    connect(scenes[currentSubtask], SIGNAL(lineInserted(Transition *)), this, SLOT(lineInserted(Transition *)));
    connect(scenes[currentSubtask], SIGNAL(reportError(QString)), this, SLOT(reportError(QString)));
    connect(scenes[currentSubtask], SIGNAL(modeChanged(SceneMode)), this, SLOT(sceneModeChanged(SceneMode)));

    connect(scenes[currentSubtask], SIGNAL(selectionChanged()), this, SLOT(selectionchanged()));

    QWidget * mainWidget = new QWidget();

    tabWidget = new QTabWidget;


    QGridLayout *layout = new QGridLayout;
    layouts[currentSubtask]=new QHBoxLayout;

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

    mod->setBlock(true);
    sysInitState * startState = new sysInitState();
    startState->setType(SYSTEM_INITIALIZATION);
    startState->setPos(2100,2300);
    startState->setName("INIT");
    scenes[currentSubtask]->setItemParams(startState);
    mod->addState(startState, mod->getMainName());
    StopState * endState = new StopState();
    endState->setPos(2600,2600);
    endState->setName("_STOP_");
    endState->setType(STATE_TYPES_NUMBER);
    scenes[currentSubtask]->setItemParams(endState);
    mod->addState(endState, mod->getMainName());
    mod->setBlock(false);

    TreeView = new myTreeView(listWidget, this);
    TreeView->setModel(treeModel);
    listLayout->addWidget(TreeView);

    listWidget->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Expanding);
    layout->addWidget(listWidget, 0, 0);
    tabWidget->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    layout->addWidget(tabWidget, 0, 1);
    editWidget->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Expanding);
    layout->addWidget(editWidget, 0, 2);
    terminal = new QListWidget(this);
    terminal->setMaximumHeight(200);
    layout->addWidget(terminal, 1, 0, 1, 3);
    tipLabel = new QLabel("Insert an item, select item to edit or move items on the scene.");
    QPushButton * clearTerminalButton = new QPushButton("Clear Terminal");
    connect (clearTerminalButton, SIGNAL(clicked()), this, SLOT(ClearTerminal()));
    layout->addWidget(tipLabel, 2, 0, 1, 2);
    layout->addWidget(clearTerminalButton, 2, 2, 1, 1);

    mainWidget->setLayout(layout);

    widgets[currentSubtask] = new QWidget;
    widgets[currentSubtask]->setLayout(layouts[currentSubtask]);

    tabWidget->addTab(widgets[currentSubtask], "MAIN");
    tabWidget->setMovable(true);

    connect(tabWidget, SIGNAL(currentChanged(int)), this, SLOT(TabChanged(int)));
    setCentralWidget(mainWidget);
    setWindowTitle(tr("RESpecTa"));
    setUnifiedTitleAndToolBarOnMac(true);

    currentSubtask=mod->getMainName();

    QDateTime dateTime= QDateTime::currentDateTime();

    QString logPath = "../logs/";
    logPath.append(currentSubtask);
    logPath.append("_");
    logPath.append(dateTime.toString());
    logPath.append(".log");
    logFile.setFileName(logPath);
    if(!logFile.open(QIODevice::WriteOnly))
    {
        QDir dir = QDir::current();
        dir.mkdir("../logs/");
        if(!logFile.open(QIODevice::WriteOnly))
            qDebug()<<"Error opening the logfile";
    }

    logStreamToWrite.setDevice(&logFile);
    mod->setChanged(false);

    reportMsg(QString("Errors will be saved to: ").append(logPath));
}

void RESpecTa::ClearTerminal()
{
    terminal->clear();
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

    /*insertEndStateAction = new QAction(QIcon(":/images/_END_image.jpg"),
                               tr("&End"), this);
    insertEndStateAction->setShortcut(tr("Ctrl+E"));
    insertEndStateAction->setStatusTip(tr("Insert End state for main task or subtask"));
    connect(insertEndStateAction, SIGNAL(triggered()),
        this, SLOT(addEndState()));*/

    showTransitions = new QAction(tr("&Transitions"), this);
    showTransitions->setShortcut(tr("Ctrl+T"));
    showTransitions->setStatusTip(tr("Show transitions of this State"));
    connect(showTransitions, SIGNAL(triggered()),
        this, SLOT(EditTransitionsOfState()));

    /*QAction * GoToState = new QAction(tr("&Go to Item from the list"), this);
    GoToState->setShortcut(tr("Ctrl+G"));
    GoToState->setStatusTip(tr("Center on the state selected on the list"));
    connect(GoToState, SIGNAL(triggered()),
        this, SLOT(GoToState()));*/
    QAction * ModelCheckIfOK = new QAction(tr("Check for &errors in the menu"), this);
    ModelCheckIfOK->setShortcut(tr("Ctrl+E"));
    ModelCheckIfOK->setStatusTip(tr("Check for errors in the menu"));
    connect (ModelCheckIfOK, SIGNAL(triggered()), this, SLOT(checkIfOK()));

    editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(deleteAction);
    editMenu->addSeparator();
    editMenu->addAction(toFrontAction);
    editMenu->addAction(sendBackAction);
    editMenu->addAction(showTransitions);
    editMenu->addAction(ModelCheckIfOK);
    //editMenu->addAction(GoToState);

    itemMenu = new QMenu();
    itemMenu->addAction(deleteAction);
    itemMenu->addAction(toFrontAction);
    itemMenu->addAction(sendBackAction);
    itemMenu->addAction(showTransitions);
}

void RESpecTa::checkIfOK()
{
    QStringList list = mod->checkIfOK();
    foreach(QString str, list)
    {
        reportError(str);
    }
}

void RESpecTa::selectionchanged()
{
    if(scenes[currentSubtask]->selectedItems().size()!=1)emit SignalDeleted();
    QList<QGraphicsItem *> newItems = scenes[currentSubtask]->selectedItems();
    foreach(QGraphicsItem * it, newItems)
    {
        if(it->type()==BaseState::Type)
        {
            BaseState * tmp = (BaseState*)it;
            tmp->setBrush(Qt::red);
            tmp->update();
        }
    }
    foreach(QGraphicsItem * it, oldSelectedItems)
    {
        if(it->type()==BaseState::Type)
        {
            if(!newItems.contains(it))
            {
                BaseState * tmp = (BaseState*)it;
                tmp->setBrush(Qt::white);
                tmp->update();
            }
        }
    }
    oldSelectedItems=newItems;
}

void RESpecTa::SubtaskLoaded(QString newSubtask)
{
    scenes[newSubtask] = new DiagramScene(itemMenu, this, mod);
    scenes[newSubtask]->setSceneRect(QRectF(0, 0, 5000, 5000));

    connect(scenes[newSubtask], SIGNAL(itemInserted(BaseState*)),this, SLOT(stateInserted(BaseState*)));
    connect(scenes[newSubtask], SIGNAL(itemSelected(QGraphicsItem*)),this, SLOT(itemSelected(QGraphicsItem*)));
    connect(scenes[newSubtask], SIGNAL(lineInserted(Transition *)), this, SLOT(lineInserted(Transition *)));
    connect(scenes[newSubtask], SIGNAL(reportError(QString)), this, SLOT(reportError(QString)));
    connect(scenes[newSubtask], SIGNAL(modeChanged(SceneMode)), this, SLOT(sceneModeChanged(SceneMode)));

    connect(scenes[newSubtask], SIGNAL(selectionChanged()), this, SLOT(selectionchanged()));

    layouts[newSubtask] = new QHBoxLayout;
    views[newSubtask] = new QGraphicsView(scenes[newSubtask]);
    layouts[newSubtask]->addWidget(views[newSubtask]);

    widgets[newSubtask] = new QWidget;
    widgets[newSubtask]->setLayout(layouts[newSubtask]);

    tabWidget->addTab(widgets[newSubtask], newSubtask);

    mod->addSubtask(newSubtask);
    emit refreshWidgets();
}

void RESpecTa::SubtaskAdded(QString newSubtask)
{
    scenes[newSubtask] = new DiagramScene(itemMenu, this, mod);
    scenes[newSubtask]->setSceneRect(QRectF(0, 0, 5000, 5000));

    connect(scenes[newSubtask], SIGNAL(itemInserted(BaseState*)),this, SLOT(stateInserted(BaseState*)));
    connect(scenes[newSubtask], SIGNAL(itemSelected(QGraphicsItem*)),this, SLOT(itemSelected(QGraphicsItem*)));
    connect(scenes[newSubtask], SIGNAL(lineInserted(Transition *)), this, SLOT(lineInserted(Transition *)));
    connect(scenes[newSubtask], SIGNAL(reportError(QString)), this, SLOT(reportError(QString)));
    connect(scenes[newSubtask], SIGNAL(modeChanged(SceneMode)), this, SLOT(sceneModeChanged(SceneMode)));

    connect(scenes[newSubtask], SIGNAL(selectionChanged()), this, SLOT(selectionchanged()));

    layouts[newSubtask] = new QHBoxLayout;
    views[newSubtask] = new QGraphicsView(scenes[newSubtask]);
    layouts[newSubtask]->addWidget(views[newSubtask]);

    widgets[newSubtask] = new QWidget;
    widgets[newSubtask]->setLayout(layouts[newSubtask]);

    tabWidget->addTab(widgets[newSubtask], newSubtask);

    mod->addSubtask(newSubtask);

    StopState * endState = new StopState();
    endState->setPos(2600,2600);
    endState->setType(STATE_TYPES_NUMBER);
    endState->setName("_END_");
    scenes[newSubtask]->setItemParams(endState);
    mod->addState(endState, newSubtask);

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
    if(oldName==newName) return;
    mod->changeSubtaskName(oldName, newName);
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
    tabWidget->setCurrentWidget(widgets[newName]);
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

    QAction * newAction = new QAction(tr("&New"), this);
    newAction->setShortcut(QKeySequence::New);
    loadAction->setStatusTip(tr("Close current and create a new project"));
    connect(newAction, SIGNAL(triggered()), this, SLOT(NewProject()));

    fileMenu = menuBar()->addMenu(tr("&File"));
    //TODO:newaction
    fileMenu->addAction(newAction);
    fileMenu->addAction(loadAction);
    fileMenu->addAction(saveAction);
    fileMenu->addAction(saveAsAction);
    fileMenu->addAction(exitAction);
}

void RESpecTa::NewProject()
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
    QStringList list = mod->getTasksNameLists();
    foreach(QString str, list)
    {
        this->SubtaskRemoved(str);
    }
    mod->setChanged(false);
    reportMsg(QString("New project created"));
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

    for (std::map<QString,DiagramScene *>::iterator it = scenes.begin();it!=scenes.end();it++)
    {
        SubtaskRemoved((*it).first);
        it = scenes.begin();//usuwa wszystkie sceny z widoku
    }

    mod->deleteAll();//usuwa wszystko z modelu

    QString subName = fileName;
    subName.chop(4);//delete .xml
    QString logPath =SaveFolder+subName;
    logPath.append(".log");
    int ind = subName.lastIndexOf('/');
    subName.remove(0,ind+1);//delete beginning till the last /

    QStringList errors;

    QString oldMain = mod->getMainName();
    mod->setMainName(subName);
    //SubtaskChanged(oldMain, subName);

    errors+=LoadStates(fileName);

    errors+=LoadTransitions(fileName);

    errors+=mod->checkIfOK();

    foreach(QString x, errors)
    {
       reportError(x);
    }

    if(mod->vertNum(oldMain)==0)
    {
        SubtaskRemoved(oldMain);
    }
    this->sceneScaleChanged(sceneScaleCombo->currentText());
    emit refreshWidgets();
    mod->setChanged(false);
    mod->setBlock(false);
    this->TabChanged(tabWidget->currentIndex());

    foreach(QString str, mod->getTasksNameLists())
    {
        if(mod->getMainName()==str)
        {
            if(mod->checkNameAvailable("INIT"))
            {
                sysInitState * startState = new sysInitState();
                startState->setPos(2100,2300);
                startState->setName("INIT");
                scenes[str]->setItemParams(startState);
                mod->addState(startState, str);
                reportMsg(QString("Added missing INIT state to task ").append(str));
            }
            if(mod->checkNameAvailable("_STOP_"))
            {
                StopState * endState = new StopState();
                endState->setPos(2600,2600);
                endState->setName("_STOP_");
                endState->setType(STATE_TYPES_NUMBER);
                scenes[str]->setItemParams(endState);
                mod->addState(endState, str);
                reportMsg(QString("Added missing _STOP_ state to task ").append(str));
            }
        }
        else
        {
            if(mod->checkNameAvailable("_END_", mod->getGraph(str)))
            {
                StopState * endState = new StopState();
                endState->setPos(2600,2600);
                endState->setType(STATE_TYPES_NUMBER);
                endState->setName("_END_");
                scenes[str]->setItemParams(endState);
                mod->addState(endState, str);
                reportMsg(QString("Added missing _END_ state to task ").append(str));
            }
        }
    }
}

QStringList RESpecTa::LoadStates(QString FileName)
{
    reportMsg(QString("File ").append(FileName).append(QString(" loaded")));
QStringList errors;
    QString filename = QString(SaveFolder)+FileName;
    QString GraphName = FileName;
    GraphName.chop(4);
    if(scenes.find(GraphName)==scenes.end())
    {
        this->SubtaskLoaded(GraphName);
    }
    QFile* file = new QFile(filename);
    file->open( QIODevice::ReadOnly);
    QXmlStreamReader * reader = new QXmlStreamReader(file);
    while (!reader->atEnd())
    {
          reader->readNextStartElement();

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
    /*if(stateName.toLower()=="_stop_"||stateName.toLower()=="_end_")
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
    }*/
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
                  else//state==NULL
                  {

                  }
              }
              else//no id or type
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
                   errors+=LoadStates(subtaskName);
          }
    }
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
                      QString subtask="";
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
                          if(subtask.size()!=0)
                          {
                            trans->setSubtask(mod->getState(subtask));
                          }
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
                            scenes[subName]->setMode(MoveItem);
                            trans->setToolTip(QString().fromStdString(trans->Print()));
                            trans->setZValue(-1000.0);
                            sourceState->addTransition(trans);
                            if(sourceState!=targetState)targetState->addTransition(trans);
                            trans->setScene(scenes[subName]);
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
                                                QString("The file exists, are you sure want to overwrite it"),
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

    aboutAction = new QAction(tr("&About"), this);
    aboutAction->setShortcut(tr("Ctrl+A"));
    connect(aboutAction, SIGNAL(triggered()),
            this, SLOT(about()));

    aboutMenu = menuBar()->addMenu(tr("&Help"));
    aboutMenu->addAction(aboutAction);

}

void RESpecTa::deleteItem()
{
    QString index = tabWidget->tabText(tabWidget->currentIndex());

    foreach (QGraphicsItem *item, scenes[index]->selectedItems())
    {
        if (item->type() == Transition::Type)
        {
            Transition *transition = qgraphicsitem_cast<Transition *>(item);
            deleteTrans(transition);

        }
        else if (item->type() == BaseState::Type)
        {
            BaseState * state = qgraphicsitem_cast<BaseState *>(item);
            if(state->getName()=="INIT"||state->getName()=="_STOP_"||state->getName()=="_END_")
            {
                reportError("INIT and END/STOP states cannot be deleted");
                continue;
            }
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

void RESpecTa::stateInserted(BaseState *item)
{
    QString index = tabWidget->tabText(tabWidget->currentIndex());

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
        (*it).second->setMode(MoveItem);
    }
}

bool RESpecTa::lineInserted(Transition *line)
{
    bool test = mod->tryInsertTransition(line);
    if(test)//success
    {
        emit itemSelectedSig(line);
        for (std::map<QString,DiagramScene *>::iterator it = scenes.begin();it!=scenes.end();it++)
        {
            (*it).second->setMode(MoveItem);
        }
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

void RESpecTa::itemSelected(QGraphicsItem *item)
{
    if(item->type()==BaseState::Type)
    {
        BaseState * state = qgraphicsitem_cast<BaseState *>(item);
        if(state->getName().toLower()=="_stop_"||state->getName().toLower()=="_end_")
        {
            emit SignalDeleted();//no item was selected to change; stop state cannot be edited.
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
{//TODO
    QMessageBox::about(this, tr("About Diagram Scene"),
                       tr("The <b>Diagram Scene</b> example shows "
                          "use of the graphics framework."));
}

void RESpecTa::createToolbars()
{

    QAction * addStateAction = new QAction(QIcon(":/images/State.png"),tr("Inset a state"), this);
    addStateAction->setStatusTip(tr("Insert a state to current task"));
    connect(addStateAction, SIGNAL(triggered()), this, SLOT(InsertState()));

    QAction * addTransAction = new QAction(QIcon(":/images/Trans.png"),tr("Inset a state"), this);
    addTransAction->setStatusTip(tr("Insert a state to current task"));
    connect(addTransAction, SIGNAL(triggered()), this, SLOT(insertTransition()));

    QAction * TasksAction = new QAction(QIcon(":/images/Tasks.png"),tr("Inset a state"), this);
    TasksAction->setStatusTip(tr("Insert a state to current task"));
    connect(TasksAction, SIGNAL(triggered()), this, SLOT(openTasksWindow()));

    editToolBar = addToolBar(tr("Edit"));
    editToolBar->addAction(deleteAction);
    editToolBar->addAction(toFrontAction);
    editToolBar->addAction(sendBackAction);

    editToolBar->addAction(addStateAction);
    editToolBar->addAction(addTransAction);
    editToolBar->addAction(TasksAction);


    //editToolBar->addAction(insertEndStateAction);

    /*QToolButton *pointerButton = new QToolButton;
    pointerButton->setCheckable(true);
    pointerButton->setChecked(true);
    pointerButton->setIcon(QIcon(":/images/pointer.png"));*/

    sceneScaleCombo = new QComboBox;
    scales << tr("50%") << tr("75%") << tr("100%") << tr("125%") << tr("150%");
    sceneScaleCombo->addItems(scales);
    sceneScaleCombo->setCurrentIndex(2);
    connect(sceneScaleCombo, SIGNAL(currentIndexChanged(QString)),
            this, SLOT(sceneScaleChanged(QString)));

    sceneToolbar = addToolBar(tr("Pointer type"));
    sceneToolbar->addWidget(sceneScaleCombo);
}

void RESpecTa::InsertState()
{
    WaitState * st = new WaitState();
    st->setName("Name");
    while(!mod->checkNameAvailable(st->getName())) st->setName(st->getName().append("_1"));

    for(std::map<QString, DiagramScene *>::iterator it = scenes.begin();it!=scenes.end();it++)
    {
        (*it).second->setMode(InsertItem);
        (*it).second->setToInsertState(st);
    }
}

void RESpecTa::insertTransition()
{
    for (std::map<QString,DiagramScene *>::iterator it = scenes.begin();it!=scenes.end();it++)
    {
        (*it).second->setMode( InsertLine);
        (*it).second->setTransitionAttributes(std::make_pair("CHANGE THIS",""));
    }
}

void RESpecTa::reportError(QString msgString)
{
    logStreamToWrite<<msgString;
    logStreamToWrite<<"\n";
    logStreamToWrite.flush();
    QDateTime dateTime= QDateTime::currentDateTime();
    QString time = dateTime.time().toString();

    //QMessageBox::information(this, QString("Error"), msgString);
    QListWidgetItem *newItem = new QListWidgetItem();
    newItem->setTextColor(Qt::red);
    newItem->setText(time.append(QString(" Error: ").append(msgString)));
    terminal->addItem(newItem);
    terminal->scrollToBottom();
}

void RESpecTa::reportMsg(QString msgString)
{
    QDateTime dateTime= QDateTime::currentDateTime();
    QString time = dateTime.time().toString();

    //QMessageBox::information(this, QString("Error"), msgString);
    QListWidgetItem *newItem = new QListWidgetItem();
    newItem->setTextColor(Qt::green);
    newItem->setText(time.append(" ").append(msgString));
    terminal->addItem(newItem);
    terminal->scrollToBottom();
}

/*void RESpecTa::addEndState()
{
    QString index = tabWidget->tabText(tabWidget->currentIndex());
    StopState * tmp = new StopState();
    tmp->setType(StateType(STATE_TYPES_NUMBER));
    tmp->setName("_END_");
    scenes[index]->setMode(InsertItem);
    scenes[index]->setToInsertState(tmp);
}*/

void RESpecTa::EditTransitionsOfState()
{
    QString index = tabWidget->tabText(tabWidget->currentIndex());
    if(scenes[index]->selectedItems().isEmpty())return;
    if(scenes[index]->selectedItems().first()->type()==BaseState::Type)
    {
        BaseState * state = qgraphicsitem_cast<BaseState *>(scenes[index]->selectedItems().first());
        transDial->openForAState(state);
        transDial->exec();
    }
    return;
}

void RESpecTa::ReplaceState(BaseState * oldState, BaseState * newState)
{
    QString index = mod->getSubtaskName(oldState);
    bool check = mod->ReplaceState(oldState,newState);
    if(check)
    {
        QList<Transition *> TranList = oldState->getTransitions();
        newState->setPos(oldState->pos().x(), oldState->pos().y());
        foreach(Transition * T, TranList)
        {
            if(T->startItem() == oldState)T->setStartItem(newState);
            if(T->endItem() == oldState)T->setEndItem(newState);
            newState->addTransition(T);
        }
        foreach(Transition * T, oldState->getSubtaskTransitions())
        {
            T->setSubtask(newState);
        }

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
    foreach(QGraphicsItem * it, oldSelectedItems)
    {
        if(it->type()==BaseState::Type)
        {
            BaseState * tmp = (BaseState*)it;
            tmp->setSelected(false);
            tmp->setBrush(Qt::white);
            tmp->update();
        }
    }
    //scenes[currentSubtask]->selectedItems().clear();

    setCurrentSubtask(tabWidget->tabText(newIndex));

    TreeModel * newModel = new TreeModel(this, mod, currentSubtask);
    TreeView->setModel(newModel);
    delete treeModel;
    treeModel = newModel;
    oldSelectedItems=QList<QGraphicsItem *>();
    emit SignalDeleted();
}

void RESpecTa::WasChanged()
{
    TreeModel * newModel = new TreeModel(this, mod, currentSubtask);
    TreeView->setModel(newModel);
    delete treeModel;
    treeModel = newModel;
    emit SignalDeleted();//żeby nie było problemu, gdyedytujemy coś i zmienimy podzadanie
}

/*void RESpecTa::GoToState()
{
    if(TreeView->getSelectedIndexes().size()<=0)
        return;
    if(TreeView->getSelectedIndexes().size()<=2)//why
    {
        QModelIndex ind = TreeView->getSelectedIndexes().first();
        QGraphicsItem * it = treeModel->getItemOrParent(ind);
        views[currentSubtask]->centerOn(it);
        scenes[currentSubtask]->clearSelection();

        scenes[currentSubtask]->selectedItems().push_back(it);
        it->setSelected(true);
        this->itemSelected(it);
        return ;
    }
}*/

void RESpecTa::listSelectionChanged(QModelIndexList list)
{
    QModelIndex ind = list.first();
    QGraphicsItem * it = treeModel->getItemOrParent(ind);
    views[currentSubtask]->centerOn(it);
    scenes[currentSubtask]->clearSelection();

    scenes[currentSubtask]->selectedItems().push_back(it);
    it->setSelected(true);
    this->itemSelected(it);
    return ;
}

void RESpecTa::FindOnList()
{
    QString textToFind = findLineEdit->text();
    TreeView->keyboardSearch(textToFind);
}


void RESpecTa::sceneModeChanged(SceneMode mode)
{
    switch(mode)
    {
    case  MoveItem:

        tipLabel->setText(QString ("Insert an item, select item to edit or move items on the scene."));
        break;
    case  InsertItem:

        tipLabel->setText(QString ("Select place on the scene to insert an item, and then edit its properties"));
        break;
    case  InsertLine:

        if(scenes[currentSubtask]->selectedItems().size()==0)
            tipLabel->setText(QString("Drag the transition from start to end state"));
        else
            tipLabel->setText(QString("Drag to end state"));
        break;
    default:
        break;
    }
}

void RESpecTa::openTasksWindow()
{
    foreach(QGraphicsItem * it, scenes[currentSubtask]->selectedItems())
    {
        it->setSelected(false);
    }
    scenes[currentSubtask]->selectedItems().clear();
    emit EditTasksSig();
}




