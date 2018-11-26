#ifndef CUSTOMFIELD_H
#define CUSTOMFIELD_H

#include <QLineEdit>
#include <QDoubleValidator>

class CustomField : public QLineEdit
{
    Q_OBJECT
public:
    explicit CustomField(QWidget *parent = nullptr);
};

#endif // CUSTOMFIELD_H
