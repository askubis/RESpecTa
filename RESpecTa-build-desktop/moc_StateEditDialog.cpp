/****************************************************************************
** Meta object code from reading C++ file 'StateEditDialog.h'
**
** Created: Wed Mar 30 13:35:36 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../StateEditDialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'StateEditDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_StateEditDialog[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      17,   16,   16,   16, 0x08,
      39,   32,   16,   16, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_StateEditDialog[] = {
    "StateEditDialog\0\0typeAccepted()\0chosen\0"
    "setStateSubclass(int)\0"
};

const QMetaObject StateEditDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_StateEditDialog,
      qt_meta_data_StateEditDialog, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &StateEditDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *StateEditDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *StateEditDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_StateEditDialog))
        return static_cast<void*>(const_cast< StateEditDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int StateEditDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: typeAccepted(); break;
        case 1: setStateSubclass((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
