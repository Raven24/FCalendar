/****************************************************************************
** Meta object code from reading C++ file 'calendar.h'
**
** Created: Tue Oct 20 19:21:02 2009
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.2-tower)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "calendar.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'calendar.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.2-tower. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Calendar[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x05,
      26,    9,    9,    9, 0x05,
      46,   42,    9,    9, 0x05,

 // slots: signature, parameters, type, tag, flags
      75,   62,    9,    9, 0x0a,
     110,  104,    9,    9, 0x0a,
     145,  137,    9,    9, 0x0a,
     167,    9,    9,    9, 0x0a,
     182,    9,    9,    9, 0x0a,
     204,    9,    9,    9, 0x0a,
     221,    9,    9,    9, 0x0a,
     237,    9,    9,    9, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Calendar[] = {
    "Calendar\0\0listPopulated()\0configChanged()\0"
    "row\0visibleRow(int)\0networkReply\0"
    "populateList(QNetworkReply*)\0index\0"
    "showEventInfo(QModelIndex)\0row,col\0"
    "showTodoInfo(int,int)\0saveSettings()\0"
    "viewUpdatedCalendar()\0configSettings()\0"
    "configNetwork()\0getData()\0"
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
        case 0: listPopulated(); break;
        case 1: configChanged(); break;
        case 2: visibleRow((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: populateList((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 4: showEventInfo((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 5: showTodoInfo((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 6: saveSettings(); break;
        case 7: viewUpdatedCalendar(); break;
        case 8: configSettings(); break;
        case 9: configNetwork(); break;
        case 10: getData(); break;
        default: ;
        }
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void Calendar::listPopulated()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void Calendar::configChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void Calendar::visibleRow(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
