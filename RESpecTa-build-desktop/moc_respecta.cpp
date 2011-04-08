/****************************************************************************
** Meta object code from reading C++ file 'respecta.h'
**
** Created: Fri Apr 8 21:01:24 2011
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
      19,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      20,   15,   10,    9, 0x08,
      46,    9,    9,    9, 0x08,
      99,    9,    9,    9, 0x08,
     116,  106,    9,    9, 0x08,
     154,  145,    9,    9, 0x08,
     186,  178,    9,    9, 0x08,
     217,  214,    9,    9, 0x08,
     241,    9,    9,    9, 0x08,
     254,  214,    9,    9, 0x08,
     279,    9,    9,    9, 0x08,
     294,    9,    9,    9, 0x08,
     312,  307,    9,    9, 0x08,
     343,  337,    9,    9, 0x08,
     370,    9,    9,    9, 0x08,
     389,    9,    9,    9, 0x08,
     408,    9,    9,    9, 0x08,
     430,    9,    9,    9, 0x08,
     452,  307,    9,    9, 0x08,
     481,    9,    9,    9, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_RESpecTa[] = {
    "RESpecTa\0\0bool\0line\0lineInserted(Transition*)\0"
    "insertTransition(std::pair<std::string,std::string>)\0"
    "save()\0newString\0selectedSubtaskName(QString)\0"
    "newState\0InsertState(BaseState*)\0"
    "newName\0NewSubtaskInserted(QString)\0"
    "id\0buttonGroupClicked(int)\0deleteItem()\0"
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
        case 0: { bool _r = lineInserted((*reinterpret_cast< Transition*(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 1: insertTransition((*reinterpret_cast< std::pair<std::string,std::string>(*)>(_a[1]))); break;
        case 2: save(); break;
        case 3: selectedSubtaskName((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: InsertState((*reinterpret_cast< BaseState*(*)>(_a[1]))); break;
        case 5: NewSubtaskInserted((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: buttonGroupClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: deleteItem(); break;
        case 8: pointerGroupClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: bringToFront(); break;
        case 10: sendToBack(); break;
        case 11: itemInserted((*reinterpret_cast< BaseState*(*)>(_a[1]))); break;
        case 12: sceneScaleChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 13: itemColorChanged(); break;
        case 14: lineColorChanged(); break;
        case 15: fillButtonTriggered(); break;
        case 16: lineButtonTriggered(); break;
        case 17: itemSelected((*reinterpret_cast< QGraphicsItem*(*)>(_a[1]))); break;
        case 18: about(); break;
        default: ;
        }
        _id -= 19;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
