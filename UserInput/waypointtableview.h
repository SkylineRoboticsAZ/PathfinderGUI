#ifndef WAYPOINTTABLE_H
#define WAYPOINTTABLE_H

#include <QTableView>

namespace WaypointTable
{

class WaypointTableView : public QTableView
{
    Q_OBJECT
public:
    WaypointTableView(QWidget *parent = nullptr);


};

}

#endif // WAYPOINTTABLE_H
