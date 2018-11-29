#include "userinput.h"

UserInput::UserInput(QWidget *parent) : QTabWidget(parent), fieldValidator_(new QDoubleValidator(this))
{
    QPalette palette = QPalette();
    palette.setColor(QPalette::Window, QColor(QStringLiteral("#434343")));
    setAutoFillBackground(true);
    setPalette(palette);

    setFocusPolicy(Qt::ClickFocus);

    fieldValidator_->setBottom(0);
    fieldValidator_->setDecimals(5);

    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addWidget(getFieldParametersGroupBox());
    mainLayout->addWidget(getRobotParametersGroupBox());
    mainLayout->addWidget(getTrajectoryParametersGroupBox());
    mainLayout->addStretch();

    QWidget *parametersWidget = new QWidget();
    parametersWidget->setLayout(mainLayout);
    parametersWidget->setPalette(palette);
    parametersWidget->setAutoFillBackground(true);

    QWidget *waypointsWidget = new QWidget();

    addTab(parametersWidget, QStringLiteral("Parameters"));
    addTab(waypointsWidget, QStringLiteral("Waypoints"));

    updateDisabledRobotFields(trajectoryTypeBox_->currentIndex());
}

void UserInput::updateDisabledRobotFields(int index)
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

void UserInput::configureLineEdit(LineEdit *lineEdit)
{
    lineEdit->setValidator(fieldValidator_);
    lineEdit->setMaxLength(15);
    lineEdit->setPlaceholderText(QStringLiteral("Enter a value"));
}

QWidget *UserInput::getFieldParametersGroupBox()
{
    QLabel *fieldHeightLabel = new QLabel(QStringLiteral("Field Length:"));

    fieldLengthField_ = new LineEdit();
    configureLineEdit(fieldLengthField_);

    QLabel *fieldWidthLabel = new QLabel(QStringLiteral("Field Width:"));

    fieldWidthField_ = new LineEdit();
    configureLineEdit(fieldWidthField_);

    QGridLayout *layout = new QGridLayout();
    layout->addWidget(fieldHeightLabel, 0, 0);
    layout->addWidget(fieldLengthField_, 0, 1);
    layout->addWidget(fieldWidthLabel, 1, 0);
    layout->addWidget(fieldWidthField_, 1, 1);

    QGroupBox *group = new QGroupBox();
    group->setTitle(QStringLiteral("Field Parameters"));
    group->setLayout(layout);

    return group;
}

QWidget *UserInput::getRobotParametersGroupBox()
{
    QLabel *maxVelocityLabel = new QLabel(QStringLiteral("Max Velocity (dx/dt):"));

    maxVelocityField_ = new LineEdit();
    configureLineEdit(maxVelocityField_);

    QLabel *maxAccelerationLabel = new QLabel(QStringLiteral("Max Acceleration (dv/dt):"));

    maxAccelerationField_ = new LineEdit();
    configureLineEdit(maxAccelerationField_);

    QLabel *maxJerkLabel = new QLabel(QStringLiteral("Max Jerk (da/dt):"));

    maxJerkField_ = new LineEdit();
    configureLineEdit(maxJerkField_);

    QLabel *trajectoryTypeLabel = new QLabel(QStringLiteral("Trajectory Type:"));

    trajectoryTypeBox_ = new QComboBox();
    trajectoryTypeBox_->addItems({"Tank", "Swerve", "Basic"});
    connect(trajectoryTypeBox_, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &UserInput::updateDisabledRobotFields);

    wheelbaseWidthLabel_ = new QLabel(QStringLiteral("Wheelbase Width:"));

    wheelbaseWidthField_ = new LineEdit();
    configureLineEdit(wheelbaseWidthField_);

    wheelbaseDepthLabel_ = new QLabel(QStringLiteral("Wheelbase Depth:"));

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
    group->setTitle(QStringLiteral("Robot Parameters"));
    group->setLayout(layout);

    return group;
}

QWidget *UserInput::getTrajectoryParametersGroupBox()
{
    QLabel *functionTypeLabel = new QLabel(QStringLiteral("Function Type:"));

    functionTypeBox_ = new QComboBox();
    functionTypeBox_->addItems({"Cubic", "Quintic"});

    QLabel *sampleCountLabel = new QLabel(QStringLiteral("Sample Count:"));

    sampleCountBox_ = new QComboBox();
    sampleCountBox_->addItems({"Fast (1k)", "Low (10k)", "High (100k)"});

    QLabel *timeStepLabel = new QLabel(QStringLiteral("Time Step:"));

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
    group->setTitle(QStringLiteral("Trajectory Parameters"));
    group->setLayout(layout);

    return group;
}
