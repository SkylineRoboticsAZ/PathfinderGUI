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

    connect(&model_, &QAbstractItemModel::dataChanged, this, &WaypointTableWidget::dataChanged);
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
}

void WaypointTableWidget::removeAllRows()
{
    model_.removeRows(0, model_.rowCount());
}

void WaypointTableWidget::setXRange(double bottom, double top)
{
    delegate_.setXRange(bottom, top);

    for (int i = 0; i < model_.rowCount(); i++) {
        QModelIndex index = model_.index(i, 0);
        QString cellData = model_.data(index).toString();

        if (!cellData.isEmpty()) {
            //the parameter i is not used, but required
            QValidator::State result = delegate_.xValidator()->validate(cellData, i);

            const bool isInvalid = index.data(WaypointTableRoles::InvalidValue).toBool();
            const bool isAcceptable = result == QValidator::Acceptable;

            if (isInvalid && isAcceptable)
                model_.setData(index, false, WaypointTableRoles::InvalidValue);
            else if (!isInvalid && !isAcceptable)
                model_.setData(index, true, WaypointTableRoles::InvalidValue);
        }
    }
}

void WaypointTableWidget::setYRange(double bottom, double top)
{
    delegate_.setYRange(bottom, top);

    for (int i = 0; i < model_.rowCount(); i++) {
        QModelIndex index = model_.index(i, 1);
        QString cellData = model_.data(index).toString();

        if (!cellData.isEmpty()) {
            //the parameter i is not used, but required
            QValidator::State result = delegate_.yValidator()->validate(cellData, i);

            const bool isInvalid = index.data(WaypointTableRoles::InvalidValue).toBool();
            const bool isAcceptable = result == QValidator::Acceptable;

            if (isInvalid && isAcceptable)
                model_.setData(index, false, WaypointTableRoles::InvalidValue);
            else if (!isInvalid && !isAcceptable)
                model_.setData(index, true, WaypointTableRoles::InvalidValue);
        }
    }
}

QVector<WaypointTableWidget::DataPoint> WaypointTableWidget::getCurrentData() const
{
    QVector<DataPoint> dataPoints;

    for (int row = 0; row < model_.rowCount(); row++) {
        DataPoint point;

        point.x = model_.data(model_.index(row, 0)).toString();
        point.y = model_.data(model_.index(row, 1)).toString();
        point.angle = model_.data(model_.index(row, 2)).toString();

        dataPoints << point;
    }

    return dataPoints;
}

void WaypointTableWidget::dataChanged(const QModelIndex &topLeft,
                                      const QModelIndex &bottomRight,
                                      const QVector<int> &roles)
{
    Q_UNUSED(bottomRight);

    if (roles.contains(Qt::EditRole) &&
            topLeft.data(WaypointTableRoles::InvalidValue).toBool()) {
        model_.setData(topLeft, false, WaypointTableRoles::InvalidValue);
    } else if (roles.contains(WaypointTableRoles::InvalidValue)) {
        if (topLeft.data(WaypointTableRoles::InvalidValue).toBool()) {
            emit dataInvalidated();
            return;
        }
    }

    runValidDataCheck();
}

void WaypointTableWidget::runValidDataCheck()
{
    const int rowCount = model_.rowCount();

    if (rowCount < 1)
        return;

    for (int row = 0; row < rowCount; row++) {
        for (int column = 0; column < 2; column++) {
            QModelIndex index = model_.index(row, column);

            if (index.data(WaypointTableRoles::InvalidValue).toBool() ||
                    index.data(Qt::EditRole).toString().isEmpty())
                return;

        }
    }

    emit validDataAvailable(getCurrentData());
}
