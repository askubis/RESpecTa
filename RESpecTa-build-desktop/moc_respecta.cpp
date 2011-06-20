/****************************************************************************
** Meta object code from reading C++ file 'respecta.h'
**
** Created: Mon Jun 20 14:05:18 2011
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
      33,   14, // methods
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
      96,    9,    9,    9, 0x08,
     118,    9,    9,    9, 0x08,
     144,  142,    9,    9, 0x08,
     176,    9,    9,    9, 0x08,
     231,  200,    9,    9, 0x08,
     275,    9,    9,    9, 0x08,
     300,    9,    9,    9, 0x08,
     324,  314,    9,    9, 0x08,
     355,  350,  345,    9, 0x08,
     381,    9,    9,    9, 0x08,
     426,    9,    9,    9, 0x08,
     433,    9,    9,    9, 0x08,
     440,    9,  345,    9, 0x08,
     459,  449,    9,    9, 0x08,
     497,  488,    9,    9, 0x08,
     529,  521,    9,    9, 0x08,
     560,  557,    9,    9, 0x08,
     584,    9,    9,    9, 0x08,
     597,  557,    9,    9, 0x08,
     622,    9,    9,    9, 0x08,
     637,    9,    9,    9, 0x08,
     650,   10,    9,    9, 0x08,
     681,  675,    9,    9, 0x08,
     708,    9,    9,    9, 0x08,
     727,    9,    9,    9, 0x08,
     746,    9,    9,    9, 0x08,
     768,    9,    9,    9, 0x08,
     790,   10,    9,    9, 0x08,
     819,    9,    9,    9, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_RESpecTa[] = {
    "RESpecTa\0\0item\0itemSelectedSig(QGraphicsItem*)\0"
    "refreshWidgets()\0SignalDeleted()\0"
    "TabChanged(int)\0SubtaskAdded(QString)\0"
    "SubtaskRemoved(QString)\0,\0"
    "SubtaskChanged(QString,QString)\0"
    "OpenSubtaskEditDialog()\0"
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
        case 3: TabChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: SubtaskAdded((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: SubtaskRemoved((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: SubtaskChanged((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 7: OpenSubtaskEditDialog(); break;
        case 8: ReplaceState((*reinterpret_cast< BaseState*(*)>(_a[1])),(*reinterpret_cast< BaseState*(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 9: EditTransitionsOfState(); break;
        case 10: addEndState(); break;
        case 11: reportError((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 12: { bool _r = lineInserted((*reinterpret_cast< Transition*(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 13: insertTransition((*reinterpret_cast< std::pair<QString,QString>(*)>(_a[1]))); break;
        case 14: Load(); break;
        case 15: save(); break;
        case 16: { bool _r = SaveAs();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 17: selectedSubtaskName((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 18: InsertState((*reinterpret_cast< BaseState*(*)>(_a[1]))); break;
        case 19: NewSubtaskInserted((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 20: buttonGroupClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 21: deleteItem(); break;
        case 22: pointerGroupClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 23: bringToFront(); break;
        case 24: sendToBack(); break;
        case 25: itemInserted((*reinterpret_cast< BaseState*(*)>(_a[1]))); break;
        case 26: sceneScaleChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 27: itemColorChanged(); break;
        case 28: lineColorChanged(); break;
        case 29: fillButtonTriggered(); break;
        case 30: lineButtonTriggered(); break;
        case 31: itemSelected((*reinterpret_cast< QGraphicsItem*(*)>(_a[1]))); break;
        case 32: about(); break;
        default: ;
        }
        _id -= 33;
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
