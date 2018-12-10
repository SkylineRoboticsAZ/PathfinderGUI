#ifndef PARAMETERSTAB_H
#define PARAMETERSTAB_H

#include <QDoubleValidator>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QComboBox>
#include <QWidget>
#include <QLabel>

#include "controls/lineedit.h"

class ParametersTab : public QWidget
{
    Q_OBJECT
public:
    explicit ParametersTab(QWidget *parent = nullptr);

signals:
    void fieldWidthChanged(QString width);
    void fieldLengthChanged(QString length);

private slots:
    void updateDisabledRobotFields(int index);

private:
    QDoubleValidator *fieldValidator_;
    LineEdit *fieldWidthField_,
              *fieldLengthField_;
    QComboBox *trajectoryTypeBox_;
    LineEdit *wheelbaseWidthField_,
              *wheelbaseDepthField_,
              *maxVelocityField_,
              *maxAccelerationField_,
              *maxJerkField_;
    QLabel *wheelbaseWidthLabel_,
           *wheelbaseDepthLabel_;
    QComboBox *functionTypeBox_,
              *sampleCountBox_;
    LineEdit *timeStepField_;

    void configureLineEdit(LineEdit *lineEdit);
    QWidget *getFieldParametersGroupBox();
    QWidget *getRobotParametersGroupBox();
    QWidget *getTrajectoryParametersGroupBox();
};

#endif // PARAMETERSTAB_H
