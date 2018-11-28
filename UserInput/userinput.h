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

    double fieldWidth() const;
    double fieldLength() const;

    /* 0 = Tank
     * 1 = Swerve
     * 2 = Basic */
    int trajectoryType() const;

    double wheelbaseWidth() const;
    double wheelbaseDepth() const;
    double maxVelocity() const;
    double maxAcceleration() const;
    double maxJerk() const;

signals:
    void fieldWidthChanged(double width);
    void fieldLengthChanged(double length);

    /* 0 = Tank
     * 1 = Swerve
     * 2 = Basic */
    void trajectoryTypeChanged(int type);

    void wheelbaseWidthChanged(double width);
    void wheelbaseDepthChanged(double depth);
    void maxVelocityChanged(double velocity);
    void maxAccelerationChanged(double acceleration);
    void maxJerkChanged(double jerk);

public slots:

private slots:
    void updateDisabledRobotFields(int index);

    void setTempVar(double value);

private:
    double tempValue_;

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
