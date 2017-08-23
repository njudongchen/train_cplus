TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    textquery.cpp \
    drive_query.cpp \
    query_Interface.cpp \
    querybase.cpp

HEADERS += \
    textquery.h \
    drive_query.h \
    query_Interface.h \
    querybase.h

