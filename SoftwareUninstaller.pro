QT       += core gui
QT       += widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SoftwareUninstaller
TEMPLATE = app

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    uninstaller.cpp

HEADERS += \
    mainwindow.h \
    uninstaller.h
