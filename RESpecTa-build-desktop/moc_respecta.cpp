/****************************************************************************
** Meta object code from reading C++ file 'respecta.h'
**
** Created: Thu May 5 10:25:52 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../respecta.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'respecta.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_RESpecTa[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      23,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      15,   10,    9,    9, 0x05,

 // slots: signature, parameters, type, tag, flags
      47,    9,    9,    9, 0x08,
      72,    9,    9,    9, 0x08,
      96,   86,    9,    9, 0x08,
     127,  122,  117,    9, 0x08,
     153,    9,    9,    9, 0x08,
     198,    9,    9,    9, 0x08,
     215,  205,    9,    9, 0x08,
     253,  244,    9,    9, 0x08,
     285,  277,    9,    9, 0x08,
     316,  313,    9,    9, 0x08,
     340,    9,    9,    9, 0x08,
     353,  313,    9,    9, 0x08,
     378,    9,    9,    9, 0x08,
     393,    9,    9,    9, 0x08,
     406,   10,    9,    9, 0x08,
     437,  431,    9,    9, 0x08,
     464,    9,    9,    9, 0x08,
     483,    9,    9,    9, 0x08,
     502,    9,    9,    9, 0x08,
     524,    9,    9,    9, 0x08,
     546,   10,    9,    9, 0x08,
     575,    9,    9,    9, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_RESpecTa[] = {
    "RESpecTa\0\0item\0itemSelectedSig(QGraphicsItem*)\0"
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
        case 1: EditTransitionsOfState(); break;
        case 2: addEndState(); break;
        case 3: reportError((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: { bool _r = lineInserted((*reinterpret_cast< Transition*(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 5: insertTransition((*reinterpret_cast< std::pair<QString,QString>(*)>(_a[1]))); break;
        case 6: save(); break;
        case 7: selectedSubtaskName((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 8: InsertState((*reinterpret_cast< BaseState*(*)>(_a[1]))); break;
        case 9: NewSubtaskInserted((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 10: buttonGroupClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: deleteItem(); break;
        case 12: pointerGroupClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: bringToFront(); break;
        case 14: sendToBack(); break;
        case 15: itemInserted((*reinterpret_cast< BaseState*(*)>(_a[1]))); break;
        case 16: sceneScaleChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 17: itemColorChanged(); break;
        case 18: lineColorChanged(); break;
        case 19: fillButtonTriggered(); break;
        case 20: lineButtonTriggered(); break;
        case 21: itemSelected((*reinterpret_cast< QGraphicsItem*(*)>(_a[1]))); break;
        case 22: about(); break;
        default: ;
        }
        _id -= 23;
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
