
#ifndef RESPECTA_H
#define RESPECTA_H
class RESpecTa;

#include <QMainWindow>

#include "baseState.h"
#include "Model.h"
#include "TransDialog.h"
#include "subtaskDialog.h"
#include "TreeModel.h"
#include "TreeItem.h"
#include "myTreeView.h"

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

class RESpecTa : public QMainWindow
{
    Q_OBJECT
public:
   RESpecTa(){}
   RESpecTa(Model * newmod );

   void WasChanged();
   void setCurrentSubtask(QString newSubtask){currentSubtask = newSubtask;}
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
    void FindOnList();
    void GoToState();
    void TabChanged(int);
    void SubtaskAdded(QString);
    void SubtaskRemoved(QString);
    void SubtaskChanged(QString, QString);
    void OpenSubtaskEditDialog();
    void ReplaceState(BaseState * oldState, BaseState * newState, QString oldStateName);
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
    void deleteItem();
    void bringToFront();
    void sendToBack();
    void itemInserted(BaseState *item);
    void sceneScaleChanged(const QString &scale);
    void itemSelected(QGraphicsItem *item);
    void about();

private:
    QStringList loadGraphics(QXmlStreamReader * reader, QString subName);
    void closeEvent(QCloseEvent *event);
    void createFileMenu();
    void createEditMenu();
    void createOptionsMenu();
    void createHelpMenu();
    void createToolbars();

    void LoadFile(QString filename);
    QStringList LoadStates(QString filename);
    QStringList LoadTransitions(QString filename);

    QStringList scales;

    Model * mod;
    QString currentSubtask;
    QString SaveName;
    QString SaveFolder;

    myTreeView *TreeView;
    TreeModel *treeModel;
    QWidget *editWidget;
    TransDialog * transDial;

    SubtaskDialog * subDialog;

    std::map<QString,QWidget *> widgets;
    QTabWidget * tabWidget;
    QLineEdit * findLineEdit;
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

    QToolBar * editToolBar;
    QToolBar * sceneToolbar;

    QComboBox *sceneScaleCombo;
};


#endif
