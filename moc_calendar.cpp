/****************************************************************************
** Meta object code from reading C++ file 'calendar.h'
**
** Created: Tue Sep 29 23:18:28 2009
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "calendar.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'calendar.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Calendar[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x05,
      32,   26,    9,    9, 0x05,

 // slots: signature, parameters, type, tag, flags
      70,   57,    9,    9, 0x0a,
     107,   99,    9,    9, 0x0a,
     130,   99,    9,    9, 0x0a,
     152,    9,    9,    9, 0x0a,
     174,    9,    9,    9, 0x0a,
     189,    9,    9,    9, 0x0a,
     209,    9,    9,    9, 0x0a,
     226,    9,    9,    9, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Calendar[] = {
    "Calendar\0\0listPopulated()\0which\0"
    "settingsChanged(QString)\0networkReply\0"
    "populateList(QNetworkReply*)\0row,col\0"
    "showEventInfo(int,int)\0showTodoInfo(int,int)\0"
    "scrollToNearestItem()\0saveSettings()\0"
    "abortSaveSettings()\0configSettings()\0"
    "configNetwork()\0"
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
        case 1: settingsChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: populateList((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 3: showEventInfo((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: showTodoInfo((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 5: scrollToNearestItem(); break;
        case 6: saveSettings(); break;
        case 7: abortSaveSettings(); break;
        case 8: configSettings(); break;
        case 9: configNetwork(); break;
        default: ;
        }
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void Calendar::listPopulated()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void Calendar::settingsChanged(const QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
