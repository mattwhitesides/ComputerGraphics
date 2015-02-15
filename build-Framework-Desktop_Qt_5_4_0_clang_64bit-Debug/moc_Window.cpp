/****************************************************************************
** Meta object code from reading C++ file 'Window.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Bresenham Line Drawing Algorithm/Window.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Window.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Window_t {
    QByteArrayData data[13];
    char stringdata[218];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Window_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Window_t qt_meta_stringdata_Window = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Window"
QT_MOC_LITERAL(1, 7, 15), // "printCallFromMW"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 17), // "chooseColorFromMW"
QT_MOC_LITERAL(4, 42, 20), // "drawDialogLineFromMW"
QT_MOC_LITERAL(5, 63, 19), // "drawMouseLineFromMW"
QT_MOC_LITERAL(6, 83, 23), // "drawMousePolyLineFromMW"
QT_MOC_LITERAL(7, 107, 22), // "drawMousePolygonFromMW"
QT_MOC_LITERAL(8, 130, 17), // "drawFanTestFromMW"
QT_MOC_LITERAL(9, 148, 19), // "drawHouseTestFromMW"
QT_MOC_LITERAL(10, 168, 17), // "drawBowTestFromMW"
QT_MOC_LITERAL(11, 186, 14), // "drawTestFromMW"
QT_MOC_LITERAL(12, 201, 16) // "drawCircleFromMW"

    },
    "Window\0printCallFromMW\0\0chooseColorFromMW\0"
    "drawDialogLineFromMW\0drawMouseLineFromMW\0"
    "drawMousePolyLineFromMW\0drawMousePolygonFromMW\0"
    "drawFanTestFromMW\0drawHouseTestFromMW\0"
    "drawBowTestFromMW\0drawTestFromMW\0"
    "drawCircleFromMW"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Window[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      11,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x06 /* Public */,
       3,    0,   70,    2, 0x06 /* Public */,
       4,    0,   71,    2, 0x06 /* Public */,
       5,    0,   72,    2, 0x06 /* Public */,
       6,    0,   73,    2, 0x06 /* Public */,
       7,    0,   74,    2, 0x06 /* Public */,
       8,    0,   75,    2, 0x06 /* Public */,
       9,    0,   76,    2, 0x06 /* Public */,
      10,    0,   77,    2, 0x06 /* Public */,
      11,    0,   78,    2, 0x06 /* Public */,
      12,    0,   79,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Window::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Window *_t = static_cast<Window *>(_o);
        switch (_id) {
        case 0: _t->printCallFromMW(); break;
        case 1: _t->chooseColorFromMW(); break;
        case 2: _t->drawDialogLineFromMW(); break;
        case 3: _t->drawMouseLineFromMW(); break;
        case 4: _t->drawMousePolyLineFromMW(); break;
        case 5: _t->drawMousePolygonFromMW(); break;
        case 6: _t->drawFanTestFromMW(); break;
        case 7: _t->drawHouseTestFromMW(); break;
        case 8: _t->drawBowTestFromMW(); break;
        case 9: _t->drawTestFromMW(); break;
        case 10: _t->drawCircleFromMW(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Window::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Window::printCallFromMW)) {
                *result = 0;
            }
        }
        {
            typedef void (Window::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Window::chooseColorFromMW)) {
                *result = 1;
            }
        }
        {
            typedef void (Window::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Window::drawDialogLineFromMW)) {
                *result = 2;
            }
        }
        {
            typedef void (Window::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Window::drawMouseLineFromMW)) {
                *result = 3;
            }
        }
        {
            typedef void (Window::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Window::drawMousePolyLineFromMW)) {
                *result = 4;
            }
        }
        {
            typedef void (Window::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Window::drawMousePolygonFromMW)) {
                *result = 5;
            }
        }
        {
            typedef void (Window::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Window::drawFanTestFromMW)) {
                *result = 6;
            }
        }
        {
            typedef void (Window::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Window::drawHouseTestFromMW)) {
                *result = 7;
            }
        }
        {
            typedef void (Window::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Window::drawBowTestFromMW)) {
                *result = 8;
            }
        }
        {
            typedef void (Window::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Window::drawTestFromMW)) {
                *result = 9;
            }
        }
        {
            typedef void (Window::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Window::drawCircleFromMW)) {
                *result = 10;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject Window::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Window.data,
      qt_meta_data_Window,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Window::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Window::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Window.stringdata))
        return static_cast<void*>(const_cast< Window*>(this));
    return QWidget::qt_metacast(_clname);
}

int Window::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void Window::printCallFromMW()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void Window::chooseColorFromMW()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void Window::drawDialogLineFromMW()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}

// SIGNAL 3
void Window::drawMouseLineFromMW()
{
    QMetaObject::activate(this, &staticMetaObject, 3, Q_NULLPTR);
}

// SIGNAL 4
void Window::drawMousePolyLineFromMW()
{
    QMetaObject::activate(this, &staticMetaObject, 4, Q_NULLPTR);
}

// SIGNAL 5
void Window::drawMousePolygonFromMW()
{
    QMetaObject::activate(this, &staticMetaObject, 5, Q_NULLPTR);
}

// SIGNAL 6
void Window::drawFanTestFromMW()
{
    QMetaObject::activate(this, &staticMetaObject, 6, Q_NULLPTR);
}

// SIGNAL 7
void Window::drawHouseTestFromMW()
{
    QMetaObject::activate(this, &staticMetaObject, 7, Q_NULLPTR);
}

// SIGNAL 8
void Window::drawBowTestFromMW()
{
    QMetaObject::activate(this, &staticMetaObject, 8, Q_NULLPTR);
}

// SIGNAL 9
void Window::drawTestFromMW()
{
    QMetaObject::activate(this, &staticMetaObject, 9, Q_NULLPTR);
}

// SIGNAL 10
void Window::drawCircleFromMW()
{
    QMetaObject::activate(this, &staticMetaObject, 10, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
