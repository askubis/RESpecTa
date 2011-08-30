class RESpecTa;

#ifndef RESPECTA_H
#define RESPECTA_H

#include <QMainWindow>

#include "baseState.h"
#include "Model.h"
#include "TransDialog.h"
#include "TreeModel.h"
#include "TreeItem.h"
#include "myTreeView.h"
#include "diagramscene.h"

QT_BEGIN_NAMESPACE
class QAction;
class QToolBox;
class QSpinBox;
class QComboBox;
class QFontComboBox;
class QButtonGroup;
class QLineEdit;
class QGraphicsTextItem;
class QFont;
class QToolButton;
class QAbstractButton;
class QGraphicsView;
QT_END_NAMESPACE

/**
*   Main window class. It is a parent to all the widgets in the project.
*/
class RESpecTa : public QMainWindow
{
    Q_OBJECT
public:
   //RESpecTa(){}
    /**
    *   Constructor creating all sub-elements of the view.
    */
   RESpecTa(Model * newmod );
   /**
   *    Destructor, which closes the log file.
   */
   ~RESpecTa()
   {
       logStreamToWrite.flush();
       logFile.close();
   }

   /**
   *   Function which displays a warning in the terminal.
   */
   void getWarning(QString msg){reportWarning(msg);}
   /**
   *   Function centering the view on a State with name _name.
   */
    void CenterOn(QString _name);

    /**
    *   Unchecks the tasksaction button.
    */
    void HideSubtask();

   /**
   *   Function refreshing the TreeView, called when change in the model has occured.
   */
   void WasChanged();
   /**
   *   Sets curentSubtask to newSubtask.
   *    @param newSubtask Name of the new subtask to show.
   */
   void setCurrentSubtask(QString newSubtask){currentSubtask = newSubtask;}
   /**
   *   Calls reportError function.
   *    @param error Error to report.
   */
   void getError(QString error){reportError(error);}
   /**
   *   Displays a dialog showing the message.
   *   @param msgString Message, which will be displayed.
   */
   void reportMsg(QString msgString);
   /**
   *   Clears name of the Save file causing browse file window to open next time while saving.
   */
   void clearSaveName() {SaveName=QString();}
   /**
   *   Removes a state from the model, calling remove functions to all transitions connected.
   */
   void deleteState(BaseState * state);
   /**
   *   Removes transition from the model and from all states, to which it is connected.
   */
   void deleteTrans(Transition * trans);
   /**
   *   Save graphic attributes of scene to XML.
   *    @param writer XML Strem, to which the attributes are saved.
   *    @param SubName Name of the subtask which parameters are saved.
   */
   void SaveGraphicsAttributes(QXmlStreamWriter * writer, QString SubName);

   /**
   *    Reacts on the change on the treeview list with concentrating on the item selected.
   */
   void listSelectionChanged(QModelIndexList list);

signals:
   /**
   *   Signal, which informs editwidget, that the Task widget should be opened.
   */
   void EditTasksSig();

