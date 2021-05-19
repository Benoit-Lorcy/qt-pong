/****************************************************************************
** Meta object code from reading C++ file 'configWindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "configWindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'configWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ConfigWindow_t {
    QByteArrayData data[15];
    char stringdata0[151];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ConfigWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ConfigWindow_t qt_meta_stringdata_ConfigWindow = {
    {
QT_MOC_LITERAL(0, 0, 12), // "ConfigWindow"
QT_MOC_LITERAL(1, 13, 12), // "ballSettings"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 5), // "ballw"
QT_MOC_LITERAL(4, 33, 5), // "ballh"
QT_MOC_LITERAL(5, 39, 9), // "baseSpeed"
QT_MOC_LITERAL(6, 49, 14), // "incrementSpeed"
QT_MOC_LITERAL(7, 64, 15), // "paddlesSettings"
QT_MOC_LITERAL(8, 80, 7), // "paddlew"
QT_MOC_LITERAL(9, 88, 7), // "paddleh"
QT_MOC_LITERAL(10, 96, 8), // "distance"
QT_MOC_LITERAL(11, 105, 7), // "vitesse"
QT_MOC_LITERAL(12, 113, 17), // "controlesSettings"
QT_MOC_LITERAL(13, 131, 8), // "textSize"
QT_MOC_LITERAL(14, 140, 10) // "scoreToWin"

    },
    "ConfigWindow\0ballSettings\0\0ballw\0ballh\0"
    "baseSpeed\0incrementSpeed\0paddlesSettings\0"
    "paddlew\0paddleh\0distance\0vitesse\0"
    "controlesSettings\0textSize\0scoreToWin"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ConfigWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    4,   29,    2, 0x06 /* Public */,
       7,    4,   38,    2, 0x06 /* Public */,
      12,    2,   47,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QReal, QMetaType::QReal, QMetaType::QReal, QMetaType::QReal,    3,    4,    5,    6,
    QMetaType::Void, QMetaType::QReal, QMetaType::QReal, QMetaType::QReal, QMetaType::QReal,    8,    9,   10,   11,
    QMetaType::Void, QMetaType::QReal, QMetaType::QReal,   13,   14,

       0        // eod
};

void ConfigWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ConfigWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->ballSettings((*reinterpret_cast< qreal(*)>(_a[1])),(*reinterpret_cast< qreal(*)>(_a[2])),(*reinterpret_cast< qreal(*)>(_a[3])),(*reinterpret_cast< qreal(*)>(_a[4]))); break;
        case 1: _t->paddlesSettings((*reinterpret_cast< qreal(*)>(_a[1])),(*reinterpret_cast< qreal(*)>(_a[2])),(*reinterpret_cast< qreal(*)>(_a[3])),(*reinterpret_cast< qreal(*)>(_a[4]))); break;
        case 2: _t->controlesSettings((*reinterpret_cast< qreal(*)>(_a[1])),(*reinterpret_cast< qreal(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ConfigWindow::*)(qreal , qreal , qreal , qreal );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ConfigWindow::ballSettings)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ConfigWindow::*)(qreal , qreal , qreal , qreal );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ConfigWindow::paddlesSettings)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ConfigWindow::*)(qreal , qreal );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ConfigWindow::controlesSettings)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ConfigWindow::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_ConfigWindow.data,
    qt_meta_data_ConfigWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ConfigWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ConfigWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ConfigWindow.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int ConfigWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void ConfigWindow::ballSettings(qreal _t1, qreal _t2, qreal _t3, qreal _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ConfigWindow::paddlesSettings(qreal _t1, qreal _t2, qreal _t3, qreal _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ConfigWindow::controlesSettings(qreal _t1, qreal _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
