#ifndef USERINPUT_H
#define USERINPUT_H

#include <QWidget>
#include <QPalette>
#include <QTabWidget>

#include "controls/tabbar.h"
#include "paremeters_tab/parameterstab.h"
#include "waypoints_tab/waypointstab.h"

class UserInput : public QTabWidget
{
    Q_OBJECT
public:
    explicit UserInput(QWidget *parent = nullptr);

private:
    ParametersTab parametersTab_;
    WaypointsTab waypointsTab_;
};

#endif // USERINPUT_H