   /**
   *   Signal from Scene, which is forwarded to EditWidget and then to transWidget or stateWidget to display item for edition.
   *    @param item Item, which has been selected on the scene.
   */
   void itemSelectedSig(QGraphicsItem *item);
   /**
   *   Refreshes stateWidget and transWidget.
   */
   void refreshWidgets();
   /**
   *   Signals that a deletion has occured ont he scene, and all editions should be canceled.
   */
   void SignalDeleted();

private slots:
   /**
   *   Slot, which runs HideSubtask function.
   */
   void HideTheSubtask(){HideSubtask();}
   /**
   *   Selects a transition after it's been changed.
   */
   void TransSelected(Transition * tr);
   /**
   *   Zooms into the scene.
   */
   void ZoomIn();
   /**
   *   Zooms out of the scene.
   */
   void ZoomOut();
   /**
   *   Slot responsible for receiving warnings from other Widgets.
   */
   void reportWarning(QString msg);
   /**
   *   Cancels drawing a line(unchecks the transition insert action).
   */
   void LineCanceled();
   /**
   *   Emits EditTasksSig, it's connected with the tasksAction triggered.
   */
   void openTasksWindow(bool enabled);
   /**
   *   Changes the tipLabel accordingto new scene mode.
   */
   void sceneModeChanged(SceneMode mode);
   /**
   *   Clears the terminal.
   */
   void ClearTerminal();
   /**
   *   Creates new project.
   */
   void NewProject();
   /**
   *   Runs checkIfOK function for the data model and displays errors and warnings.
   */
   void checkIfOK();
    /**
    *   Selection on the stage changed, therefore color needs to be changed.
    */
    void selectionchanged();
    /**
    *   Finds text in the TreeView widget.
    */
    void FindOnList();
    /**
    *   Centers  the view on the graphicsItem selected on the TreeView list.
    */
    /*void GoToState();*/
    /**
    *   Changes the task displayed on the TreeView to the task displayed on the selected tab.
    */
    void TabChanged(int);
    /**
    *   Creates new scene, view, and layout for the subtask, adds the subtask to the model and refreshes the editwidgets.
    *   @param subtaskName Name of the subtask, which is added to the Model.
    */
    void SubtaskAdded(QString subtaskName);
    /**
    *   Removes a scene etc. for the subtask, removes the subtask from the model and refreshes the editwidgets.
    *   @param subtaskName Name of the subtask, which is deleted.
    */
    void SubtaskRemoved(QString subtaskName);
    /**
    *   Changes the nme of the subtask in the model nad in the views, changes the Tab label.
    */
    void SubtaskChanged(QString oldName, QString newName);
    /**
    *   Checks if state oldState exists, if yes - replaces oldState with newState.
    */
    void ReplaceState(BaseState * oldState, BaseState * newState);

    /**
    *   Creates and connects scene and view after loading a task from the XML.
    *   It also checks if end state exists, and if not - the function creates it.
    */
    void SubtaskLoaded(QString subtaskName);
    /**
    *   Opens TransDialog for the selected state.
    */
    void EditTransitionsOfState();
    /**
    *   Sets a StopState member as a state, which will be next added to the active scene.
    */
    //void addEndState();
    /**
    *   Displays a dialog showing the error.
    *   @param msgString Message, which will be displayed.
    */
    void reportError(QString msgString);
    /**
    *   Checks if the line can be inserted, and if yes the adss it to the model.
    *   @param line Pointer to the transition, which will be inserted.
    *   @returns True if the Transition has been added to the Model.
    */
    void lineInserted(Transition *line);
    /**
    *   Forwards the transition attributes (condition, subtask) to the active scene.
    */
    void insertTransition(bool);
    /**
    *   Asks the user for name of the file to open, reads the name and runs LoadFile function.
    */
    void Load();
    /**
    *   Runs the SaveAs function is SaveName wasn't set, and forwards it to the Model's save function.
    */
    void save();
    /**
    *   Asks the user for filename to save and stores it in the SaveName variable.
    *   @returns False, if the user has chosen to abort.
    */
    bool SaveAs();
    /**
    *   If state with that name is not present in the model, then forwards the newState to all scenes(it will be added to the first scene, on which it will be clicked).
    */
    void InsertState(bool);
    /**
    *   Deletes all selected items on the active scene.
    */
    void deleteItem();
    /**
    *   Moves the selected items to foreground.
    */
    void bringToFront();
    /**
    *   Moves the selected items to background.
    */
    void sendToBack();
    /**
    *   Adds a state to the Model.
    */
    void stateInserted(BaseState *item);
    /**
    *   Changes the view Scale of the scenes.
    */
    void sceneScaleChanged(const QString &scale);
    /**
    *   Aborts if the item is a stop state, otherwise clls itemSelectedSig.
    */
    void itemSelected(QGraphicsItem *item);
    /**
    *   Opens about window.
    */
    void about();

private:
    /**
    *   Loads Graphic attributes for the scene for subName task from XML Stream.
    *   @param reader Strem, from which the data is read.
    *   @param subName Name of Subtask to which the data is relevant.
    *   @returns Errors during load.
    */
    QStringList loadGraphics(QXmlStreamReader * reader, QString subName);
    /**
    *   Asks if the user wants to save his work before exit.
    */
    void closeEvent(QCloseEvent *event);
    /**
    *   Creates File options.
    */
    void createFileMenu();
    /**
    *   Creates Edit options and options for context menu of states.
    */
    void createEditMenu();
    /**
    *   Creates Options menu.
    */
    void createOptionsMenu();
    /**
    *   Creates Help menu.
    */
    void createHelpMenu();
    /**
    *   Creates toolbar.
    */
    void createToolbars();

