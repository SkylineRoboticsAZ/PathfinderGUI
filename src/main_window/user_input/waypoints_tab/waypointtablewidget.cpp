#include "waypointtablewidget.h"

WaypointTableWidget::WaypointTableWidget(QWidget *parent) : QTableView(parent),
    model_(10, 3), delegate_()
{
    setModel(&model_);
    setItemDelegate(&delegate_);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setSelectionMode(QAbstractItemView::SingleSelection);

    model_.setHeaderData(0, Qt::Horizontal, tr("X"));
    model_.setHeaderData(1, Qt::Horizontal, tr("Y"));
    model_.setHeaderData(2, Qt::Horizontal, tr("θ"));

    QHeaderView *horizontal = horizontalHeader();
    horizontal->setSectionResizeMode(QHeaderView::Stretch);
    horizontal->setSectionsMovable(false);
    horizontal->setSectionsClickable(false);

    QHeaderView *vertical = verticalHeader();
    vertical->setSectionResizeMode(QHeaderView::Fixed);
    vertical->setSectionsMovable(false);
    vertical->setSectionsClickable(false);

    connect(this, &WaypointTableWidget::validDataAvailable,
            this, [=](QVector<DataPoint> data)
    {
        for (DataPoint point : data) {
            qDebug() << "X: " << point.x;
            qDebug() << "Y: " << point.y;
            qDebug() << "Angle: " << point.angle;
        }
    });
    connect(this, &WaypointTableWidget::dataInvalidated, this, [=]()
    {
        qDebug() << "Data Invalidated!";
    });
}

void WaypointTableWidget::appendRow()
{
    model_.appendRow(new QStandardItem());
}

void WaypointTableWidget::removeSelectedRow()
{
    QItemSelectionModel *selection = selectionModel();
    if (selection->hasSelection())
        model_.removeRow(selection->selectedRows().first().row());

    runValidDataCheck();
}

void WaypointTableWidget::removeAllRows()
{
    model_.removeRows(0, model_.rowCount());

    setDataValiditity(false);
}

void WaypointTableWidget::setXRange(double bottom, double top)
{
    setRangeHelper(true, bottom, top);
}

void WaypointTableWidget::setYRange(double bottom, double top)
{
    setRangeHelper(false, bottom, top);
}

void WaypointTableWidget::setCurrentData(const QVector<WaypointTableWidget::DataPoint> &data)
{

}

QVector<WaypointTableWidget::DataPoint> WaypointTableWidget::getCurrentData() const
{
    const int rowCount = model_.rowCount();

    QVector<DataPoint> dataPoints;
    dataPoints.reserve(rowCount);

    for (int row = 0; row < rowCount; row++) {
        DataPoint point;

        point.x = model_.data(model_.index(row, 0)).toString();
        point.y = model_.data(model_.index(row, 1)).toString();
        point.angle = model_.data(model_.index(row, 2)).toString();

        dataPoints << point;
    }

    return dataPoints;
}

bool WaypointTableWidget::isDataValid() const
{
    return isDataValid_;
}

void WaypointTableWidget::dataChanged(const QModelIndex &topLeft,
                                      const QModelIndex &bottomRight,
                                      const QVector<int> &roles)
{    
    Q_UNUSED(bottomRight);

    if (roles.contains(Qt::EditRole)) {
        const bool isInvalid = topLeft.data(WaypointTableRoles::InvalidValue).toBool();

        if (isInvalid)
            model_.setData(topLeft, false, WaypointTableRoles::InvalidValue);

        // There is no way a user can invalidate the table by editing
        // due to input regulations set in the delegate
        // Therefore, we must only check if the table is valid after edits
        runValidDataCheck();
    }
}

void WaypointTableWidget::setDataValiditity(bool isValid)
{
    if (isDataValid_ != isValid) {
        isDataValid_ = isValid;

        if (!isDataValid_)
            emit dataInvalidated();
    }

    if (isDataValid_)
        emit validDataAvailable(getCurrentData());
}

void WaypointTableWidget::setRangeHelper(bool isXRange, double bottom, double top)
{
    if (isXRange)
        delegate_.setXRange(bottom, top);
    else
        delegate_.setYRange(bottom, top);

    bool wasDataInvalidated = false;
    bool wasDataValidated = false;

    for (int i = 0; i < model_.rowCount(); i++) {
        QModelIndex index = model_.index(i, (isXRange ? 0 : 1));
        QString cellData = model_.data(index).toString();

        if (!cellData.isEmpty()) {
            //the parameter i is not used, but required
            QValidator::State result = isXRange ? delegate_.xValidator()->validate(cellData, i) :
                                                  delegate_.yValidator()->validate(cellData, i);

            const bool isInvalid = index.data(WaypointTableRoles::InvalidValue).toBool();
            const bool isAcceptable = result == QValidator::Acceptable;

            if (isInvalid && isAcceptable) {
                model_.setData(index, false, WaypointTableRoles::InvalidValue);
                wasDataValidated = true;
            } else if (!isInvalid && !isAcceptable) {
                model_.setData(index, true, WaypointTableRoles::InvalidValue);
                wasDataInvalidated = true;
            }
        }
    }

    if (wasDataInvalidated)
        setDataValiditity(false);
    else if (wasDataValidated)
        // If no data was invalidated and some data was validated
        // we must check if the table is now valid
        runValidDataCheck();
}

void WaypointTableWidget::runValidDataCheck()
{
    bool isDataValid = false;

    const int rowCount = model_.rowCount();

    if (rowCount >= 1) {
        for (int row = 0; row < rowCount; row++) {

            bool isFirstColumnEmpty = false;

            for (int column = 0; column < 3; column++) {
                QModelIndex index = model_.index(row, column);

                if (column < 3) {
                    const bool isInvalid = index.data(WaypointTableRoles::InvalidValue).toBool();

                    if (isInvalid)
                        goto end;
                }

                // Make sure all the columns in the row are in the same state
                // either all filled or all empty - we ignore empty rows
                const bool isCurrentColumnEmpty = index.data().toString().isEmpty();

                if (column == 0)
                    isFirstColumnEmpty = isCurrentColumnEmpty;
                else if (isFirstColumnEmpty != isCurrentColumnEmpty)
                    goto end;
            }
        }

        isDataValid = true;
    }

    end:
    setDataValiditity(isDataValid);
}
