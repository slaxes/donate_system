#-------------------------------------------------
#
# Project created by QtCreator 2017-07-25T21:36:30
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = donate_system
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    clos.cpp \
    _add_dep.cpp \
    _add_class.cpp \
    _add_student.cpp \
    grade_rank.cpp \
    seekdep.cpp \
    seekclas.cpp \
    seekstu.cpp \
    changedep.cpp \
    changeclas.cpp \
    changestu.cpp \
    dev_info.cpp \
    oper_help.cpp

HEADERS += \
        mainwindow.h \
    clos.h \
    _add_dep.h \
    _add_class.h \
    _add_student.h \
    dev_info.h \
    oper_help.h \
    grade_rank.h \
    seekdep.h \
    seekclas.h \
    seekstu.h \
    changedep.h \
    changeclas.h \
    changestu.h

FORMS += \
        mainwindow.ui \
    clos.ui \
    _add_dep.ui \
    _add_class.ui \
    _add_student.ui \
    dev_info.ui \
    oper_help.ui \
    grade_rank.ui \
    seekdep.ui \
    seekclas.ui \
    seekstu.ui \
    changedep.ui \
    changeclas.ui \
    changestu.ui

DISTFILES += \
    icon1.ico \
    app.rc

RC_FILE += app.rc
