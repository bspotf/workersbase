#-------------------------------------------------
#
# Project created by Vyacheaslav Fisyuk
#
#-------------------------------------------------

QT       += core gui sql testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WorkersBase
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
    src/main.cpp \
    src/forms/mainwindow.cpp \
    src/services/dbservice.cpp \
    src/services/salaryservice.cpp \
    src/services/log.cpp \
    src/forms/createworkerform.cpp

HEADERS += \
    src/forms/mainwindow.h \
    src/services/dbservice.h \
    src/services/salaryservice.h \
    src/helpers/datetimehelper.h \
    src/helpers/workerhelper.h \
    src/services/log.h \
    src/forms/createworkerform.h \
    searchhelper.h

FORMS += \
    src/forms/mainwindow.ui \
    src/forms/createworkerform.ui
