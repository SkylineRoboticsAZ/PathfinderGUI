#include "waypointtablemodel.h"

WaypointTableModel::WaypointTableModel(QObject *parent) : QStandardItemModel(parent)
{

}

WaypointTableModel::WaypointTableModel(int rows, int columns, QObject *parent) :
    QStandardItemModel(rows, columns, parent)
{

}
