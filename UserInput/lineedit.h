#ifndef LINEEDIT_H
#define LINEEDIT_H

#include <QLineEdit>
#include <QValidator>
#include <QKeyEvent>
#include <QFocusEvent>
#include <QDebug>

class LineEdit : public QLineEdit
{
    Q_OBJECT
public:
    LineEdit(QWidget *parent = nullptr);
    LineEdit(const QString &contents, QWidget *parent = nullptr);

signals:
    void userChangedText(QString oldText, QString newText);

private:
    QString textCache_;

    void editingFinished();
    void keyPressEvent(QKeyEvent *event) override;
    void focusOutEvent(QFocusEvent *event) override;
};

#endif // LINEEDIT_H
