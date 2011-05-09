/****************************************************************************
** Meta object code from reading C++ file 'respecta.h'
**
** Created: Mon May 9 14:37:55 2011
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
      24,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      15,   10,    9,    9, 0x05,

 // slots: signature, parameters, type, tag, flags
      65,   47,    9,    9, 0x08,
     101,    9,    9,    9, 0x08,
     126,    9,    9,    9, 0x08,
     150,  140,    9,    9, 0x08,
     181,  176,  171,    9, 0x08,
     207,    9,    9,    9, 0x08,
     252,    9,    9,    9, 0x08,
     269,  259,    9,    9, 0x08,
     307,  298,    9,    9, 0x08,
     339,  331,    9,    9, 0x08,
     370,  367,    9,    9, 0x08,
     394,    9,    9,    9, 0x08,
     407,  367,    9,    9, 0x08,
     432,    9,    9,    9, 0x08,
     447,    9,    9,    9, 0x08,
     460,   10,    9,    9, 0x08,
     491,  485,    9,    9, 0x08,
     518,    9,    9,    9, 0x08,
     537,    9,    9,    9, 0x08,
     556,    9,    9,    9, 0x08,
     578,    9,    9,    9, 0x08,
     600,   10,    9,    9, 0x08,
     629,    9,    9,    9, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_RESpecTa[] = {
    "RESpecTa\0\0item\0itemSelectedSig(QGraphicsItem*)\0"
    "oldState,newState\0ReplaceState(BaseState*,BaseState*)\0"
    "EditTransitionsOfState()\0addEndState()\0"
    "msgString\0reportError(QString)\0bool\0"
    "line\0lineInserted(Transition*)\0"
    "insertTransition(std::pair<QString,QString>)\0"
    "save()\0newString\0selectedSubtaskName(QString)\0"
    "newState\0InsertState(BaseState*)\0"
    "newName\0NewSubtaskInserted(QString)\0"
    "id\0buttonGroupClicked(int)\0deleteItem()\0"
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
        case 1: ReplaceState((*reinterpret_cast< BaseState*(*)>(_a[1])),(*reinterpret_cast< BaseState*(*)>(_a[2]))); break;
        case 2: EditTransitionsOfState(); break;
        case 3: addEndState(); break;
        case 4: reportError((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: { bool _r = lineInserted((*reinterpret_cast< Transition*(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 6: insertTransition((*reinterpret_cast< std::pair<QString,QString>(*)>(_a[1]))); break;
        case 7: save(); break;
        case 8: selectedSubtaskName((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 9: InsertState((*reinterpret_cast< BaseState*(*)>(_a[1]))); break;
        case 10: NewSubtaskInserted((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 11: buttonGroupClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: deleteItem(); break;
        case 13: pointerGroupClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 14: bringToFront(); break;
        case 15: sendToBack(); break;
        case 16: itemInserted((*reinterpret_cast< BaseState*(*)>(_a[1]))); break;
        case 17: sceneScaleChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 18: itemColorChanged(); break;
        case 19: lineColorChanged(); break;
        case 20: fillButtonTriggered(); break;
        case 21: lineButtonTriggered(); break;
        case 22: itemSelected((*reinterpret_cast< QGraphicsItem*(*)>(_a[1]))); break;
        case 23: about(); break;
        default: ;
        }
        _id -= 24;
    }
    return _id;
}

// SIGNAL 0
void RESpecTa::itemSelectedSig(QGraphicsItem * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
