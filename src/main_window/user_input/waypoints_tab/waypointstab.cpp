#include "waypointstab.h"

WaypointsTab::WaypointsTab(QWidget *parent) : QWidget(parent)
{
    setFocusPolicy(Qt::ClickFocus);

    QGridLayout *mainLayout = new QGridLayout();

    //Add code for the table buttons
    addRowButton_ = new QPushButton(tr("Add Row"));
    removeRowButton_ = new QPushButton(tr("Remove Row"));
    clearButton_ = new QPushButton(tr("Clear Table"));

    mainLayout->addWidget(addRowButton_, 0, 0);
    mainLayout->addWidget(removeRowButton_, 0, 1);
    mainLayout->addWidget(clearButton_, 0, 2);
    mainLayout->addWidget(&waypointTable_, 1, 0, 1, 3);

    setLayout(mainLayout);

    connect(addRowButton_, &QPushButton::clicked, this, &WaypointsTab::addRowClicked);
    connect(removeRowButton_, &QPushButton::clicked, this, &WaypointsTab::removeRowClicked);
    connect(clearButton_, &QPushButton::clicked, this, &WaypointsTab::clearClicked);
}

void WaypointsTab::setXRange(double bottom, double top)
{
    waypointTable_.setXRange(bottom, top);
}

void WaypointsTab::setYRange(double bottom, double top)
{
    waypointTable_.setYRange(bottom, top);
}

void WaypointsTab::addRowClicked()
{
    waypointTable_.appendRow();
}

void WaypointsTab::removeRowClicked()
{
    waypointTable_.removeSelectedRow();
}

void WaypointsTab::clearClicked()
{
    //TO-DO Warn the user before clearing their entire table
    waypointTable_.removeAllRows();
}
