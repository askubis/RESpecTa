
#ifndef RESPECTA_H
#define RESPECTA_H
class RESpecTa;

#include <QMainWindow>
//#include "GlobalVariables.h"

#include "baseState.h"
#include "Model.h"
#include "TransDialog.h"
#include "subtaskDialog.h"
//#include "Graph.h"

class DiagramScene;
//class Model;


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


class RESpecTa : public QMainWindow
{
    Q_OBJECT

public:
    RESpecTa(){}
    RESpecTa(Model * newmod );

    void setCurrentSubtask(QString newSubtask){currentSubtask = newSubtask;}
   //MyGraphType * getGraph (){return myGraph;}
   //std::map<std::string, MyGraphType *> * getSubtasks (){return subtasks;}
   void getError(QString x){reportError(x);}
   void clearSaveName() {SaveName=QString();}
   void deleteState(BaseState * state);
   void deleteTrans(Transition * trans);

   void SaveGraphicsAttributes(QXmlStreamWriter * writer, QString SubName);

signals:
   void itemSelectedSig(QGraphicsItem *item);
   void refreshWidgets();
   void SignalDeleted();


private slots:
    void TabChanged(int);
    void SubtaskAdded(QString);
    void SubtaskRemoved(QString);
    void SubtaskChanged(QString, QString);
    void OpenSubtaskEditDialog();
    void ReplaceState(BaseState * oldState, BaseState * newState, QString oldStateName);
    //QStringList getSubtasksList();
    void EditTransitionsOfState();
    void addEndState();
    void reportError(QString msgString);
    bool lineInserted(Transition *line);
    void insertTransition(std::pair<QString,QString>);
    void Load();
    void save();
    bool SaveAs();
    void selectedSubtaskName(QString newString);
    void InsertState(BaseState * newState);
    void NewSubtaskInserted(QString newName);
    //void backgroundButtonGroupClicked(QAbstractButton *button);
    void buttonGroupClicked(int id);
    void deleteItem();
    void pointerGroupClicked(int id);
    void bringToFront();
    void sendToBack();
    void itemInserted(BaseState *item);
    //void textInserted(QGraphicsTextItem *item);
    //void currentFontChanged(const QFont &font);
    //void fontSizeChanged(const QString &size);
    void sceneScaleChanged(const QString &scale);
    //void textColorChanged();
    void itemColorChanged();
    void lineColorChanged();
    //void textButtonTriggered();
    void fillButtonTriggered();
    void lineButtonTriggered();
    //void handleFontChange();
    void itemSelected(QGraphicsItem *item);
    void about();

private:
    QStringList loadGraphics(QXmlStreamReader * reader, QString subName);
    void closeEvent(QCloseEvent *event);
    void createFileMenu();
    void createEditMenu();
    void createOptionsMenu();
    void createHelpMenu();
    void createToolBox();
    void createActions();
    void createToolbars();

    void LoadFile(QString filename);
    QStringList LoadStates(QString filename);
    QStringList LoadTransitions(QString filename);

    QStringList scales;

    Model * mod;
    QString currentSubtask;
    QString SaveName;
    QString SaveFolder;

    QWidget *editWidget;
    TransDialog * transDial;

    SubtaskDialog * subDialog;


    QWidget *createBackgroundCellWidget(const QString &text,
                                        const QString &image);
    QWidget *createCellWidget(const QString &text);
    QMenu *createColorMenu(const char *slot, QColor defaultColor);
    QIcon createColorToolButtonIcon(const QString &image, QColor color);
    QIcon createColorIcon(QColor color);

    std::map<QString,QWidget *> widgets;
    QTabWidget * tabWidget;
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
    QMenu *aboutMenu;

    QToolBar *textToolBar;
    QToolBar *editToolBar;
    QToolBar *colorToolBar;
    QToolBar *pointerToolbar;

    QComboBox *sceneScaleCombo;
    QComboBox *itemColorCombo;
    QComboBox *textColorCombo;
    QComboBox *fontSizeCombo;
    QFontComboBox *fontCombo;

    QToolBox *toolBox;
    QButtonGroup *buttonGroup;
    QButtonGroup *pointerTypeGroup;
    QButtonGroup *backgroundButtonGroup;
    QToolButton *fontColorToolButton;
    QToolButton *fillColorToolButton;
    QToolButton *lineColorToolButton;
    QAction *boldAction;
    QAction *underlineAction;
    QAction *italicAction;
    QAction *textAction;
    QAction *fillAction;
    QAction *lineAction;
};


#endif
