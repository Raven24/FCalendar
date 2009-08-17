# -------------------------------------------------
# Project created by QtCreator 2009-08-06T13:14:21
# -------------------------------------------------

TARGET = FCalendar
TEMPLATE = app
SOURCES += main.cpp \
    calendar.cpp \
    vcalparser.cpp \
    task.cpp \
    tevent.cpp \
    ttodo.cpp
HEADERS += calendar.h \
    vcalparser.h \
    task.h \
    tevent.h \
    ttodo.h
FORMS += 
QT += network

symbian {
	include(qts60main.pri)
    HEADERS +=  sym_iap_util.h
    INCLUDEPATH += $$APP_LAYER_SYSTEMINCLUDE
    TARGET.CAPABILITY="NetworkServices"
    #TARGET.UID3 = 0xA000A648
    LIBS+=-lesock -lconnmon   # For IAP selection
}