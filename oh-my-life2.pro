######################################################################
# Automatically generated by qmake (2.01a) ?? 3? 1 23:30:30 2014
######################################################################

# run with "qmake -spec macx-g++" in mac

TEMPLATE = app
TARGET = 
DEPENDPATH += . include lib
INCLUDEPATH += . include

# Input
HEADERS += include/DBm.h include/Record.h include/RecordPocket.h include/sql.def include/omlMainWindow.h include/RecordWidget.h include/StatisWidget.h
SOURCES += QtMain.cpp \
           lib/DBm.cpp \
           lib/Record.cpp \
           lib/RecordPocket.cpp \
           lib/omlMainWindow.cpp \
           lib/RecordWidget.cpp \
           lib/StatisWidget.cpp

LIBS += -lsqlite3

RESOURCES += QtSource.qrc
CONFIG += qt

macx:ICON = ./images/face.icns
ICON = ./images/face.icns
