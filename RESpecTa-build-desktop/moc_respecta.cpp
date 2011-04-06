/****************************************************************************
** Meta object code from reading C++ file 'respecta.h'
**
** Created: Wed Apr 6 13:41:34 2011
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
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      13,   10,    9,    9, 0x08,
      37,    9,    9,    9, 0x08,
      50,   10,    9,    9, 0x08,
      75,    9,    9,    9, 0x08,
      90,    9,    9,    9, 0x08,
     108,  103,    9,    9, 0x08,
     139,  133,    9,    9, 0x08,
     166,    9,    9,    9, 0x08,
     185,    9,    9,    9, 0x08,
     204,    9,    9,    9, 0x08,
     226,    9,    9,    9, 0x08,
     248,  103,    9,    9, 0x08,
     277,    9,    9,    9, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_RESpecTa[] = {
    "RESpecTa\0\0id\0buttonGroupClicked(int)\0"
    "deleteItem()\0pointerGroupClicked(int)\0"
    "bringToFront()\0sendToBack()\0item\0"
    "itemInserted(BaseState*)\0scale\0"
    "sceneScaleChanged(QString)\0"
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
        case 0: buttonGroupClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: deleteItem(); break;
        case 2: pointerGroupClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: bringToFront(); break;
        case 4: sendToBack(); break;
        case 5: itemInserted((*reinterpret_cast< BaseState*(*)>(_a[1]))); break;
        case 6: sceneScaleChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: itemColorChanged(); break;
        case 8: lineColorChanged(); break;
        case 9: fillButtonTriggered(); break;
        case 10: lineButtonTriggered(); break;
        case 11: itemSelected((*reinterpret_cast< QGraphicsItem*(*)>(_a[1]))); break;
        case 12: about(); break;
        default: ;
        }
        _id -= 13;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
