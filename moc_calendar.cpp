/****************************************************************************
** Meta object code from reading C++ file 'calendar.h'
**
** Created: Thu Aug 20 12:07:30 2009
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "calendar.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'calendar.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Calendar[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      23,   10,    9,    9, 0x0a,
      60,   52,    9,    9, 0x0a,
      83,   52,    9,    9, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Calendar[] = {
    "Calendar\0\0networkReply\0"
    "populateList(QNetworkReply*)\0row,col\0"
    "showEventInfo(int,int)\0showTodoInfo(int,int)\0"
};

const QMetaObject Calendar::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_Calendar,
      qt_meta_data_Calendar, 0 }
};

const QMetaObject *Calendar::metaObject() const
{
    return &staticMetaObject;
}

void *Calendar::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Calendar))
        return static_cast<void*>(const_cast< Calendar*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int Calendar::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: populateList((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 1: showEventInfo((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: showTodoInfo((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
