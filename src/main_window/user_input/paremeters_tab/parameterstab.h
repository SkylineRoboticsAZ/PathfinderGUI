#ifndef PARAMETERSTAB_H
#define PARAMETERSTAB_H

#include <QDoubleValidator>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QComboBox>
#include <QWidget>
#include <QLabel>
#include <QSet>
#include <QDebug>

#include "controls/lineedit.h"

class ParametersTab : public QWidget
{
    Q_OBJECT
public:
    struct UserData
    {
        QString fieldLength, fieldWidth;

        /*
         * 0 -> Tank
         * 1 -> Swerve
         * 2 -> Basic
         */
        int trajectoryType;
        QString wheelbaseWidth, wheelbaseDepth,
        maxVelocity, maxAcceleration, maxJerk;

        /*
         * 0 -> Cubic
         * 1 -> Quintic
         */
        int functionType;

        /*
         * 0 -> Fast (1K)
         * 1 -> Low (10K)
         * 2 -> High (100K)
         */
        int sampleCount;
        QString timeStep;
    };

    enum Input
    {
        fieldLength, fieldWidth, trajectoryType,
        wheelbaseWidth, wheelbaseDepth, maxVelocity,
        maxAcceleration, maxJerk, functionType, sampleCount,
        timeStep
    };

    // Each errored input is incomplete
    typedef QSet<Input> ErrorData;

    explicit ParametersTab(QWidget *parent = nullptr);

    /**
     * @brief isDataValid Gets the validity of the data
     * @return True if valid, false otherwise
     *
     * Valid data is defined as completely filled in, within
     * appropriate ranges, and in a proper format
     */
    bool isDataValid() const;

    /**
     * @brief getUserData Gets all user data from the input fields
     * @return The user data
     */
    UserData getUserData() const;

    /**
     * @brief getErrorData Gets all error data - error data tells which
     * input fields are incomplete
     * @return The errored fields
     */
    ErrorData getErrorData() const;

    /**
     * @brief setUserData Sets the data that appears in the UI
     * Values will be checked for validity and will not be applied
     * if they are invalid
     * @param data The data
     */
    void setUserData(UserData data);

signals:
    void fieldWidthChanged(QString width);
    void fieldLengthChanged(QString length);

    void dataValidityChanged(bool isValid);
    void userDataChanged(UserData data);
    void errorDataChanged(ErrorData data);

private slots:
    void updateDisabledRobotFields(int index);

private:
    ErrorData errorData_;

    QDoubleValidator *fieldValidator_;
    LineEdit *fieldLengthField_,
              *fieldWidthField_;
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

    void fieldChanged(QString newText, Input input);
    void comboBoxChanged(int newIndex, Input input);
    void configureLineEdit(LineEdit *lineEdit);
    void setUserDataHelper(LineEdit *lineEdit, Input input, QString data);
    void setUserDataHelper(QComboBox *comboBox, Input input, int data);
    QWidget *getFieldParametersGroupBox();
    QWidget *getRobotParametersGroupBox();
    QWidget *getTrajectoryParametersGroupBox();
};

#endif // PARAMETERSTAB_H
