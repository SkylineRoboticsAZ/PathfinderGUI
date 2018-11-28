#ifndef USERINPUT_H
#define USERINPUT_H

#include <QWidget>
#include <QPalette>
#include <QComboBox>
#include <QGridLayout>
#include <QLabel>
#include <QDebug>
#include <QGroupBox>
#include <QLineEdit>
#include <QDoubleValidator>
#include <QApplication>
#include <QMouseEvent>

class UserInput : public QWidget
{
    Q_OBJECT
public:
    explicit UserInput(QWidget *parent = nullptr);

signals:
    /* 0 = Tank
     * 1 = Swerve
     * 2 = Basic */
    void trajectoryTypeChanged(int type);

public slots:

private slots:
    void updateDisabledRobotFields(int index);

private:
    QDoubleValidator *fieldValidator_;
    QLineEdit *fieldWidthField_,
              *fieldLengthField_;
    QComboBox *trajectoryTypeBox_;
    QLineEdit *wheelbaseWidthField_,
              *wheelbaseDepthField_,
              *maxVelocityField_,
              *maxAccelerationField_,
              *maxJerkField_;
    QLabel *wheelbaseWidthLabel_,
           *wheelbaseDepthLabel_;

    QWidget *getFieldParametersGroupBox();
    QWidget *getRobotParametersGroupBox();
};

#endif // USERINPUT_H
