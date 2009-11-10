/****************************************************************************
** Meta object code from reading C++ file 'calendar.h'
**
** Created: Tue Nov 10 18:17:49 2009
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
      16,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x05,
      26,    9,    9,    9, 0x05,
      46,   42,    9,    9, 0x05,
      62,    9,    9,    9, 0x05,

 // slots: signature, parameters, type, tag, flags
      84,   73,    9,    9, 0x0a,
     135,  129,    9,    9, 0x0a,
     170,  164,    9,    9, 0x0a,
     205,  197,    9,    9, 0x0a,
     227,    9,    9,    9, 0x0a,
     242,    9,    9,    9, 0x0a,
     264,    9,    9,    9, 0x0a,
     281,    9,    9,    9, 0x0a,
     297,    9,    9,    9, 0x0a,
     313,  307,    9,    9, 0x0a,
     365,  354,    9,    9, 0x0a,
     406,  398,    9,    9, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Calendar[] = {
    "Calendar\0\0listPopulated()\0configChanged()\0"
    "row\0visibleRow(int)\0authLoop()\0"
    "reply,auth\0authenticate(QNetworkReply*,QAuthenticator*)\0"
    "reply\0populateList(QNetworkReply*)\0"
    "index\0showEventInfo(QModelIndex)\0"
    "row,col\0showTodoInfo(int,int)\0"
    "saveSettings()\0viewUpdatedCalendar()\0"
    "configSettings()\0configNetwork()\0"
    "getData()\0error\0"
    "outputError(QNetworkReply::NetworkError)\0"
    "done,total\0transmissionStats(qint64,qint64)\0"
    "message\0outputError(QString)\0"
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
        case 3: authLoop(); break;
        case 4: authenticate((*reinterpret_cast< QNetworkReply*(*)>(_a[1])),(*reinterpret_cast< QAuthenticator*(*)>(_a[2]))); break;
        case 5: populateList((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 6: showEventInfo((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 7: showTodoInfo((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 8: saveSettings(); break;
        case 9: viewUpdatedCalendar(); break;
        case 10: configSettings(); break;
        case 11: configNetwork(); break;
        case 12: getData(); break;
        case 13: outputError((*reinterpret_cast< QNetworkReply::NetworkError(*)>(_a[1]))); break;
        case 14: transmissionStats((*reinterpret_cast< const qint64(*)>(_a[1])),(*reinterpret_cast< const qint64(*)>(_a[2]))); break;
        case 15: outputError((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 16;
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

// SIGNAL 3
void Calendar::authLoop()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}
QT_END_MOC_NAMESPACE
