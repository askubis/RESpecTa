
#include <QtGui>
#include <QLabel>

#include "respecta.h"
#include "baseState.h"
#include "diagramscene.h"
#include "diagramtextitem.h"
#include "Transition.h"
//#include <boost/graph/adjacency_list.hpp>


#include <cstdio>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>

//#include "GraphFunctions.cpp"

#include "editWidget.h"

const int InsertTextButton = 10;

//! [0]
RESpecTa::RESpecTa(Model * newmod)
{
    mod=newmod;

    createFileMenu();
    createEditMenu();
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
//! [0]

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

void RESpecTa::createFileMenu()
{
    exitAction = new QAction(tr("E&xit"), this);
    exitAction->setShortcuts(QKeySequence::Quit);
    exitAction->setStatusTip(tr("Quit Scenediagram example"));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

    saveAction = new QAction(tr("&Save"), this);
    saveAction->setShortcuts(QKeySequence::Save);
    saveAction->setStatusTip(tr("save to file"));
    connect(saveAction, SIGNAL(triggered()), this, SLOT(save()));

    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(exitAction);
    fileMenu->addAction(saveAction);
}

void RESpecTa::save()
{
    //get path
    mod->save("MAIN.xml");


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


//! [1]
/*void RESpecTa::backgroundButtonGroupClicked(QAbstractButton *button)
{
    QList<QAbstractButton *> buttons = backgroundButtonGroup->buttons();
    foreach (QAbstractButton *myButton, buttons) {
    if (myButton != button)
        button->setChecked(false);
    }
    QString text = button->text();
    if (text == tr("Blue Grid"))
        scene->setBackgroundBrush(QPixmap(":/images/background1.png"));
    else if (text == tr("White Grid"))
        scene->setBackgroundBrush(QPixmap(":/images/background2.png"));
    else if (text == tr("Gray Grid"))
        scene->setBackgroundBrush(QPixmap(":/images/background3.png"));
    else
        scene->setBackgroundBrush(QPixmap(":/images/background4.png"));

    scene->update();
    view->update();
}*/
//! [1]

//! [2]
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
//! [2]

//! [3]
void RESpecTa::deleteItem()
{

    //check why there's a bug with deleting transitions attached to a deleted node
    foreach (QGraphicsItem *item, scene->selectedItems())
    {
        if (item->type() == Transition::Type)
        {
            scene->removeItem(item);
            Transition *transition = qgraphicsitem_cast<Transition *>(item);
            mod->deleteTransition(transition);

            //scene->removeItem(item);
            delete item;
        }
    }

    foreach (QGraphicsItem *item, scene->selectedItems())
    {
         if (item->type() == BaseState::Type)
         {
             BaseState * state = qgraphicsitem_cast<BaseState *>(item);
             foreach(Transition * transition, state->getTransitions())
             {
                 mod->deleteTransition(transition);
                 scene->removeItem(transition);
                 delete transition;
             }



             state->removeTransitions();

             mod->deleteState(state);



             scene->removeItem(item);

             delete item;
         }
     }
}
//! [3]

//! [4]
void RESpecTa::pointerGroupClicked(int)
{
    scene->setMode(DiagramScene::Mode(pointerTypeGroup->checkedId()));
}
//! [4]

//! [5]
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
}
//! [5]

//! [6]
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
            zValue = item->zValue() - 0.1;
    }
    selectedItem->setZValue(zValue);
}
//! [6]

