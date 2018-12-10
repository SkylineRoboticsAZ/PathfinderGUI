#include "parameterstab.h"

ParametersTab::ParametersTab(QWidget *parent) : QWidget(parent),
    fieldValidator_(new QDoubleValidator())
{
    fieldValidator_->setBottom(0);

    setFocusPolicy(Qt::ClickFocus);

    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addWidget(getFieldParametersGroupBox());
    mainLayout->addWidget(getRobotParametersGroupBox());
    mainLayout->addWidget(getTrajectoryParametersGroupBox());
    mainLayout->addStretch();

    setLayout(mainLayout);

    //Implement code for updating the table
    connect(fieldWidthField_, &LineEdit::userChangedText, this,
            [=](QString oldText, QString newText)
    { Q_UNUSED(oldText); emit fieldWidthChanged(newText); });
    connect(fieldLengthField_, &LineEdit::userChangedText, this,
            [=](QString oldText, QString newText)
    { Q_UNUSED(oldText); emit fieldLengthChanged(newText); });
    connect(trajectoryTypeBox_, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &ParametersTab::updateDisabledRobotFields);

    updateDisabledRobotFields(trajectoryTypeBox_->currentIndex());
}

void ParametersTab::updateDisabledRobotFields(int index)
{
    bool wheelbaseWidthDisabled, wheelbaseDepthDisabled;

    switch (index)
    {
    case 0:
        wheelbaseWidthDisabled = false;
        wheelbaseDepthDisabled = true;
        break;
    case 1:
        wheelbaseWidthDisabled = false;
        wheelbaseDepthDisabled = false;
        break;
    case 2:
        wheelbaseWidthDisabled = true;
        wheelbaseDepthDisabled = true;
        break;
    default:
        wheelbaseWidthDisabled = false;
        wheelbaseDepthDisabled = true;
    }

    wheelbaseWidthLabel_->setDisabled(wheelbaseWidthDisabled);
    wheelbaseWidthField_->setDisabled(wheelbaseWidthDisabled);

    wheelbaseDepthLabel_->setDisabled(wheelbaseDepthDisabled);
    wheelbaseDepthField_->setDisabled(wheelbaseDepthDisabled);
}

void ParametersTab::configureLineEdit(LineEdit *lineEdit)
{
    lineEdit->setValidator(fieldValidator_);
    lineEdit->setMaxLength(15);
    lineEdit->setPlaceholderText(tr("Enter a value"));
}

QWidget *ParametersTab::getFieldParametersGroupBox()
{
    QLabel *fieldHeightLabel = new QLabel(tr("Field Length:"));

    fieldLengthField_ = new LineEdit();
    configureLineEdit(fieldLengthField_);

    QLabel *fieldWidthLabel = new QLabel(tr("Field Width:"));

    fieldWidthField_ = new LineEdit();
    configureLineEdit(fieldWidthField_);

    QGridLayout *layout = new QGridLayout();
    layout->addWidget(fieldHeightLabel, 0, 0);
    layout->addWidget(fieldLengthField_, 0, 1);
    layout->addWidget(fieldWidthLabel, 1, 0);
    layout->addWidget(fieldWidthField_, 1, 1);

    QGroupBox *group = new QGroupBox();
    group->setTitle(tr("Field Parameters"));
    group->setLayout(layout);

    return group;
}

QWidget *ParametersTab::getRobotParametersGroupBox()
{
    QLabel *maxVelocityLabel = new QLabel(tr("Max Velocity (dx/dt):"));

    maxVelocityField_ = new LineEdit();
    configureLineEdit(maxVelocityField_);

    QLabel *maxAccelerationLabel = new QLabel(tr("Max Acceleration (dv/dt):"));

    maxAccelerationField_ = new LineEdit();
    configureLineEdit(maxAccelerationField_);

    QLabel *maxJerkLabel = new QLabel(tr("Max Jerk (da/dt):"));

    maxJerkField_ = new LineEdit();
    configureLineEdit(maxJerkField_);

    QLabel *trajectoryTypeLabel = new QLabel(tr("Trajectory Type:"));

    trajectoryTypeBox_ = new QComboBox();
    trajectoryTypeBox_->addItems({"Tank", "Swerve", "Basic"});

    wheelbaseWidthLabel_ = new QLabel(tr("Wheelbase Width:"));

    wheelbaseWidthField_ = new LineEdit();
    configureLineEdit(wheelbaseWidthField_);

    wheelbaseDepthLabel_ = new QLabel(tr("Wheelbase Depth:"));

    wheelbaseDepthField_ = new LineEdit();
    configureLineEdit(wheelbaseDepthField_);

    QGridLayout *layout = new QGridLayout();
    layout->addWidget(maxVelocityLabel, 0, 0);
    layout->addWidget(maxVelocityField_, 0, 1);
    layout->addWidget(maxAccelerationLabel, 2, 0);
    layout->addWidget(maxAccelerationField_, 2, 1);
    layout->addWidget(maxJerkLabel, 3, 0);
    layout->addWidget(maxJerkField_, 3, 1);
    layout->addWidget(trajectoryTypeLabel, 4, 0);
    layout->addWidget(trajectoryTypeBox_, 4, 1);
    layout->addWidget(wheelbaseWidthLabel_, 5, 0);
    layout->addWidget(wheelbaseWidthField_, 5, 1);
    layout->addWidget(wheelbaseDepthLabel_, 6, 0);
    layout->addWidget(wheelbaseDepthField_, 6, 1);

    QGroupBox *group = new QGroupBox();
    group->setTitle(tr("Robot Parameters"));
    group->setLayout(layout);

    return group;
}

QWidget *ParametersTab::getTrajectoryParametersGroupBox()
{
    QLabel *functionTypeLabel = new QLabel(tr("Function Type:"));

    functionTypeBox_ = new QComboBox();
    functionTypeBox_->addItems({tr("Cubic"), tr("Quintic")});

    QLabel *sampleCountLabel = new QLabel(tr("Sample Count:"));

    sampleCountBox_ = new QComboBox();
    sampleCountBox_->addItems({tr("Fast (1k)"), tr("Low (10k)"), tr("High (100k)")});

    QLabel *timeStepLabel = new QLabel(tr("Time Step:"));

    timeStepField_ = new LineEdit();
    configureLineEdit(timeStepField_);

    QGridLayout *layout = new QGridLayout();
    layout->addWidget(functionTypeLabel, 0, 0);
    layout->addWidget(functionTypeBox_, 0, 1);
    layout->addWidget(sampleCountLabel, 1, 0);
    layout->addWidget(sampleCountBox_, 1, 1);
    layout->addWidget(timeStepLabel, 2, 0);
    layout->addWidget(timeStepField_, 2, 1);

    QGroupBox *group = new QGroupBox();
    group->setTitle(tr("Trajectory Parameters"));
    group->setLayout(layout);

    return group;
}
