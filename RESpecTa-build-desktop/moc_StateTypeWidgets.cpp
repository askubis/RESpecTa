/****************************************************************************
** Meta object code from reading C++ file 'StateTypeWidgets.h'
**
** Created: Sun Apr 3 15:04:56 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../StateTypeWidgets.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'StateTypeWidgets.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MyTypeWidget[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

static const char qt_meta_stringdata_MyTypeWidget[] = {
    "MyTypeWidget\0"
};

const QMetaObject MyTypeWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_MyTypeWidget,
      qt_meta_data_MyTypeWidget, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MyTypeWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MyTypeWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MyTypeWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MyTypeWidget))
        return static_cast<void*>(const_cast< MyTypeWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int MyTypeWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_sysIniWidget[] = {

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
      14,   13,   13,   13, 0x08,
      33,   13,   13,   13, 0x08,
      52,   13,   13,   13, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_sysIniWidget[] = {
    "sysIniWidget\0\0removeECPSection()\0"
    "createECPSection()\0changeMPSection()\0"
};

const QMetaObject sysIniWidget::staticMetaObject = {
    { &MyTypeWidget::staticMetaObject, qt_meta_stringdata_sysIniWidget,
      qt_meta_data_sysIniWidget, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &sysIniWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *sysIniWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *sysIniWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_sysIniWidget))
        return static_cast<void*>(const_cast< sysIniWidget*>(this));
    return MyTypeWidget::qt_metacast(_clname);
}

int sysIniWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = MyTypeWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: removeECPSection(); break;
        case 1: createECPSection(); break;
        case 2: changeMPSection(); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}
static const uint qt_meta_data_runGenWidget[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x08,
      27,   13,   13,   13, 0x08,
      40,   13,   13,   13, 0x08,
      50,   13,   13,   13, 0x08,
      71,   13,   13,   13, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_runGenWidget[] = {
    "runGenWidget\0\0PoseCancel()\0PosesReset()\0"
    "PoseAdd()\0showAddPosesDialog()\0"
    "selectTrjFilePath()\0"
};

const QMetaObject runGenWidget::staticMetaObject = {
    { &MyTypeWidget::staticMetaObject, qt_meta_stringdata_runGenWidget,
      qt_meta_data_runGenWidget, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &runGenWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *runGenWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *runGenWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_runGenWidget))
        return static_cast<void*>(const_cast< runGenWidget*>(this));
    return MyTypeWidget::qt_metacast(_clname);
}

int runGenWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = MyTypeWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: PoseCancel(); break;
        case 1: PosesReset(); break;
        case 2: PoseAdd(); break;
        case 3: showAddPosesDialog(); break;
        case 4: selectTrjFilePath(); break;
        default: ;
        }
        _id -= 5;
    }
    return _id;
}
static const uint qt_meta_data_emptyGenForSetWidget[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      22,   21,   21,   21, 0x08,
      33,   21,   21,   21, 0x08,
      47,   21,   21,   21, 0x08,
      59,   21,   21,   21, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_emptyGenForSetWidget[] = {
    "emptyGenForSetWidget\0\0addFirst()\0"
    "removeFirst()\0addSecond()\0removeSecond()\0"
};

const QMetaObject emptyGenForSetWidget::staticMetaObject = {
    { &MyTypeWidget::staticMetaObject, qt_meta_stringdata_emptyGenForSetWidget,
      qt_meta_data_emptyGenForSetWidget, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &emptyGenForSetWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *emptyGenForSetWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *emptyGenForSetWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_emptyGenForSetWidget))
        return static_cast<void*>(const_cast< emptyGenForSetWidget*>(this));
    return MyTypeWidget::qt_metacast(_clname);
}

int emptyGenForSetWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = MyTypeWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: addFirst(); break;
        case 1: removeFirst(); break;
        case 2: addSecond(); break;
        case 3: removeSecond(); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}
static const uint qt_meta_data_emptyGenWidget[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

static const char qt_meta_stringdata_emptyGenWidget[] = {
    "emptyGenWidget\0"
};

const QMetaObject emptyGenWidget::staticMetaObject = {
    { &MyTypeWidget::staticMetaObject, qt_meta_stringdata_emptyGenWidget,
      qt_meta_data_emptyGenWidget, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &emptyGenWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *emptyGenWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *emptyGenWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_emptyGenWidget))
        return static_cast<void*>(const_cast< emptyGenWidget*>(this));
    return MyTypeWidget::qt_metacast(_clname);
}

int emptyGenWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = MyTypeWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_waitStateWidget[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

static const char qt_meta_stringdata_waitStateWidget[] = {
    "waitStateWidget\0"
};

const QMetaObject waitStateWidget::staticMetaObject = {
    { &MyTypeWidget::staticMetaObject, qt_meta_stringdata_waitStateWidget,
      qt_meta_data_waitStateWidget, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &waitStateWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *waitStateWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *waitStateWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_waitStateWidget))
        return static_cast<void*>(const_cast< waitStateWidget*>(this));
    return MyTypeWidget::qt_metacast(_clname);
}

int waitStateWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = MyTypeWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_stopGenWidget[] = {

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
      15,   14,   14,   14, 0x08,
      26,   14,   14,   14, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_stopGenWidget[] = {
    "stopGenWidget\0\0addFirst()\0removeFirst()\0"
};

const QMetaObject stopGenWidget::staticMetaObject = {
    { &MyTypeWidget::staticMetaObject, qt_meta_stringdata_stopGenWidget,
      qt_meta_data_stopGenWidget, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &stopGenWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *stopGenWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *stopGenWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_stopGenWidget))
        return static_cast<void*>(const_cast< stopGenWidget*>(this));
    return MyTypeWidget::qt_metacast(_clname);
}

int stopGenWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = MyTypeWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: addFirst(); break;
        case 1: removeFirst(); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}
static const uint qt_meta_data_iniSensorWidget[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

static const char qt_meta_stringdata_iniSensorWidget[] = {
    "iniSensorWidget\0"
};

const QMetaObject iniSensorWidget::staticMetaObject = {
    { &MyTypeWidget::staticMetaObject, qt_meta_stringdata_iniSensorWidget,
      qt_meta_data_iniSensorWidget, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &iniSensorWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *iniSensorWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *iniSensorWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_iniSensorWidget))
        return static_cast<void*>(const_cast< iniSensorWidget*>(this));
    return MyTypeWidget::qt_metacast(_clname);
}

int iniSensorWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = MyTypeWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_getSensorWidget[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

static const char qt_meta_stringdata_getSensorWidget[] = {
    "getSensorWidget\0"
};

const QMetaObject getSensorWidget::staticMetaObject = {
    { &MyTypeWidget::staticMetaObject, qt_meta_stringdata_getSensorWidget,
      qt_meta_data_getSensorWidget, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &getSensorWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *getSensorWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *getSensorWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_getSensorWidget))
        return static_cast<void*>(const_cast< getSensorWidget*>(this));
    return MyTypeWidget::qt_metacast(_clname);
}

int getSensorWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = MyTypeWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_PoseDialog[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

static const char qt_meta_stringdata_PoseDialog[] = {
    "PoseDialog\0"
};

const QMetaObject PoseDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_PoseDialog,
      qt_meta_data_PoseDialog, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &PoseDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *PoseDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *PoseDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PoseDialog))
        return static_cast<void*>(const_cast< PoseDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int PoseDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_ECPDialog[] = {

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
      11,   10,   10,   10, 0x08,
      20,   10,   10,   10, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ECPDialog[] = {
    "ECPDialog\0\0remove()\0add()\0"
};

const QMetaObject ECPDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_ECPDialog,
      qt_meta_data_ECPDialog, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ECPDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ECPDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ECPDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ECPDialog))
        return static_cast<void*>(const_cast< ECPDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int ECPDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: remove(); break;
        case 1: add(); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}
static const uint qt_meta_data_MPDialog[] = {

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
      10,    9,    9,    9, 0x08,
      19,    9,    9,    9, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MPDialog[] = {
    "MPDialog\0\0remove()\0add()\0"
};

const QMetaObject MPDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_MPDialog,
      qt_meta_data_MPDialog, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MPDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MPDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MPDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MPDialog))
        return static_cast<void*>(const_cast< MPDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int MPDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: remove(); break;
        case 1: add(); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE