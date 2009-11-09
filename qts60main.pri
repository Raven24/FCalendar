QT_SOURCE_TREE = $$QMAKE_INCDIR_QT/..
DEPENDPATH += $$QT_SOURCE_TREE/src/s60main

HEADERS += \
        qts60mainapplication.h \
        qts60mainappui.h \
        qts60maindocument.h

SOURCES += \
        qts60mainapplication.cpp \
        qts60mainappui.cpp \
        qts60main.cpp \
        qts60maindocument.cpp \
        qts60main_mcrt0.cpp

LIBS -= qtmain
QMAKE_LIBS -= qtmain

MMP_RULES += \
        "SOURCEPATH $$QT_SOURCE_TREE/src/s60main" \
        "START RESOURCE s60main.rss" \
        "HEADER" \
        "TARGETPATH /resource/apps" \
        "END"

