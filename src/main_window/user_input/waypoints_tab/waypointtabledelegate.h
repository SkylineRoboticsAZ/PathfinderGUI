#ifndef WAYPOINTTABLEDELEGATE_H
#define WAYPOINTTABLEDELEGATE_H

#include <QStyledItemDelegate>
#include <QLineEdit>
#include <QDoubleValidator>
#include <QDebug>
#include <memory>

class WaypointTableDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    WaypointTableDelegate(QObject *parent = nullptr);

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const override;

    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option,
                              const QModelIndex &index) const override;

    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;

    void setXRange(double bottom, double top);
    void setYRange(double bottom, double top);

    QDoubleValidator *xValidator() const;
    QDoubleValidator *yValidator() const;
    QDoubleValidator *angleValidator() const;

protected:
    void initStyleOption(QStyleOptionViewItem *option, const QModelIndex &index) const override;

private:
    QDoubleValidator *xValidator_,
                     *yValidator_,
                     *angleValidator_;
};

#endif // WAYPOINTTABLEDELEGATE_H
