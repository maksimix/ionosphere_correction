/****************************************************************************
** Meta object code from reading C++ file 'drawmembase.h'
**
** Created:
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../draw/drawmembase.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'drawmembase.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DrawMemBase[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: signature, parameters, type, tag, flags
      15,   13,   12,   12, 0x05,
      46,   12,   12,   12, 0x05,
      78,   68,   12,   12, 0x05,
     124,  118,   12,   12, 0x05,
     162,   13,   12,   12, 0x05,
     201,   12,   12,   12, 0x05,
     225,   12,   12,   12, 0x05,

 // slots: signature, parameters, type, tag, flags
     249,   13,   12,   12, 0x0a,
     292,  288,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_DrawMemBase[] = {
    "DrawMemBase\0\0,\0signalRealValue(double,double)\0"
    "signalResetMarkFild()\0kol,x1,x2\0"
    "signalChangeMarkFild(int,double,double)\0"
    "x1,x2\0signalChangeSelectFild(double,double)\0"
    "signalPressMouse(long,Qt::MouseButton)\0"
    "signalResetSelectFild()\0signalReleaseMouseMid()\0"
    "slotSetMarkerToPosition(double,double)\0"
    "str\0setTextMetka(QString&)\0"
};

const QMetaObject DrawMemBase::staticMetaObject = {
    { &WIDGET::staticMetaObject, qt_meta_stringdata_DrawMemBase,
      qt_meta_data_DrawMemBase, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DrawMemBase::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DrawMemBase::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DrawMemBase::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DrawMemBase))
        return static_cast<void*>(const_cast< DrawMemBase*>(this));
    return WIDGET::qt_metacast(_clname);
}

int DrawMemBase::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = WIDGET::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: signalRealValue((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 1: signalResetMarkFild(); break;
        case 2: signalChangeMarkFild((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3]))); break;
        case 3: signalChangeSelectFild((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 4: signalPressMouse((*reinterpret_cast< long(*)>(_a[1])),(*reinterpret_cast< Qt::MouseButton(*)>(_a[2]))); break;
        case 5: signalResetSelectFild(); break;
        case 6: signalReleaseMouseMid(); break;
        case 7: slotSetMarkerToPosition((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 8: setTextMetka((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void DrawMemBase::signalRealValue(double _t1, double _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void DrawMemBase::signalResetMarkFild()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void DrawMemBase::signalChangeMarkFild(int _t1, double _t2, double _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void DrawMemBase::signalChangeSelectFild(double _t1, double _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void DrawMemBase::signalPressMouse(long _t1, Qt::MouseButton _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void DrawMemBase::signalResetSelectFild()
{
    QMetaObject::activate(this, &staticMetaObject, 5, 0);
}

// SIGNAL 6
void DrawMemBase::signalReleaseMouseMid()
{
    QMetaObject::activate(this, &staticMetaObject, 6, 0);
}
QT_END_MOC_NAMESPACE
