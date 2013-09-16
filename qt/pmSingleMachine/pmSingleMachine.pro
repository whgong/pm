#-------------------------------------------------
#
# Project created by QtCreator 2013-07-11T15:55:23
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = pmSingleMachine
TEMPLATE = app


SOURCES += main.cpp\
        contentpage.cpp \
    userpassword.cpp \
    loginpage.cpp \
    userInfo.cpp \
    userdao.cpp \
    userpwdinfopage.cpp \
    updao.cpp

HEADERS  += contentpage.h \
    userpassword.h \
    loginpage.h \
    userinfo.h \
    userdao.h \
    userpwdinfopage.h \
    updao.h

FORMS    += contentpage.ui \
    loginpage.ui \
    userpwdinfopage.ui

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../Program_Files/sqlite3/lib/ -lsqlite3
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../Program_Files/sqlite3/lib/ -lsqlite3
else:unix: LIBS += -L$$PWD/../../../../Program_Files/sqlite3/lib/ -lsqlite3

INCLUDEPATH += $$PWD/../../../../Program_Files/sqlite3/include
DEPENDPATH += $$PWD/../../../../Program_Files/sqlite3/include
