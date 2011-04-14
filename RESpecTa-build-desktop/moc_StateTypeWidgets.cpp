/****************************************************************************
** Meta object code from reading C++ file 'StateTypeWidgets.h'
**
** Created: Thu Apr 14 13:49:38 2011
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
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      24,   14,   13,   13, 0x05,

 // slots: signature, parameters, type, tag, flags
      45,   13,   13,   13, 0x08,
      64,   13,   13,   13, 0x08,
      83,   13,   13,   13, 0x08,
     109,  101,   13,   13, 0x08,
     142,  128,   13,   13, 0x08,
     184,   14,   13,   13, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_sysIniWidget[] = {
    "sysIniWidget\0\0msgString\0reportError(QString)\0"
    "removeECPSection()\0createECPSection()\0"
    "changeMPSection()\0newInit\0InsertECP(genInit)\0"
    "sensors,trans\0InsertMP(std::vector<Sensor>,Transmitter)\0"
    "forwardError(QString)\0"
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
        case 0: reportError((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: removeECPSection(); break;
        case 2: createECPSection(); break;
        case 3: changeMPSection(); break;
        case 4: InsertECP((*reinterpret_cast< genInit(*)>(_a[1]))); break;
        case 5: InsertMP((*reinterpret_cast< std::vector<Sensor>(*)>(_a[1])),(*reinterpret_cast< Transmitter(*)>(_a[2]))); break;
        case 6: forwardError((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void sysIniWidget::reportError(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
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
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      24,   14,   13,   13, 0x05,

 // slots: signature, parameters, type, tag, flags
      55,   45,   13,   13, 0x08,
      82,   13,   13,   13, 0x08,
     103,   13,   13,   13, 0x08,
     123,   14,   13,   13, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_runGenWidget[] = {
    "runGenWidget\0\0msgString\0reportError(QString)\0"
    "newCoords\0CoordsInsert(Coordinates*)\0"
    "showAddPosesDialog()\0selectTrjFilePath()\0"
    "forwardError(QString)\0"
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
        case 0: reportError((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: CoordsInsert((*reinterpret_cast< Coordinates*(*)>(_a[1]))); break;
        case 2: showAddPosesDialog(); break;
        case 3: selectTrjFilePath(); break;
        case 4: forwardError((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void runGenWidget::reportError(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
static const uint qt_meta_data_emptyGenForSetWidget[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      32,   22,   21,   21, 0x05,

 // slots: signature, parameters, type, tag, flags
      53,   21,   21,   21, 0x08,
      64,   21,   21,   21, 0x08,
      78,   21,   21,   21, 0x08,
      90,   21,   21,   21, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_emptyGenForSetWidget[] = {
    "emptyGenForSetWidget\0\0msgString\0"
    "reportError(QString)\0addFirst()\0"
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
        case 0: reportError((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: addFirst(); break;
        case 2: removeFirst(); break;
        case 3: addSecond(); break;
        case 4: removeSecond(); break;
        default: ;
        }
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void emptyGenForSetWidget::reportError(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
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
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      25,   15,   14,   14, 0x05,

 // slots: signature, parameters, type, tag, flags
      46,   14,   14,   14, 0x08,
      52,   14,   14,   14, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_stopGenWidget[] = {
    "stopGenWidget\0\0msgString\0reportError(QString)\0"
    "add()\0remove()\0"
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
        case 0: reportError((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: add(); break;
        case 2: remove(); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void stopGenWidget::reportError(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
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
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      22,   12,   11,   11, 0x05,
      59,   49,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
      80,   11,   11,   11, 0x08,
      90,   11,   11,   11, 0x08,
     103,   11,   11,   11, 0x08,
     112,   11,   11,   11, 0x08,
     125,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_PoseDialog[] = {
    "PoseDialog\0\0newCoords\0InsertCoords(Coordinates*)\0"
    "msgString\0reportError(QString)\0AddPose()\0"
    "RemovePose()\0PoseOK()\0PoseCancel()\0"
    "PosesReset()\0"
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
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: InsertCoords((*reinterpret_cast< Coordinates*(*)>(_a[1]))); break;
        case 1: reportError((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: AddPose(); break;
        case 3: RemovePose(); break;
        case 4: PoseOK(); break;
        case 5: PoseCancel(); break;
        case 6: PosesReset(); break;
        default: ;
        }
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void PoseDialog::InsertCoords(Coordinates * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void PoseDialog::reportError(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
static const uint qt_meta_data_ECPDialog[] = {

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
      19,   11,   10,   10, 0x05,
      48,   38,   10,   10, 0x05,

 // slots: signature, parameters, type, tag, flags
      69,   10,   10,   10, 0x08,
      78,   10,   10,   10, 0x08,
      84,   10,   10,   10, 0x08,
      96,   10,   10,   10, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ECPDialog[] = {
    "ECPDialog\0\0newInit\0InsertECP(genInit)\0"
    "msgString\0reportError(QString)\0remove()\0"
    "add()\0OKPressed()\0CancelPressed()\0"
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
        case 0: InsertECP((*reinterpret_cast< genInit(*)>(_a[1]))); break;
        case 1: reportError((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: remove(); break;
        case 3: add(); break;
        case 4: OKPressed(); break;
        case 5: CancelPressed(); break;
        default: ;
        }
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void ECPDialog::InsertECP(genInit _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ECPDialog::reportError(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
static const uint qt_meta_data_MPDialog[] = {

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
      24,   10,    9,    9, 0x05,
      76,   66,    9,    9, 0x05,

 // slots: signature, parameters, type, tag, flags
      97,    9,    9,    9, 0x08,
     106,    9,    9,    9, 0x08,
     112,    9,    9,    9, 0x08,
     124,    9,    9,    9, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MPDialog[] = {
    "MPDialog\0\0sensors,trans\0"
    "InsertMP(std::vector<Sensor>,Transmitter)\0"
    "msgString\0reportError(QString)\0remove()\0"
    "add()\0OKPressed()\0CancelPressed()\0"
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
        case 0: InsertMP((*reinterpret_cast< std::vector<Sensor>(*)>(_a[1])),(*reinterpret_cast< Transmitter(*)>(_a[2]))); break;
        case 1: reportError((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: remove(); break;
        case 3: add(); break;
        case 4: OKPressed(); break;
        case 5: CancelPressed(); break;
        default: ;
        }
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void MPDialog::InsertMP(std::vector<Sensor> _t1, Transmitter _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MPDialog::reportError(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
