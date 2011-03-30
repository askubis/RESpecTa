/****************************************************************************
** Meta object code from reading C++ file 'transWidget.h'
**
** Created: Wed Mar 30 13:35:44 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../transWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'transWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_TransWidget[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      23,   13,   12,   12, 0x08,
      46,   12,   12,   12, 0x08,
      60,   12,   12,   12, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_TransWidget[] = {
    "TransWidget\0\0newString\0lengthChanged(QString)\0"
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
        case 0: lengthChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: AcceptTrans(); break;
        case 2: InsertTrans(); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
