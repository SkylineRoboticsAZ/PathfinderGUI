#ifndef USERINPUT_H
#define USERINPUT_H

#include <QWidget>
#include <QPalette>
#include <QComboBox>
#include <QGridLayout>
#include <QLabel>
#include <QDebug>
#include <QGroupBox>
#include <QDoubleValidator>
#include <QApplication>
#include <QTabWidget>
#include <QTableView>

#include "tabbar.h"
#include "lineedit.h"
#include "waypointtabledelegate.h"
#include "waypointtablemodel.h"

using WaypointTable::WaypointTableDelegate;
using WaypointTable::WaypointTableModel;

class UserInput : public QTabWidget
{
    Q_OBJECT
public:
    explicit UserInput(QWidget *parent = nullptr);

public slots:

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

    QTableView *waypointTableView_;
    WaypointTableDelegate *waypointTableDelegate_;
    WaypointTableModel *waypointTableModel_;

    void configureLineEdit(LineEdit *lineEdit);
    QWidget *getFieldParametersGroupBox();
    QWidget *getRobotParametersGroupBox();
    QWidget *getTrajectoryParametersGroupBox();
    QTableView *getWaypointTable();
};

#endif // USERINPUT_H
