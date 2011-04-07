/****************************************************************************
** Meta object code from reading C++ file 'respecta.h'
**
** Created: Fri Apr 8 00:14:17 2011
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
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x08,
      27,   17,    9,    9, 0x08,
      65,   56,    9,    9, 0x08,
      97,   89,    9,    9, 0x08,
     128,  125,    9,    9, 0x08,
     152,    9,    9,    9, 0x08,
     165,  125,    9,    9, 0x08,
     190,    9,    9,    9, 0x08,
     205,    9,    9,    9, 0x08,
     223,  218,    9,    9, 0x08,
     254,  248,    9,    9, 0x08,
     281,    9,    9,    9, 0x08,
     300,    9,    9,    9, 0x08,
     319,    9,    9,    9, 0x08,
     341,    9,    9,    9, 0x08,
     363,  218,    9,    9, 0x08,
     392,    9,    9,    9, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_RESpecTa[] = {
    "RESpecTa\0\0save()\0newString\0"
    "selectedSubtaskName(QString)\0newState\0"
    "InsertState(BaseState*)\0newName\0"
    "NewSubtaskInserted(QString)\0id\0"
    "buttonGroupClicked(int)\0deleteItem()\0"
    "pointerGroupClicked(int)\0bringToFront()\0"
    "sendToBack()\0item\0itemInserted(BaseState*)\0"
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
        case 0: save(); break;
        case 1: selectedSubtaskName((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: InsertState((*reinterpret_cast< BaseState*(*)>(_a[1]))); break;
        case 3: NewSubtaskInserted((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: buttonGroupClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: deleteItem(); break;
        case 6: pointerGroupClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: bringToFront(); break;
        case 8: sendToBack(); break;
        case 9: itemInserted((*reinterpret_cast< BaseState*(*)>(_a[1]))); break;
        case 10: sceneScaleChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 11: itemColorChanged(); break;
        case 12: lineColorChanged(); break;
        case 13: fillButtonTriggered(); break;
        case 14: lineButtonTriggered(); break;
        case 15: itemSelected((*reinterpret_cast< QGraphicsItem*(*)>(_a[1]))); break;
        case 16: about(); break;
        default: ;
        }
        _id -= 17;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
