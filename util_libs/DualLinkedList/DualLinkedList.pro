TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    DualLinkedListTester.c \
    DualLinkedList.c #\    ../BaseType/Object_WH_G.c

HEADERS += \
    Iterator_WH_G.h \
    List_WH_G.h \ #\    ../BaseType/Object_WH_G.h
    DualLinkedList.h


unix|win32: LIBS += -L$$PWD/../../mclib/lib/ -llibObject_WH_G

INCLUDEPATH += $$PWD/../../mclib/include
DEPENDPATH += $$PWD/../../mclib/include

win32: PRE_TARGETDEPS += $$PWD/../../mclib/lib/libObject_WH_G.lib
else:unix: PRE_TARGETDEPS += $$PWD/../../mclib/lib/liblibObject_WH_G.a
