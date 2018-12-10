#include "userinput.h"

UserInput::UserInput(QWidget *parent) : QTabWidget(parent)
{
    QPalette palette = QPalette();
    palette.setColor(QPalette::Window, QColor(QStringLiteral("#434343")));
    setAutoFillBackground(true);
    setPalette(palette);

    setFocusPolicy(Qt::ClickFocus);

    TabBar *tabBar = new TabBar();
    setTabBar(tabBar);
    tabBar->setGeometry(0, 0, width(), 50);

    waypointsTab_.setContentsMargins(5, 5, 5, 5);

    addTab(&parametersTab_, tr("Parameters"));
    addTab(&waypointsTab_, tr("Waypoints"));

    connect(&parametersTab_, &ParametersTab::fieldLengthChanged, this,
            [=](QString length){ waypointsTab_.setXRange(0, length.toDouble()); });
    connect(&parametersTab_, &ParametersTab::fieldWidthChanged, this,
            [=](QString width){ waypointsTab_.setYRange(0, width.toDouble()); });
}
