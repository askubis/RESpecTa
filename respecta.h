class RESpecTa;

#ifndef RESPECTA_H
#define RESPECTA_H

#include <QMainWindow>

#include "baseState.h"
#include "Model.h"
#include "TransDialog.h"
#include "subtaskDialog.h"
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
   RESpecTa(){}
   RESpecTa(Model * newmod );

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

signals:
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
    *   Finds text in the TreeView widget.
    */
    void FindOnList();
    /**
    *   Centers  the view on the graphicsItem selected on the TreeView list.
    */
    void GoToState();
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
    *   Opens SubtaskDialog.
    */
    void OpenSubtaskEditDialog();
    /**
    *   Checks if state with name oldStateName exists, if yes - replaces oldState with newState.
    */
    void ReplaceState(BaseState * oldState, BaseState * newState, QString oldStateName);
    /**
    *   Opens TransDialog for the selected state.
    */
    void EditTransitionsOfState();
    /**
    *   Sets a StopState member as a state, which will be next added to the active scene.
    */
    void addEndState();
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
    bool lineInserted(Transition *line);
    /**
    *   Forwards the transition attributes (condition, subtask) to the active scene.
    */
    void insertTransition(std::pair<QString,QString>);
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
    void InsertState(BaseState * newState);
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
    *   Adds item to the Model.
    */
    void itemInserted(BaseState *item);
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

    QStringList scales;

    Model * mod;

    myTreeView *TreeView;
    TreeModel *treeModel;
    QLineEdit * findLineEdit;

    QTabWidget * tabWidget;
    QWidget *editWidget;

    TransDialog * transDial;
    SubtaskDialog * subDialog;

    QString currentSubtask;
    QString SaveName;
    QString SaveFolder;

    std::map<QString,QWidget *> widgets;
    std::map<QString,DiagramScene *> scenes;
    std::map<QString,QGraphicsView *> views;
    std::map<QString, QHBoxLayout *> layouts;

    QAction *editSubtasks;
    QAction *exitAction;
    QAction *saveAction;
    QAction *saveAsAction;
    QAction *loadAction;
    QAction *addAction;
    QAction *deleteAction;
    QAction *insertEndStateAction;
    QAction *showTransitions;

    QAction *toFrontAction;
    QAction *sendBackAction;
    QAction *aboutAction;

    QMenu *fileMenu;
    QMenu *itemMenu;
    QMenu *optionsMenu;
    QMenu *editMenu;
    QMenu *aboutMenu;

    QToolBar * editToolBar;
    QToolBar * sceneToolbar;

    QComboBox *sceneScaleCombo;
};


#endif
