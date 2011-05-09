/****************************************************************************
** Meta object code from reading C++ file 'stateWidget.h'
**
** Created: Mon May 9 14:38:05 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../stateWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'stateWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_StateWidget[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: signature, parameters, type, tag, flags
      28,   13,   12,   12, 0x05,
      62,   53,   12,   12, 0x05,
      96,   86,   12,   12, 0x05,
     135,  125,   12,   12, 0x05,
     174,  156,   12,   12, 0x05,

 // slots: signature, parameters, type, tag, flags
     210,  125,   12,   12, 0x08,
     239,  232,   12,   12, 0x08,
     261,   12,   12,   12, 0x08,
     280,   12,   12,   12, 0x08,
     309,   86,   12,   12, 0x08,
     344,  339,   12,   12, 0x08,
     367,   12,   12,   12, 0x08,
     381,   12,   12,   12, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_StateWidget[] = {
    "StateWidget\0\0newSubtaskName\0"
    "SubtaskInserted(QString)\0newState\0"
    "InsertState(BaseState*)\0newString\0"
    "selectedSubtaskName(QString)\0msgString\0"
    "reportError(QString)\0oldState,newState\0"
    "ReplaceState(BaseState*,BaseState*)\0"
    "forwardError(QString)\0chosen\0"
    "setStateSubclass(int)\0createNewSubtask()\0"
    "SubtaskIndexChanged(QString)\0"
    "lengthSubtaskChanged(QString)\0text\0"
    "lengthChanged(QString)\0AcceptState()\0"
    "InsertState()\0"
};

const QMetaObject StateWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_StateWidget,
      qt_meta_data_StateWidget, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &StateWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *StateWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *StateWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_StateWidget))
        return static_cast<void*>(const_cast< StateWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int StateWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: SubtaskInserted((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: InsertState((*reinterpret_cast< BaseState*(*)>(_a[1]))); break;
        case 2: selectedSubtaskName((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: reportError((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: ReplaceState((*reinterpret_cast< BaseState*(*)>(_a[1])),(*reinterpret_cast< BaseState*(*)>(_a[2]))); break;
        case 5: forwardError((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: setStateSubclass((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: createNewSubtask(); break;
        case 8: SubtaskIndexChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 9: lengthSubtaskChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 10: lengthChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 11: AcceptState(); break;
        case 12: InsertState(); break;
        default: ;
        }
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void StateWidget::SubtaskInserted(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void StateWidget::InsertState(BaseState * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void StateWidget::selectedSubtaskName(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void StateWidget::reportError(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void StateWidget::ReplaceState(BaseState * _t1, BaseState * _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_END_MOC_NAMESPACE
