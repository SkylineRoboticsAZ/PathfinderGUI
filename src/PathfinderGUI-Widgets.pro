#-------------------------------------------------
#
# Project created by QtCreator 2018-11-25T12:46:57
#
#-------------------------------------------------

QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PathfinderGUI-Widgets
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

CONFIG += c++11

SOURCES += \
    main_window/graph_viewport/graphviewport.cpp \
    main_window/user_input/controls/tabbar.cpp \
    main_window/user_input/waypoints_tab/waypointtabledelegate.cpp \
    main_window/user_input/waypoints_tab/waypointtablemodel.cpp \
    main_window/user_input/waypoints_tab/waypointtableview.cpp \
    main_window/user_input/userinput.cpp \
    main_window/mainwindow.cpp \
    main_window/menubar.cpp \
    main.cpp \
    pathfinderapplication.cpp \
    main_window/user_input/paremeters_tab/parameterstab.cpp \
    main_window/user_input/paremeters_tab/controls/lineedit.cpp \
    main_window/user_input/waypoints_tab/waypointstab.cpp \
    main_window/user_input/waypoints_tab/waypointtablewidget.cpp

HEADERS += \
    main_window/graph_viewport/graphviewport.h \
    main_window/user_input/controls/tabbar.h \
    main_window/user_input/waypoints_tab/waypointtabledelegate.h \
    main_window/user_input/waypoints_tab/waypointtablemodel.h \
    main_window/user_input/waypoints_tab/waypointtableview.h \
    main_window/user_input/userinput.h \
    main_window/mainwindow.h \
    main_window/menubar.h \
    pathfinderapplication.h \
    main_window/user_input/paremeters_tab/parameterstab.h \
    main_window/user_input/paremeters_tab/controls/lineedit.h \
    main_window/user_input/waypoints_tab/waypointstab.h \
    main_window/user_input/waypoints_tab/waypointtablewidget.h \
    main_window/user_input/waypoints_tab/roles.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources/resources.qrc


DISTFILES +=
