QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_basic.cpp

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../pp-core/release/ -lpp-core
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../pp-core/debug/ -lpp-core
else:unix: LIBS += -L$$OUT_PWD/../pp-core/ -lpp-core

INCLUDEPATH += $$PWD/../pp-core
DEPENDPATH += $$PWD/../pp-core

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../pp-core/release/libpp-core.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../pp-core/debug/libpp-core.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../pp-core/release/pp-core.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../pp-core/debug/pp-core.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../pp-core/libpp-core.a
