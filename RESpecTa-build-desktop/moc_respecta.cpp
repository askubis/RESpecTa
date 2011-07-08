/****************************************************************************
** Meta object code from reading C++ file 'respecta.h'
**
** Created: Fri Jul 8 17:55:33 2011
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
      27,   14, // methods
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
      80,    9,    9,    9, 0x08,
      99,    9,    9,    9, 0x08,
     112,    9,    9,    9, 0x08,
     124,    9,    9,    9, 0x08,
     152,  140,    9,    9, 0x08,
     174,  140,    9,    9, 0x08,
     214,  198,    9,    9, 0x08,
     264,  246,    9,    9, 0x08,
     300,    9,    9,    9, 0x08,
     325,    9,    9,    9, 0x08,
     349,  339,    9,    9, 0x08,
     380,  375,  370,    9, 0x08,
     406,    9,    9,    9, 0x08,
     451,    9,    9,    9, 0x08,
     458,    9,    9,    9, 0x08,
     465,    9,  370,    9, 0x08,
     483,  474,    9,    9, 0x08,
     507,    9,    9,    9, 0x08,
     520,    9,    9,    9, 0x08,
     535,    9,    9,    9, 0x08,
     548,   10,    9,    9, 0x08,
     579,  573,    9,    9, 0x08,
     606,   10,    9,    9, 0x08,
     635,    9,    9,    9, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_RESpecTa[] = {
    "RESpecTa\0\0item\0itemSelectedSig(QGraphicsItem*)\0"
    "refreshWidgets()\0SignalDeleted()\0"
    "selectionchanged()\0FindOnList()\0"
    "GoToState()\0TabChanged(int)\0subtaskName\0"
    "SubtaskAdded(QString)\0SubtaskRemoved(QString)\0"
    "oldName,newName\0SubtaskChanged(QString,QString)\0"
    "oldState,newState\0ReplaceState(BaseState*,BaseState*)\0"
    "EditTransitionsOfState()\0addEndState()\0"
    "msgString\0reportError(QString)\0bool\0"
    "line\0lineInserted(Transition*)\0"
    "insertTransition(std::pair<QString,QString>)\0"
    "Load()\0save()\0SaveAs()\0newState\0"
    "InsertState(BaseState*)\0deleteItem()\0"
    "bringToFront()\0sendToBack()\0"
    "itemInserted(BaseState*)\0scale\0"
    "sceneScaleChanged(QString)\0"
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
        case 3: selectionchanged(); break;
        case 4: FindOnList(); break;
        case 5: GoToState(); break;
        case 6: TabChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: SubtaskAdded((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 8: SubtaskRemoved((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 9: SubtaskChanged((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 10: ReplaceState((*reinterpret_cast< BaseState*(*)>(_a[1])),(*reinterpret_cast< BaseState*(*)>(_a[2]))); break;
        case 11: EditTransitionsOfState(); break;
        case 12: addEndState(); break;
        case 13: reportError((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 14: { bool _r = lineInserted((*reinterpret_cast< Transition*(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 15: insertTransition((*reinterpret_cast< std::pair<QString,QString>(*)>(_a[1]))); break;
        case 16: Load(); break;
        case 17: save(); break;
        case 18: { bool _r = SaveAs();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 19: InsertState((*reinterpret_cast< BaseState*(*)>(_a[1]))); break;
        case 20: deleteItem(); break;
        case 21: bringToFront(); break;
        case 22: sendToBack(); break;
        case 23: itemInserted((*reinterpret_cast< BaseState*(*)>(_a[1]))); break;
        case 24: sceneScaleChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 25: itemSelected((*reinterpret_cast< QGraphicsItem*(*)>(_a[1]))); break;
        case 26: about(); break;
        default: ;
        }
        _id -= 27;
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
