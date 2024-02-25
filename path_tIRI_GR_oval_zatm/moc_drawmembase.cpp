/****************************************************************************
** Meta object code from reading C++ file 'drawmembase.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../draw/drawmembase.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'drawmembase.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_DrawMemBase_t {
    QByteArrayData data[17];
    char stringdata0[230];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DrawMemBase_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DrawMemBase_t qt_meta_stringdata_DrawMemBase = {
    {
QT_MOC_LITERAL(0, 0, 11), // "DrawMemBase"
QT_MOC_LITERAL(1, 12, 15), // "signalRealValue"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 19), // "signalResetMarkFild"
QT_MOC_LITERAL(4, 49, 20), // "signalChangeMarkFild"
QT_MOC_LITERAL(5, 70, 3), // "kol"
QT_MOC_LITERAL(6, 74, 2), // "x1"
QT_MOC_LITERAL(7, 77, 2), // "x2"
QT_MOC_LITERAL(8, 80, 22), // "signalChangeSelectFild"
QT_MOC_LITERAL(9, 103, 16), // "signalPressMouse"
QT_MOC_LITERAL(10, 120, 15), // "Qt::MouseButton"
QT_MOC_LITERAL(11, 136, 21), // "signalResetSelectFild"
QT_MOC_LITERAL(12, 158, 21), // "signalReleaseMouseMid"
QT_MOC_LITERAL(13, 180, 23), // "slotSetMarkerToPosition"
QT_MOC_LITERAL(14, 204, 12), // "setTextMetka"
QT_MOC_LITERAL(15, 217, 8), // "QString&"
QT_MOC_LITERAL(16, 226, 3) // "str"

    },
    "DrawMemBase\0signalRealValue\0\0"
    "signalResetMarkFild\0signalChangeMarkFild\0"
    "kol\0x1\0x2\0signalChangeSelectFild\0"
    "signalPressMouse\0Qt::MouseButton\0"
    "signalResetSelectFild\0signalReleaseMouseMid\0"
    "slotSetMarkerToPosition\0setTextMetka\0"
    "QString&\0str"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DrawMemBase[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   59,    2, 0x06 /* Public */,
       3,    0,   64,    2, 0x06 /* Public */,
       4,    3,   65,    2, 0x06 /* Public */,
       8,    2,   72,    2, 0x06 /* Public */,
       9,    2,   77,    2, 0x06 /* Public */,
      11,    0,   82,    2, 0x06 /* Public */,
      12,    0,   83,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      13,    2,   84,    2, 0x0a /* Public */,
      14,    1,   89,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Double, QMetaType::Double,    2,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Double, QMetaType::Double,    5,    6,    7,
    QMetaType::Void, QMetaType::Double, QMetaType::Double,    6,    7,
    QMetaType::Void, QMetaType::Long, 0x80000000 | 10,    2,    2,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Double, QMetaType::Double,    2,    2,
    QMetaType::Void, 0x80000000 | 15,   16,

       0        // eod
};

void DrawMemBase::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        DrawMemBase *_t = static_cast<DrawMemBase *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalRealValue((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 1: _t->signalResetMarkFild(); break;
        case 2: _t->signalChangeMarkFild((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3]))); break;
        case 3: _t->signalChangeSelectFild((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 4: _t->signalPressMouse((*reinterpret_cast< long(*)>(_a[1])),(*reinterpret_cast< Qt::MouseButton(*)>(_a[2]))); break;
        case 5: _t->signalResetSelectFild(); break;
        case 6: _t->signalReleaseMouseMid(); break;
        case 7: _t->slotSetMarkerToPosition((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 8: _t->setTextMetka((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (DrawMemBase::*_t)(double , double );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DrawMemBase::signalRealValue)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (DrawMemBase::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DrawMemBase::signalResetMarkFild)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (DrawMemBase::*_t)(int , double , double );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DrawMemBase::signalChangeMarkFild)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (DrawMemBase::*_t)(double , double );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DrawMemBase::signalChangeSelectFild)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (DrawMemBase::*_t)(long , Qt::MouseButton );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DrawMemBase::signalPressMouse)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (DrawMemBase::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DrawMemBase::signalResetSelectFild)) {
                *result = 5;
                return;
            }
        }
        {
            typedef void (DrawMemBase::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DrawMemBase::signalReleaseMouseMid)) {
                *result = 6;
                return;
            }
        }
    }
}

const QMetaObject DrawMemBase::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_DrawMemBase.data,
      qt_meta_data_DrawMemBase,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *DrawMemBase::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DrawMemBase::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_DrawMemBase.stringdata0))
        return static_cast<void*>(const_cast< DrawMemBase*>(this));
    return QWidget::qt_metacast(_clname);
}

int DrawMemBase::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void DrawMemBase::signalRealValue(double _t1, double _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void DrawMemBase::signalResetMarkFild()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void DrawMemBase::signalChangeMarkFild(int _t1, double _t2, double _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void DrawMemBase::signalChangeSelectFild(double _t1, double _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void DrawMemBase::signalPressMouse(long _t1, Qt::MouseButton _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void DrawMemBase::signalResetSelectFild()
{
    QMetaObject::activate(this, &staticMetaObject, 5, Q_NULLPTR);
}

// SIGNAL 6
void DrawMemBase::signalReleaseMouseMid()
{
    QMetaObject::activate(this, &staticMetaObject, 6, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
