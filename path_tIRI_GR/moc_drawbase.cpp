/****************************************************************************
** Meta object code from reading C++ file 'drawbase.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../draw/drawbase.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'drawbase.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_DrawBase_t {
    QByteArrayData data[4];
    char stringdata0[38];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DrawBase_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DrawBase_t qt_meta_stringdata_DrawBase = {
    {
QT_MOC_LITERAL(0, 0, 8), // "DrawBase"
QT_MOC_LITERAL(1, 9, 15), // "signalRealValue"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 11) // "signalClear"

    },
    "DrawBase\0signalRealValue\0\0signalClear"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DrawBase[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   29,    2, 0x06 /* Public */,
       1,    4,   34,    2, 0x06 /* Public */,
       3,    1,   43,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Double, QMetaType::Double,    2,    2,
    QMetaType::Void, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Double,    2,    2,    2,    2,
    QMetaType::Void, QMetaType::Int,    2,

       0        // eod
};

void DrawBase::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        DrawBase *_t = static_cast<DrawBase *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalRealValue((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 1: _t->signalRealValue((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3])),(*reinterpret_cast< double(*)>(_a[4]))); break;
        case 2: _t->signalClear((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (DrawBase::*_t)(double , double );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DrawBase::signalRealValue)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (DrawBase::*_t)(double , double , double , double );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DrawBase::signalRealValue)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (DrawBase::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DrawBase::signalClear)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject DrawBase::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_DrawBase.data,
      qt_meta_data_DrawBase,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *DrawBase::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DrawBase::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_DrawBase.stringdata0))
        return static_cast<void*>(const_cast< DrawBase*>(this));
    return QWidget::qt_metacast(_clname);
}

int DrawBase::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void DrawBase::signalRealValue(double _t1, double _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void DrawBase::signalRealValue(double _t1, double _t2, double _t3, double _t4)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void DrawBase::signalClear(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
