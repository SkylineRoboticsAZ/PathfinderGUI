#ifndef WAYPOINTTABLEDELEGATE_H
#define WAYPOINTTABLEDELEGATE_H

#include <QStyledItemDelegate>
#include <QLineEdit>
#include <QDoubleValidator>
#include <QDebug>

#include "waypointtablemodel.h"

namespace WaypointTable
{

class WaypointTableDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    WaypointTableDelegate(WaypointTableModel *model, QObject *parent = nullptr);

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const override;

    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option,
                              const QModelIndex &index) const override;

    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;

    void setXRange(double min, double max);
    void setYRange(double min, double max);

protected:
    void initStyleOption(QStyleOptionViewItem *option, const QModelIndex &index) const override;

private:
    WaypointTableModel *model_;
    QDoubleValidator *xValidator_,
                     *yValidator_,
                     *angleValidator_;
};

}

#endif // WAYPOINTTABLEDELEGATE_H
