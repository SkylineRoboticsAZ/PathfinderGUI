#include "waypointtabledelegate.h"

WaypointTableDelegate::WaypointTableDelegate(QObject *parent) :
    QStyledItemDelegate(parent), xValidator_(new QDoubleValidator(this)),
    yValidator_(new QDoubleValidator(this)),
    angleValidator_(new QDoubleValidator(this)),
    normalBrush_(QColor(QStringLiteral("#242425"))), invalidBrush_(QColor(QStringLiteral("#921212"))),
    invalidHighlightBrush_(Qt::red), incompleteBrush_(QColor(QStringLiteral("#925e12"))),
    incompleteHighlightBrush_(QColor(QStringLiteral("#ff9900")))
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

    if (index.data(WaypointTableRoles::InvalidValue).toBool()) {
        option->backgroundBrush = invalidBrush_;
        option->palette.setBrush(QPalette::Highlight, invalidHighlightBrush_);
        option->text = tr("Invalid: ") + option->text;
    } else {
        if (index.data().toString().isEmpty()) {
            bool isEntireRowEmpty = true;

            int otherCells[2];

            switch (index.column()) {
            case 0:
                otherCells[0] = 1;
                otherCells[1] = 2;
                break;
            case 1:
                otherCells[0] = 0;
                otherCells[1] = 2;
                break;
            case 2:
                otherCells[0] = 0;
                otherCells[1] = 1;
                break;
            }

            for (int column : otherCells) {
                if (!index.model()->
                        index(index.row(), column).data().toString().isEmpty())
                    isEntireRowEmpty = false;
            }

            if (!isEntireRowEmpty) {
                option->backgroundBrush = incompleteBrush_;
                option->palette.setBrush(QPalette::Highlight, incompleteHighlightBrush_);
                //option->palette.setBrush(QPalette::Text, QBrush(Qt::black));
                option->text = tr("Incomplete");
            }
        }
    }
}