//! [7]
void RESpecTa::itemInserted(BaseState *item)
{

    pointerTypeGroup->button(int(DiagramScene::MoveItem))->setChecked(true);
    scene->setMode(DiagramScene::Mode(pointerTypeGroup->checkedId()));
    //Vertex v_new;

    //item->setSubtaskName(currentSubtask);
    mod->addState(item, currentSubtask.toStdString());
    if(currentSubtask.toStdString()==mod->getMainName() && item->getName().toLower()==QString().fromStdString("_end_"))
    {
        item->setName(QString().fromStdString("_STOP_"));
    }
    item->setToolTip(QString().fromStdString(item->Print()));

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
//! [7]



bool RESpecTa::lineInserted(Transition *line)
{

    bool test = mod->tryInsertTransition(line);
    if(test==false)
    {
        reportError(QString("Cannot create a transition between\nstates in different tasks"));
    }
    return test;
}

//! [8]
/*void RESpecTa::textInsertedBaseState *(QGraphicsTextItem *)
{
    buttonGroup->button(InsertTextButton)->setChecked(false);
    scene->setMode(DiagramScene::Mode(pointerTypeGroup->checkedId()));
}*/
//! [8]

//! [9]
/*void RESpecTa::currentFontChanged(const QFont &)
{
    handleFontChange();
}*/
//! [9]

//! [10]
/*void RESpecTa::fontSizeChanged(const QString &)
{
    handleFontChange();
}*/
//! [10]

//! [11]
void RESpecTa::sceneScaleChanged(const QString &scale)
{
    double newScale = scale.left(scale.indexOf(tr("%"))).toDouble() / 100.0;
    QMatrix oldMatrix = view->matrix();
    view->resetMatrix();
    view->translate(oldMatrix.dx(), oldMatrix.dy());
    view->scale(newScale, newScale);
}
//! [11]

//! [12]
/*void RESpecTa::textColorChanged()
{
    textAction = qobject_cast<QAction *>(sender());
    fontColorToolButton->setIcon(createColorToolButtonIcon(
                ":/images/textpointer.png",
                qVariantValue<QColor>(textAction->data())));
    //textButtonTriggered();
}*/
//! [12]

//! [13]
void RESpecTa::itemColorChanged()
{
    fillAction = qobject_cast<QAction *>(sender());
    fillColorToolButton->setIcon(createColorToolButtonIcon(
                 ":/images/floodfill.png",
                 qVariantValue<QColor>(fillAction->data())));
    fillButtonTriggered();
}
//! [13]

//! [14]
void RESpecTa::lineColorChanged()
{
    lineAction = qobject_cast<QAction *>(sender());
    lineColorToolButton->setIcon(createColorToolButtonIcon(
                 ":/images/linecolor.png",
                 qVariantValue<QColor>(lineAction->data())));
    lineButtonTriggered();
}
//! [14]

//! [15]
/*void RESpecTa::textButtonTriggered()
{
    //scene->setTextColor(qVariantValue<QColor>(textAction->data()));
}*/
//! [15]

//! [16]
void RESpecTa::fillButtonTriggered()
{
    scene->setItemColor(qVariantValue<QColor>(fillAction->data()));
}
//! [16]

//! [17]
void RESpecTa::lineButtonTriggered()
{
    scene->setLineColor(qVariantValue<QColor>(lineAction->data()));
}
//! [17]

//! [18]
/*void RESpecTa::handleFontChange()
{
    QFont font = fontCombo->currentFont();
    font.setPointSize(fontSizeCombo->currentText().toInt());
    font.setWeight(boldAction->isChecked() ? QFont::Bold : QFont::Normal);
    font.setItalic(italicAction->isChecked());
    font.setUnderline(underlineAction->isChecked());

    scene->setFont(font);
}*/
//! [18]

//! [19]
void RESpecTa::itemSelected(QGraphicsItem *item)
{
    emit itemSelectedSig(item);
    /*DiagramTextItem *textItem =
    qgraphicsitem_cast<DiagramTextItem *>(item);

    QFont font = textItem->font();
    QColor color = textItem->defaultTextColor();
    fontCombo->setCurrentFont(font);
    fontSizeCombo->setEditText(QString().setNum(font.pointSize()));
    boldAction->setChecked(font.weight() == QFont::Bold);
    italicAction->setChecked(font.italic());
    underlineAction->setChecked(font.underline());*/
}
//! [19]

//! [20]
void RESpecTa::about()
{
    QMessageBox::about(this, tr("About Diagram Scene"),
                       tr("The <b>Diagram Scene</b> example shows "
                          "use of the graphics framework."));
}
//! [20]

//! [21]
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
//! [21]

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


//! [22]
    //toolBox = new QToolBox;
    //toolBox->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Ignored));
    //toolBox->setMinimumWidth(itemWidget->sizeHint().width());
    //toolBox->addItem(itemWidget, tr("Basic Flowchart Shapes"));
    //toolBox->addItem(backgroundWidget, tr("Backgrounds"));
}
//! [22]

//! [23]
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


//! [25]
void RESpecTa::createToolbars()
{
//! [25]
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
//! [26]
    /*fillColorToolButton = new QToolButton;
    fillColorToolButton->setPopupMode(QToolButton::MenuButtonPopup);
    fillColorToolButton->setMenu(createColorMenu(SLOT(itemColorChanged()),
                         Qt::white));
    fillAction = fillColorToolButton->menu()->defaultAction();
    fillColorToolButton->setIcon(createColorToolButtonIcon(
    ":/images/floodfill.png", Qt::white));
    connect(fillColorToolButton, SIGNAL(clicked()),
            this, SLOT(fillButtonTriggered()));*/
//! [26]

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



//! [27]
}
//! [27]

//! [28]
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
//! [28]

//! [29]
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
//! [29]

//! [30]
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
//! [30]

//! [31]
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
//! [31]

//! [32]
QIcon RESpecTa::createColorIcon(QColor color)
{
    QPixmap pixmap(20, 20);
    QPainter painter(&pixmap);
    painter.setPen(Qt::NoPen);
    painter.fillRect(QRect(0, 0, 20, 20), color);

    return QIcon(pixmap);
}
//! [32]

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
    QMessageBox::information(this, QString().fromStdString("Error"), msgString);
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
    if(scene->selectedItems().first()->type()==BaseState::Type)
    {
        BaseState * state = qgraphicsitem_cast<BaseState *>(scene->selectedItems().first());
        transDial->openForAState(state);
        transDial->setModal(true);
        transDial->setVisible(true);
    }
    return;
}

void RESpecTa::ReplaceState(BaseState * oldState, BaseState * newState)
{
    bool check = mod->ReplaceState(oldState,newState);
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
    }
    //state could be somehow chosen to be edited...
}

