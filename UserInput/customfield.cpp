#include "customfield.h"

CustomField::CustomField(QWidget *parent) : QLineEdit(parent)
{
    setValidator(new QDoubleValidator(this));
}
