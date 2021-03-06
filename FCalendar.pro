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
    ttodo.cpp \
    eventmodel.cpp \
	eventdelegate.cpp\
	eventtableview.cpp \
    statusindicator.cpp \
    contextmenu.cpp
HEADERS += calendar.h \
    vcalparser.h \
    task.h \
    tevent.h \
    ttodo.h \
    eventmodel.h \
	eventdelegate.h \
	eventtableview.h \
    statusindicator.h \
    contextmenu.h
FORMS += 
QT += network

symbian { 
    #include(qts60main.pri)
    HEADERS += sym_iap_util.h
    INCLUDEPATH += $$APP_LAYER_SYSTEMINCLUDE
    TARGET.CAPABILITY = "NetworkServices ReadUserData WriteUserData"
    
    # TARGET.UID3 = 0xA000A648
    LIBS += -lesock -lconnmon -linsock # For IAP selection
}

RESOURCES += \
    app.qrc
