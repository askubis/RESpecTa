/****************************************************************************
** Meta object code from reading C++ file 'respecta.h'
**
** Created: Mon Apr 18 11:07:30 2011
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
      21,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      22,    9,   10,    9, 0x08,
      50,   40,    9,    9, 0x08,
      81,   76,   71,    9, 0x08,
     107,    9,    9,    9, 0x08,
     152,    9,    9,    9, 0x08,
     169,  159,    9,    9, 0x08,
     207,  198,    9,    9, 0x08,
     239,  231,    9,    9, 0x08,
     270,  267,    9,    9, 0x08,
     294,    9,    9,    9, 0x08,
     307,  267,    9,    9, 0x08,
     332,    9,    9,    9, 0x08,
     347,    9,    9,    9, 0x08,
     365,  360,    9,    9, 0x08,
     396,  390,    9,    9, 0x08,
     423,    9,    9,    9, 0x08,
     442,    9,    9,    9, 0x08,
     461,    9,    9,    9, 0x08,
     483,    9,    9,    9, 0x08,
     505,  360,    9,    9, 0x08,
     534,    9,    9,    9, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_RESpecTa[] = {
    "RESpecTa\0\0QStringList\0getSubtasksList()\0"
    "msgString\0reportError(QString)\0bool\0"
    "line\0lineInserted(Transition*)\0"
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
        case 0: { QStringList _r = getSubtasksList();
            if (_a[0]) *reinterpret_cast< QStringList*>(_a[0]) = _r; }  break;
        case 1: reportError((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: { bool _r = lineInserted((*reinterpret_cast< Transition*(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 3: insertTransition((*reinterpret_cast< std::pair<QString,QString>(*)>(_a[1]))); break;
        case 4: save(); break;
        case 5: selectedSubtaskName((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: InsertState((*reinterpret_cast< BaseState*(*)>(_a[1]))); break;
        case 7: NewSubtaskInserted((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 8: buttonGroupClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: deleteItem(); break;
        case 10: pointerGroupClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: bringToFront(); break;
        case 12: sendToBack(); break;
        case 13: itemInserted((*reinterpret_cast< BaseState*(*)>(_a[1]))); break;
        case 14: sceneScaleChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 15: itemColorChanged(); break;
        case 16: lineColorChanged(); break;
        case 17: fillButtonTriggered(); break;
        case 18: lineButtonTriggered(); break;
        case 19: itemSelected((*reinterpret_cast< QGraphicsItem*(*)>(_a[1]))); break;
        case 20: about(); break;
        default: ;
        }
        _id -= 21;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
