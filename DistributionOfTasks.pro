#-------------------------------------------------
#
# Project created by QtCreator 2015-12-23T15:52:25
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DistributionOfTasks
TEMPLATE = app

CONFIG += c++14

SOURCES += main.cpp\
        taskmainwindow.cpp \
        dbsettingsdialog.cpp \
        taskform.cpp \
        multiplefilterproxymodel.cpp \
        userform.cpp \
        departmentform.cpp \
    usereditdialog.cpp \
    createtaskdialog.cpp \
    changecompletiondialog.cpp

HEADERS  += taskmainwindow.h \
        dbsettingsdialog.h \
        taskform.h \
        multiplefilterproxymodel.h \
        userform.h \
        departmentform.h \
        usereditdialog.h \
        createtaskdialog.h \
    changecompletiondialog.h

FORMS    += taskmainwindow.ui \
        dbsettingsdialog.ui \
        taskform.ui \
        userform.ui \
        departmentform.ui \
        usereditdialog.ui \
        createtaskdialog.ui \
    changecompletiondialog.ui
