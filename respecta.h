
#ifndef RESPECTA_H
#define RESPECTA_H

#include <QMainWindow>
//#include "GlobalVariables.h"

#include "baseState.h"
#include "Graph.h"

class DiagramScene;

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

//! [0]
class RESpecTa : public QMainWindow
{
    Q_OBJECT

public:
   RESpecTa();
   void setCurrentSubtask(QString newSubtask){currentSubtask = newSubtask;}
   MyGraphType * getGraph (){return myGraph;}
   std::map<std::string, MyGraphType *> * getSubtasks (){return subtasks;}


private slots:
    QStringList getSubtasksList();
    void reportError(QString msgString);
    bool lineInserted(Transition *line);
    void insertTransition(std::pair<QString,QString>);
    void save();
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
    void createFileMenu();
    void createEditMenu();
    void createHelpMenu();
    void createToolBox();
    void createActions();
    void createToolbars();



    MyGraphType * myGraph;
    std::map<std::string, MyGraphType *> * subtasks;
    QString currentSubtask;

    QWidget *editWidget;


    QWidget *createBackgroundCellWidget(const QString &text,
                                        const QString &image);
    QWidget *createCellWidget(const QString &text);
    QMenu *createColorMenu(const char *slot, QColor defaultColor);
    QIcon createColorToolButtonIcon(const QString &image, QColor color);
    QIcon createColorIcon(QColor color);

    DiagramScene *scene;
    QGraphicsView *view;

    QAction *exitAction;
    QAction *saveAction;
    QAction *loadAction;
    QAction *addAction;
    QAction *deleteAction;

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
//! [0]

#endif
