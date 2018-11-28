#include "userinput.h"

UserInput::UserInput(QWidget *parent) : QWidget(parent), fieldValidator_(new QDoubleValidator(this))
{
    QPalette palette = QPalette();
    palette.setColor(QPalette::Background, QColor(QStringLiteral("#434343")));
    setAutoFillBackground(true);
    setPalette(palette);

    fieldValidator_->setBottom(0);
    fieldValidator_->setDecimals(5);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(getFieldParametersGroupBox());
    mainLayout->addWidget(getRobotParametersGroupBox());
    mainLayout->addStretch();

    updateDisabledRobotFields(trajectoryTypeBox_->currentIndex());
}

void UserInput::mousePressEvent(QMouseEvent *event)
{
    QApplication::focusWidget()->clearFocus();
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

QWidget *UserInput::getFieldParametersGroupBox()
{
    QLabel *fieldHeightLabel = new QLabel(QStringLiteral("Field Length:"));

    fieldLengthField_ = new QLineEdit();
    fieldLengthField_->setValidator(fieldValidator_);

    QLabel *fieldWidthLabel = new QLabel(QStringLiteral("Field Width:"));

    fieldWidthField_ = new QLineEdit();
    fieldWidthField_->setValidator(fieldValidator_);

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

    maxVelocityField_ = new QLineEdit();
    maxVelocityField_->setValidator(fieldValidator_);

    QLabel *maxAccelerationLabel = new QLabel(QStringLiteral("Max Acceleration (dv/dt):"));

    maxAccelerationField_ = new QLineEdit();
    maxAccelerationField_->setValidator(fieldValidator_);

    QLabel *maxJerkLabel = new QLabel(QStringLiteral("Max Jerk (da/dt):"));

    maxJerkField_ = new QLineEdit();
    maxJerkField_->setValidator(fieldValidator_);

    QLabel *trajectoryTypeLabel = new QLabel(QStringLiteral("Trajectory Type:"));

    trajectoryTypeBox_ = new QComboBox();
    trajectoryTypeBox_->addItems({"Tank", "Swerve", "Basic"});
    connect(trajectoryTypeBox_, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &UserInput::updateDisabledRobotFields);
    connect(trajectoryTypeBox_, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &UserInput::trajectoryTypeChanged);

    wheelbaseWidthLabel_ = new QLabel(QStringLiteral("Wheelbase Width:"));

    wheelbaseWidthField_ = new QLineEdit();
    wheelbaseWidthField_->setValidator(fieldValidator_);

    wheelbaseDepthLabel_ = new QLabel(QStringLiteral("Wheelbase Depth:"));

    wheelbaseDepthField_ = new QLineEdit();
    wheelbaseDepthField_->setValidator(fieldValidator_);

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
