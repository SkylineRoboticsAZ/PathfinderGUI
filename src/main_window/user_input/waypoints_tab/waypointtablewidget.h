#ifndef WAYPOINTTABLEWIDGET_H
#define WAYPOINTTABLEWIDGET_H

#include <QTableView>
#include <QStandardItemModel>
#include <Qt>
#include <QHeaderView>

#include "waypointtabledelegate.h"

class WaypointTableWidget : public QTableView
{
    Q_OBJECT
public:
    explicit WaypointTableWidget(QWidget *parent = nullptr);

    void appendRow();
    void removeSelectedRow();
    void removeAllRows();

    void setXRange(double bottom, double top);
    void setYRange(double bottom, double top);

signals:

private slots:
    void dataChanged(const QModelIndex &topLeft,
                     const QModelIndex &bottomRight,
                     const QVector<int> &roles);

private:
    QStandardItemModel model_;
    WaypointTableDelegate delegate_;

    QBrush normalBrush_, invalidBrush_;
};

#endif // WAYPOINTTABLEWIDGET_H