    /**
    *   Runs LoadStates and LoadTransition functions for the file, and displays errors.
    */
    void LoadFile(QString filename);
    /**
    *   Loads all states from the file, adds them to view and Model and recursively runs itself for other files included in this file.
    */
    QStringList LoadStates(QString filename);
    /**
    *   Loads all transitions from the file, adds them to view and Model and recursively runs itself for other files included in this file.
    */
    QStringList LoadTransitions(QString filename);

    /**
    *   List of available scale modifiers.
    */
    QStringList scales;

    /**
    *   Pointer to the model, representing the data in the program.
    */
    Model * mod;

    /**
    *   Pointer to the class representing treeview of the task.
    */
    myTreeView *TreeView;
    /**
    *   Model of the tree representation.
    */
    TreeModel *treeModel;
    /**
    *   Line edit allowing to search the treeview.
    */
    QLineEdit * findLineEdit;

    /**
    *   Widget containing scenes.
    */
    QTabWidget * tabWidget;
    /**
    *   Widget containing transwidget and statewidget.
    */
    QWidget *editWidget;

    /**
    *   Dialog box showing transitions of the state.
    */
    TransDialog * transDial;

    /**
    *   Name of the currently displayed(active) task.
    */
    QString currentSubtask;
    /**
    *   Name to which the task is saved when Save option is used.
    */
    QString SaveName;
    /**
    *   Folder to which the task is saved when Save option is used.
    */
    QString SaveFolder;

    /**
    *   Map of widgets containing views of the tasks.
    */
    std::map<QString,QWidget *> widgets;
    /**
    *   Map of scenes, on which the tasks are represented.
    */
    std::map<QString,DiagramScene *> scenes;
    /**
    *   Map of sceneViews graphicaly representing tasks.
    */
    std::map<QString,QGraphicsView *> views;
    /**
    *   Map of layouts for widgets containing views of tasks.
    */
    std::map<QString, QHBoxLayout *> layouts;

    /**
    *   Action responsible for exiting from the program.
    */
    QAction *exitAction;
    /**
    *   Action responsible for saving.
    */
    QAction *saveAction;
    /**
    *   Action responsible for opening file choose dialog to choose the file, to which the project should be saved.
    */
    QAction *saveAsAction;
    /**
    *   Action responsible for opening file choose dialog, in which user hcooses file, from which to load; this action starts also all Load functions.
    */
    QAction *loadAction;
    /**
    *   Action responsible for deleting selected widgets(states and transitions).
    */
    QAction *deleteAction;
    /**
    *   Action responsible for opening a dialogbox showing transitions of a state.
    */
    QAction *showTransitions;
    /**
    *   Action responsible for moving selected items to foreground.
    */
    QAction *toFrontAction;
    /**
    *   Action responsible for moving selected items to background.
    */
    QAction *sendBackAction;
    /**
    *   Action responsible for showing the about dialog.
    */
    QAction *aboutAction;
    /**
    *   The "Menu" menu.
    */
    QMenu *fileMenu;
    /**
    *   Context menu for states.
    */
    QMenu *itemMenu;
    /**
    *   The "Edit" menu.
    */
    QMenu *editMenu;
    /**
    *   The "About" menu.
    */
    QMenu *aboutMenu;

    /**
    *   Toolbar holding edit options for states.
    */
    QToolBar * editToolBar;
    /**
    *   Toolbar holding view edit options.
    */
    QToolBar * sceneToolbar;

    /**
    *   Combobox containing availablescales for scenes.
    */
    QComboBox *sceneScaleCombo;

    /**
    *   List of items, which were selected before.
    */
    QList<QGraphicsItem *> oldSelectedItems;

    /**
    *   A Widget which contains messages to a user.
    */
    QListWidget * terminal;

    /**
    *   Stream to the file to which logs are saved.
    */
    QTextStream logStreamToWrite;

    /**
    *   File, to which errors are saved.
    */
    QFile logFile;

    /**
    *   Label displaying tips for the user.
    */
    QLabel * tipLabel;
    /**
    *   Acction responsible for adding states.
    */
    QAction * addStateAction;
    /**
    *   Action responsible for adding transition.
    */
    QAction * addTransAction;
    /**
    *   Action responsible
    */
    QAction * TasksAction;
};


#endif
