#include "waypointtabledelegate.h"

WaypointTableDelegate::WaypointTableDelegate(QObject *parent) :
    QStyledItemDelegate(parent), xValidator_(new QDoubleValidator(this)),
    yValidator_(new QDoubleValidator(this)),
    angleValidator_(new QDoubleValidator(this))
{
    xValidator_->setRange(0, 0);
    yValidator_->setRange(0, 0);
    angleValidator_->setRange(0, 360);
}

QWidget *WaypointTableDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                                             const QModelIndex &index) const
{
    Q_UNUSED(option);

    QLineEdit *editor = new QLineEdit(parent);

    switch(index.column()) {
    case 0:
        editor->setValidator(xValidator_);
        break;
    case 1:
        editor->setValidator(yValidator_);
        break;
    case 2:
        editor->setValidator(angleValidator_);
        break;
    }

    return editor;
}

void WaypointTableDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option,
                                                 const QModelIndex &index) const
{
    Q_UNUSED(index);

    editor->setGeometry(option.rect);
}


void WaypointTableDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    const QString value = index.model()->data(index, Qt::EditRole).toString();

    QLineEdit *lineEdit = static_cast<QLineEdit*>(editor);
    lineEdit->setText(value);
}

void WaypointTableDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                         const QModelIndex &index) const
{
    QLineEdit *lineEdit = static_cast<QLineEdit*>(editor);
    const QString value = lineEdit->text();

    model->setData(index, value, Qt::EditRole);
}

void WaypointTableDelegate::setXRange(double min, double max)
{
    xValidator_->setRange(min, max);
}

void WaypointTableDelegate::setYRange(double min, double max)
{
    yValidator_->setRange(min, max);
}

QDoubleValidator *WaypointTableDelegate::xValidator() const
{
    return xValidator_;
}

QDoubleValidator *WaypointTableDelegate::yValidator() const
{
    return yValidator_;
}

QDoubleValidator *WaypointTableDelegate::angleValidator() const
{
    return angleValidator_;
}

void WaypointTableDelegate::initStyleOption(QStyleOptionViewItem *option,
                                                           const QModelIndex &index) const
{
    QStyledItemDelegate::initStyleOption(option, index);

    /*QBrush backgroundBrush;

    if (index.column() <= 1) {
        QString value = index.model()->data(index, Qt::EditRole).toString();

        if (index.column() == 0) {
            if (QValidator::Acceptable == xValidator_->
                    validate(value, *(static_cast<int*>(nullptr)))) {
                backgroundBrush = QColor("white");
            } else {
                backgroundBrush = QColor("red");
            }
        } else {
            if (QValidator::Acceptable == yValidator_->
                    validate(value, *(static_cast<int*>(nullptr)))) {
                backgroundBrush = QColor("white");
            } else {
                backgroundBrush = QColor("red");
            }
        }
    } else {
        backgroundBrush = QColor("white");
    }

    option->backgroundBrush = backgroundBrush;*/
}
