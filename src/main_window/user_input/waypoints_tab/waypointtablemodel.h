#ifndef WAYPOINTTABLEMODEL_H
#define WAYPOINTTABLEMODEL_H

#include <QStandardItemModel>

class WaypointTableModel : public QStandardItemModel
{
    Q_OBJECT
public:
    WaypointTableModel(QObject *parent = nullptr);
    WaypointTableModel(int rows, int columns, QObject *parent = nullptr);
};

#endif // WAYPOINTTABLEMODEL_H
