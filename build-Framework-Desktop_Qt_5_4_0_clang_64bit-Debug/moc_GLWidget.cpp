/****************************************************************************
** Meta object code from reading C++ file 'GLWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ScanlineFill/GLWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GLWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_GLWidget_t {
    QByteArrayData data[29];
    char stringdata[313];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GLWidget_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GLWidget_t qt_meta_stringdata_GLWidget = {
    {
QT_MOC_LITERAL(0, 0, 8), // "GLWidget"
QT_MOC_LITERAL(1, 9, 10), // "mouseMoved"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 1), // "x"
QT_MOC_LITERAL(4, 23, 1), // "y"
QT_MOC_LITERAL(5, 25, 17), // "togglePrintDialog"
QT_MOC_LITERAL(6, 43, 14), // "drawDialogLine"
QT_MOC_LITERAL(7, 58, 16), // "drawDialogCircle"
QT_MOC_LITERAL(8, 75, 16), // "updateDialogLine"
QT_MOC_LITERAL(9, 92, 2), // "x1"
QT_MOC_LITERAL(10, 95, 2), // "y1"
QT_MOC_LITERAL(11, 98, 2), // "x2"
QT_MOC_LITERAL(12, 101, 2), // "y2"
QT_MOC_LITERAL(13, 104, 18), // "updateDialogCircle"
QT_MOC_LITERAL(14, 123, 2), // "rX"
QT_MOC_LITERAL(15, 126, 2), // "rY"
QT_MOC_LITERAL(16, 129, 13), // "drawMouseLine"
QT_MOC_LITERAL(17, 143, 17), // "drawMousePolyline"
QT_MOC_LITERAL(18, 161, 16), // "drawMousePolygon"
QT_MOC_LITERAL(19, 178, 16), // "drawScanFillTest"
QT_MOC_LITERAL(20, 195, 17), // "drawScanFillTest2"
QT_MOC_LITERAL(21, 213, 17), // "drawScanFillTest3"
QT_MOC_LITERAL(22, 231, 11), // "clearWindow"
QT_MOC_LITERAL(23, 243, 11), // "chooseColor"
QT_MOC_LITERAL(24, 255, 11), // "drawFanTest"
QT_MOC_LITERAL(25, 267, 11), // "drawBowTest"
QT_MOC_LITERAL(26, 279, 13), // "drawHouseTest"
QT_MOC_LITERAL(27, 293, 8), // "drawTest"
QT_MOC_LITERAL(28, 302, 10) // "drawCircle"

    },
    "GLWidget\0mouseMoved\0\0x\0y\0togglePrintDialog\0"
    "drawDialogLine\0drawDialogCircle\0"
    "updateDialogLine\0x1\0y1\0x2\0y2\0"
    "updateDialogCircle\0rX\0rY\0drawMouseLine\0"
    "drawMousePolyline\0drawMousePolygon\0"
    "drawScanFillTest\0drawScanFillTest2\0"
    "drawScanFillTest3\0clearWindow\0chooseColor\0"
    "drawFanTest\0drawBowTest\0drawHouseTest\0"
    "drawTest\0drawCircle"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GLWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      19,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,  109,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,  114,    2, 0x0a /* Public */,
       6,    0,  115,    2, 0x0a /* Public */,
       7,    0,  116,    2, 0x0a /* Public */,
       8,    4,  117,    2, 0x0a /* Public */,
      13,    4,  126,    2, 0x0a /* Public */,
      16,    0,  135,    2, 0x0a /* Public */,
      17,    0,  136,    2, 0x0a /* Public */,
      18,    0,  137,    2, 0x0a /* Public */,
      19,    0,  138,    2, 0x0a /* Public */,
      20,    0,  139,    2, 0x0a /* Public */,
      21,    0,  140,    2, 0x0a /* Public */,
      22,    0,  141,    2, 0x0a /* Public */,
      23,    0,  142,    2, 0x0a /* Public */,
      24,    0,  143,    2, 0x0a /* Public */,
      25,    0,  144,    2, 0x0a /* Public */,
      26,    0,  145,    2, 0x0a /* Public */,
      27,    0,  146,    2, 0x0a /* Public */,
      28,    0,  147,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    3,    4,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,    9,   10,   11,   12,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,    9,   10,   14,   15,
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
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void GLWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        GLWidget *_t = static_cast<GLWidget *>(_o);
        switch (_id) {
        case 0: _t->mouseMoved((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->togglePrintDialog(); break;
        case 2: _t->drawDialogLine(); break;
        case 3: _t->drawDialogCircle(); break;
        case 4: _t->updateDialogLine((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 5: _t->updateDialogCircle((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 6: _t->drawMouseLine(); break;
        case 7: _t->drawMousePolyline(); break;
        case 8: _t->drawMousePolygon(); break;
        case 9: _t->drawScanFillTest(); break;
        case 10: _t->drawScanFillTest2(); break;
        case 11: _t->drawScanFillTest3(); break;
        case 12: _t->clearWindow(); break;
        case 13: _t->chooseColor(); break;
        case 14: _t->drawFanTest(); break;
        case 15: _t->drawBowTest(); break;
        case 16: _t->drawHouseTest(); break;
        case 17: _t->drawTest(); break;
        case 18: _t->drawCircle(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (GLWidget::*_t)(int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GLWidget::mouseMoved)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject GLWidget::staticMetaObject = {
    { &QGLWidget::staticMetaObject, qt_meta_stringdata_GLWidget.data,
      qt_meta_data_GLWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *GLWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GLWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_GLWidget.stringdata))
        return static_cast<void*>(const_cast< GLWidget*>(this));
    return QGLWidget::qt_metacast(_clname);
}

int GLWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGLWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 19)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 19;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 19)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 19;
    }
    return _id;
}

// SIGNAL 0
void GLWidget::mouseMoved(int _t1, int _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
