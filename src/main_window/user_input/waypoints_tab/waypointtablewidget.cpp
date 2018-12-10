#include "waypointtablewidget.h"

WaypointTableWidget::WaypointTableWidget(QWidget *parent) : QTableView(parent),
    model_(10, 3), delegate_(), normalBrush_(QColor(QStringLiteral("#242425"))), invalidBrush_(Qt::red)
{
    setModel(&model_);
    setItemDelegate(&delegate_);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setSelectionMode(QAbstractItemView::SingleSelection);

    model_.setHeaderData(0, Qt::Horizontal, tr("X"));
    model_.setHeaderData(1, Qt::Horizontal, tr("Y"));
    model_.setHeaderData(2, Qt::Horizontal, tr("θ"));

    QPalette palette;
    palette.setColor(QPalette::Window, QColor(QStringLiteral("#242425")));

    QHeaderView *horizontal = horizontalHeader();
    horizontal->setSectionResizeMode(QHeaderView::Stretch);
    horizontal->setSectionsMovable(false);
    horizontal->setSectionsClickable(false);
    horizontal->setPalette(palette);

    QHeaderView *vertical = verticalHeader();
    vertical->setSectionResizeMode(QHeaderView::Fixed);
    vertical->setSectionsMovable(false);
    vertical->setSectionsClickable(false);
    vertical->setPalette(palette);

    connect(&model_, &QAbstractItemModel::dataChanged, this, &WaypointTableWidget::dataChanged);
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
            if (result == QValidator::Acceptable)
                model_.setData(index, normalBrush_, Qt::BackgroundRole);
            else
                model_.setData(index, invalidBrush_, Qt::BackgroundRole);
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
            if (result == QValidator::Acceptable)
                model_.setData(index, normalBrush_, Qt::BackgroundRole);
            else
                model_.setData(index, invalidBrush_, Qt::BackgroundRole);
        }
    }
}

void WaypointTableWidget::dataChanged(const QModelIndex &topLeft,
                                      const QModelIndex &bottomRight,
                                      const QVector<int> &roles)
{
    if (topLeft == bottomRight && roles.contains(Qt::EditRole))
        model_.setData(topLeft, normalBrush_, Qt::BackgroundRole);
}
