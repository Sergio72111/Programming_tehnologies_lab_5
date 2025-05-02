QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    consolelogger.cpp \
    devicefactory.cpp \
    devicemanager.cpp \
    drill.cpp \
    drillfactory.cpp \
    electricdevice.cpp \
    main.cpp \
    mainwindow.cpp \
    refrigerator.cpp \
    refrigeratorfactory.cpp

HEADERS += \
    consolelogger.h \
    devicefactory.h \
    devicemanager.h \
    drill.h \
    drillfactory.h \
    electricdevice.h \
    ilogger.h \
    mainwindow.h \
    refrigerator.h \
    refrigeratorfactory.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
