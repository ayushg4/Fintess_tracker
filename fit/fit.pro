QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

SOURCES += \
    fitnesstracker.cpp \
    main.cpp \
    profilemanager.cpp

HEADERS += \
    fitnesstracker.h \
    profilemanager.h \
    user.h \
    workout.h

FORMS +=

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
