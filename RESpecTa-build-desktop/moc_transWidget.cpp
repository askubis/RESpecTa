/****************************************************************************
** Meta object code from reading C++ file 'transWidget.h'
**
** Created: Fri Jul 8 17:55:53 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../transWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'transWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_TransWidget[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x05,
      58,   12,   12,   12, 0x05,

 // slots: signature, parameters, type, tag, flags
      79,   12,   12,   12, 0x08,
     113,  103,   12,   12, 0x08,
     136,   12,   12,   12, 0x08,
     150,   12,   12,   12, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_TransWidget[] = {
    "TransWidget\0\0insertTransition(std::pair<QString,QString>)\0"
    "reportError(QString)\0subtaskChanged(QString)\0"
    "newString\0lengthChanged(QString)\0"
    "AcceptTrans()\0InsertTrans()\0"
};

const QMetaObject TransWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_TransWidget,
      qt_meta_data_TransWidget, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &TransWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *TransWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *TransWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TransWidget))
        return static_cast<void*>(const_cast< TransWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int TransWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: insertTransition((*reinterpret_cast< std::pair<QString,QString>(*)>(_a[1]))); break;
        case 1: reportError((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: subtaskChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: lengthChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: AcceptTrans(); break;
        case 5: InsertTrans(); break;
        default: ;
        }
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void TransWidget::insertTransition(std::pair<QString,QString> _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void TransWidget::reportError(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
