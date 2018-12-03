#include "waypointtablemodel.h"

namespace WaypointTable
{

WaypointTableModel::WaypointTableModel(QObject *parent) : QStandardItemModel(parent)
{

}

WaypointTableModel::WaypointTableModel(int rows, int columns, QObject *parent) :
    QStandardItemModel(rows, columns, parent)
{

}

}
