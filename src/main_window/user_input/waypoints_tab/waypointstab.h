#ifndef WAYPOINTSTAB_H
#define WAYPOINTSTAB_H

#include <QWidget>
#include <QPushButton>
#include <QTableView>
#include <QGridLayout>

#include "waypointtablewidget.h"

class WaypointsTab : public QWidget
{
    Q_OBJECT
public:
    explicit WaypointsTab(QWidget *parent = nullptr);

    void setXRange(double bottom, double top);
    void setYRange(double bottom, double top);

signals:

private slots:
    void addRowClicked();
    void removeRowClicked();
    void clearClicked();

private:
    QPushButton *addRowButton_,
                *removeRowButton_,
                *clearButton_;

    WaypointTableWidget waypointTable_;
};

#endif // WAYPOINTSTAB_H
