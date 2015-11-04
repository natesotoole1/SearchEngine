TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += C++11

SOURCES += main.cpp \
    indexinterface.cpp \
    term.cpp \
    termbucket.cpp \
    porter2_stemmer.cpp \
    pageinfo.cpp \
    avltreeindex.cpp \
    avltreeinterface.cpp \
    docparser.cpp \
    indexhandler.cpp \
    queryprocessor.cpp \
    hashtableindex.cpp \
    hashtableinterface.cpp \
    interface.cpp \
    timer.cpp


include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    indexinterface.h \
    term.h \
    termbucket.h \
    porter2_stemmer.h \
    pageinfo.h \
    avltreeindex.h \
    avltreeinterface.h \
    docparser.h \
    indexhandler.h \
    queryprocessor.h \
    hashtableindex.h \
    hashtableinterface.h \
    interface.h \
    timer.h

