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
    struct DataPoint
    {
        QString x, y, angle;
    };

    explicit WaypointTableWidget(QWidget *parent = nullptr);

    /**
     * @brief appendRow Adds an empty row to the table
     */
    void appendRow();

    /**
     * @brief removeSelectedRow Removes the currently selected row from
     * the table
     */
    void removeSelectedRow();

    /**
     * @brief removeAllRows Empties the table
     */
    void removeAllRows();

    /**
     * @brief setXRange Sets the range for X values in the table
     * @param bottom The minimum value
     * @param top The maximum value
     */
    void setXRange(double bottom, double top);

    /**
     * @brief setYRange Sets the range for Y values in the table
     * @param bottom The minimum value
     * @param top The maximum value
     */
    void setYRange(double bottom, double top);

    /**
     * @brief setCurrentData Inserts data into the table widget (removing any
     * existing data) and updates color coding and validity.
     * @param data The data to insert
     */
    void setCurrentData(const QVector<DataPoint> &data);

    /**
     * @brief getCurrentData Reads all the data from the table (including blank
     * rows and invalid data)
     * @return The data from the table
     */
    QVector<DataPoint> getCurrentData() const;

    /**
     * @brief isDataValid Get the validity of the table
     *
     * A valid table has:
     * - at least one row
     * - no incomplete rows (empty rows are ignored)
     * - data that is entirely valid (within X, Y, Angle ranges)
     *
     * @return The validity of the table
     */
    bool isDataValid() const;

signals:
    /**
     * @brief validDataAvailable This signal is emitted whenever there is new,
     * validated data available in the table
     * @param data The data from the table
     */
    void validDataAvailable(QVector<DataPoint> data);

    /**
     * @brief dataInvalidated This signal is emitted whenever the table is
     * invalidated
     */
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
