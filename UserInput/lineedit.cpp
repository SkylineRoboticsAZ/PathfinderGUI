#include "lineedit.h"

LineEdit::LineEdit()
{

}

void LineEdit::editingFinished()
{
    const QString &newText = text();

    if (textCache_ != newText) {
        const QString oldText = textCache_;

        textCache_ = newText;

        emit userChangedText(oldText, newText);
    }
}

void LineEdit::keyPressEvent(QKeyEvent *event)
{
    QLineEdit::keyPressEvent(event);

    if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter)
        editingFinished();
}

void LineEdit::focusOutEvent(QFocusEvent *event)
{
    QLineEdit::focusOutEvent(event);

    editingFinished();
}
