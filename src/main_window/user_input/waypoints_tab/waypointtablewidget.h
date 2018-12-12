#ifndef WAYPOINTTABLEWIDGET_H
#define WAYPOINTTABLEWIDGET_H

#include <QTableView>
#include <QStandardItemModel>
#include <Qt>
#include <QHeaderView>
#include <QVector>

#include "waypointtabledelegate.h"
#include "roles.h"

class WaypointTableWidget : public QTableView
{
    Q_OBJECT
public:
    struct DataPoint {
        QString x, y, angle;
    };

    explicit WaypointTableWidget(QWidget *parent = nullptr);

    void appendRow();
    void removeSelectedRow();
    void removeAllRows();

    void setXRange(double bottom, double top);
    void setYRange(double bottom, double top);

    QVector<DataPoint> getCurrentData() const;
    bool isDataValid() const;

signals:
    void validDataAvailable(QVector<DataPoint> data);
    void dataInvalidated();

private slots:
    void dataChanged(const QModelIndex &topLeft,
                     const QModelIndex &bottomRight,
                     const QVector<int> &roles);

private:
    QStandardItemModel model_;
    WaypointTableDelegate delegate_;
    bool isDataValid_ = false;

    void setDataValiditity(bool isValid);
    void setRangeHelper(bool isXRange, double bottom, double top);
    void runValidDataCheck();
};

#endif // WAYPOINTTABLEWIDGET_H
