/****************************************************************************
** Meta object code from reading C++ file 'respecta.h'
**
** Created: Fri May 20 16:43:49 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../respecta.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'respecta.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_RESpecTa[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      28,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      15,   10,    9,    9, 0x05,
      47,    9,    9,    9, 0x05,
      64,    9,    9,    9, 0x05,

 // slots: signature, parameters, type, tag, flags
     111,   80,    9,    9, 0x08,
     155,    9,    9,    9, 0x08,
     180,    9,    9,    9, 0x08,
     204,  194,    9,    9, 0x08,
     235,  230,  225,    9, 0x08,
     261,    9,    9,    9, 0x08,
     306,    9,    9,    9, 0x08,
     313,    9,    9,    9, 0x08,
     320,    9,    9,    9, 0x08,
     339,  329,    9,    9, 0x08,
     377,  368,    9,    9, 0x08,
     409,  401,    9,    9, 0x08,
     440,  437,    9,    9, 0x08,
     464,    9,    9,    9, 0x08,
     477,  437,    9,    9, 0x08,
     502,    9,    9,    9, 0x08,
     517,    9,    9,    9, 0x08,
     530,   10,    9,    9, 0x08,
     561,  555,    9,    9, 0x08,
     588,    9,    9,    9, 0x08,
     607,    9,    9,    9, 0x08,
     626,    9,    9,    9, 0x08,
     648,    9,    9,    9, 0x08,
     670,   10,    9,    9, 0x08,
     699,    9,    9,    9, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_RESpecTa[] = {
    "RESpecTa\0\0item\0itemSelectedSig(QGraphicsItem*)\0"
    "refreshWidgets()\0SignalDeleted()\0"
    "oldState,newState,oldStateName\0"
    "ReplaceState(BaseState*,BaseState*,QString)\0"
    "EditTransitionsOfState()\0addEndState()\0"
    "msgString\0reportError(QString)\0bool\0"
    "line\0lineInserted(Transition*)\0"
    "insertTransition(std::pair<QString,QString>)\0"
    "Load()\0save()\0SaveAs()\0newString\0"
    "selectedSubtaskName(QString)\0newState\0"
    "InsertState(BaseState*)\0newName\0"
    "NewSubtaskInserted(QString)\0id\0"
    "buttonGroupClicked(int)\0deleteItem()\0"
    "pointerGroupClicked(int)\0bringToFront()\0"
    "sendToBack()\0itemInserted(BaseState*)\0"
    "scale\0sceneScaleChanged(QString)\0"
    "itemColorChanged()\0lineColorChanged()\0"
    "fillButtonTriggered()\0lineButtonTriggered()\0"
    "itemSelected(QGraphicsItem*)\0about()\0"
};

const QMetaObject RESpecTa::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_RESpecTa,
      qt_meta_data_RESpecTa, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &RESpecTa::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *RESpecTa::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *RESpecTa::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_RESpecTa))
        return static_cast<void*>(const_cast< RESpecTa*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int RESpecTa::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: itemSelectedSig((*reinterpret_cast< QGraphicsItem*(*)>(_a[1]))); break;
        case 1: refreshWidgets(); break;
        case 2: SignalDeleted(); break;
        case 3: ReplaceState((*reinterpret_cast< BaseState*(*)>(_a[1])),(*reinterpret_cast< BaseState*(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 4: EditTransitionsOfState(); break;
        case 5: addEndState(); break;
        case 6: reportError((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: { bool _r = lineInserted((*reinterpret_cast< Transition*(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 8: insertTransition((*reinterpret_cast< std::pair<QString,QString>(*)>(_a[1]))); break;
        case 9: Load(); break;
        case 10: save(); break;
        case 11: SaveAs(); break;
        case 12: selectedSubtaskName((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 13: InsertState((*reinterpret_cast< BaseState*(*)>(_a[1]))); break;
        case 14: NewSubtaskInserted((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 15: buttonGroupClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 16: deleteItem(); break;
        case 17: pointerGroupClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 18: bringToFront(); break;
        case 19: sendToBack(); break;
        case 20: itemInserted((*reinterpret_cast< BaseState*(*)>(_a[1]))); break;
        case 21: sceneScaleChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 22: itemColorChanged(); break;
        case 23: lineColorChanged(); break;
        case 24: fillButtonTriggered(); break;
        case 25: lineButtonTriggered(); break;
        case 26: itemSelected((*reinterpret_cast< QGraphicsItem*(*)>(_a[1]))); break;
        case 27: about(); break;
        default: ;
        }
        _id -= 28;
    }
    return _id;
}

// SIGNAL 0
void RESpecTa::itemSelectedSig(QGraphicsItem * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void RESpecTa::refreshWidgets()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void RESpecTa::SignalDeleted()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}
QT_END_MOC_NAMESPACE
