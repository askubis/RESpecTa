/****************************************************************************
** Meta object code from reading C++ file 'respecta.h'
**
** Created: Fri Apr 15 22:17:03 2011
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
      20,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      20,   10,    9,    9, 0x08,
      51,   46,   41,    9, 0x08,
      77,    9,    9,    9, 0x08,
     122,    9,    9,    9, 0x08,
     139,  129,    9,    9, 0x08,
     177,  168,    9,    9, 0x08,
     209,  201,    9,    9, 0x08,
     240,  237,    9,    9, 0x08,
     264,    9,    9,    9, 0x08,
     277,  237,    9,    9, 0x08,
     302,    9,    9,    9, 0x08,
     317,    9,    9,    9, 0x08,
     335,  330,    9,    9, 0x08,
     366,  360,    9,    9, 0x08,
     393,    9,    9,    9, 0x08,
     412,    9,    9,    9, 0x08,
     431,    9,    9,    9, 0x08,
     453,    9,    9,    9, 0x08,
     475,  330,    9,    9, 0x08,
     504,    9,    9,    9, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_RESpecTa[] = {
    "RESpecTa\0\0msgString\0reportError(QString)\0"
    "bool\0line\0lineInserted(Transition*)\0"
    "insertTransition(std::pair<QString,QString>)\0"
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
        case 0: reportError((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: { bool _r = lineInserted((*reinterpret_cast< Transition*(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 2: insertTransition((*reinterpret_cast< std::pair<QString,QString>(*)>(_a[1]))); break;
        case 3: save(); break;
        case 4: selectedSubtaskName((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: InsertState((*reinterpret_cast< BaseState*(*)>(_a[1]))); break;
        case 6: NewSubtaskInserted((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: buttonGroupClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: deleteItem(); break;
        case 9: pointerGroupClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: bringToFront(); break;
        case 11: sendToBack(); break;
        case 12: itemInserted((*reinterpret_cast< BaseState*(*)>(_a[1]))); break;
        case 13: sceneScaleChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 14: itemColorChanged(); break;
        case 15: lineColorChanged(); break;
        case 16: fillButtonTriggered(); break;
        case 17: lineButtonTriggered(); break;
        case 18: itemSelected((*reinterpret_cast< QGraphicsItem*(*)>(_a[1]))); break;
        case 19: about(); break;
        default: ;
        }
        _id -= 20;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
