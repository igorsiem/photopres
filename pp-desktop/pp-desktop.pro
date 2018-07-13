#-------------------------------------------------
#
# Project created by QtCreator 2018-07-03T21:18:26
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = pp-desktop
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp

HEADERS += \
        mainwindow.h \
    errorhandling.h

FORMS += \
        mainwindow.ui

CONFIG += mobility
MOBILITY = 


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../pp-core/release/ -lpp-core
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../pp-core/debug/ -lpp-core
else:unix: LIBS += -L$$OUT_PWD/../pp-core/ -lpp-core

INCLUDEPATH += $$PWD/../pp-core
INCLUDEPATH += $$PWD/../third-party

DEPENDPATH += $$PWD/../pp-core

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../pp-core/release/libpp-core.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../pp-core/debug/libpp-core.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../pp-core/release/pp-core.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../pp-core/debug/pp-core.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../pp-core/libpp-core.a
