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

    // Implement code for updating the table
    connect(fieldLengthField_, &LineEdit::userChangedText, this,
            [=](QString oldText, QString newText)
    { Q_UNUSED(oldText); emit fieldLengthChanged(newText); });
    connect(fieldWidthField_, &LineEdit::userChangedText, this,
            [=](QString oldText, QString newText)
    { Q_UNUSED(oldText); emit fieldWidthChanged(newText); });
    connect(trajectoryTypeBox_, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &ParametersTab::updateDisabledRobotFields);

    errorData_ << fieldWidth << fieldLength << wheelbaseWidth << wheelbaseDepth
               << maxVelocity << maxAcceleration << maxJerk << timeStep;

    // Connect all the monitoring signals
    connect(fieldLengthField_, &LineEdit::userChangedText, this,
            [=](QString oldText, QString newText)
    { Q_UNUSED(oldText); fieldChanged(newText, Input::fieldLength); });
    connect(fieldWidthField_, &LineEdit::userChangedText, this,
            [=](QString oldText, QString newText)
    { Q_UNUSED(oldText); fieldChanged(newText, Input::fieldWidth); });

    connect(trajectoryTypeBox_,
            QOverload<int>::of(&QComboBox::currentIndexChanged), this,
            [=](int index) { comboBoxChanged(index, Input::trajectoryType); });

    connect(wheelbaseWidthField_, &LineEdit::userChangedText, this,
            [=](QString oldText, QString newText)
    { Q_UNUSED(oldText); fieldChanged(newText, Input::wheelbaseWidth); });
    connect(wheelbaseDepthField_, &LineEdit::userChangedText, this,
            [=](QString oldText, QString newText)
    { Q_UNUSED(oldText); fieldChanged(newText, Input::wheelbaseDepth); });
    connect(maxVelocityField_, &LineEdit::userChangedText, this,
            [=](QString oldText, QString newText)
    { Q_UNUSED(oldText); fieldChanged(newText, Input::maxVelocity); });
    connect(maxAccelerationField_, &LineEdit::userChangedText, this,
            [=](QString oldText, QString newText)
    { Q_UNUSED(oldText); fieldChanged(newText, Input::maxAcceleration); });
    connect(maxJerkField_, &LineEdit::userChangedText, this,
            [=](QString oldText, QString newText)
    { Q_UNUSED(oldText); fieldChanged(newText, Input::maxJerk); });

    connect(functionTypeBox_,
            QOverload<int>::of(&QComboBox::currentIndexChanged), this,
            [=](int index) { comboBoxChanged(index, Input::functionType); });
    connect(sampleCountBox_,
            QOverload<int>::of(&QComboBox::currentIndexChanged), this,
            [=](int index) { comboBoxChanged(index, Input::sampleCount); });

    connect(timeStepField_, &LineEdit::userChangedText, this,
            [=](QString oldText, QString newText)
    { Q_UNUSED(oldText); fieldChanged(newText, Input::timeStep); });

    updateDisabledRobotFields(trajectoryTypeBox_->currentIndex());
}

bool ParametersTab::isDataValid() const
{
    return errorData_.isEmpty();
}

ParametersTab::UserData ParametersTab::getUserData() const
{
    UserData data;
    data.fieldLength = fieldLengthField_->text();
    data.fieldWidth = fieldWidthField_->text();
    data.trajectoryType = trajectoryTypeBox_->currentIndex();
    data.wheelbaseWidth = wheelbaseWidthField_->text();
    data.wheelbaseDepth = wheelbaseDepthField_->text();
    data.maxVelocity = maxVelocityField_->text();
    data.maxAcceleration = maxAccelerationField_->text();
    data.maxJerk = maxJerkField_->text();
    data.functionType = functionTypeBox_->currentIndex();
    data.sampleCount = sampleCountBox_->currentIndex();
    data.timeStep = timeStepField_->text();
    return data;
}

ParametersTab::ErrorData ParametersTab::getErrorData() const
{
    return errorData_;
}

void ParametersTab::setUserData(UserData data)
{
    const bool oldValidity = isDataValid();

    setUserDataHelper(fieldLengthField_, Input::fieldLength, data.fieldLength);
    setUserDataHelper(fieldWidthField_, Input::fieldWidth, data.fieldWidth);
    setUserDataHelper(trajectoryTypeBox_, Input::trajectoryType,
                      data.trajectoryType);
    setUserDataHelper(wheelbaseWidthField_, Input::wheelbaseWidth,
                      data.wheelbaseWidth);
    setUserDataHelper(wheelbaseDepthField_, Input::wheelbaseDepth,
                      data.wheelbaseDepth);
    setUserDataHelper(maxVelocityField_, Input::maxVelocity, data.maxVelocity);
    setUserDataHelper(maxAccelerationField_, Input::maxAcceleration,
                      data.maxAcceleration);
    setUserDataHelper(maxJerkField_, Input::maxJerk, data.maxJerk);
    setUserDataHelper(functionTypeBox_, Input::functionType, data.functionType);
    setUserDataHelper(sampleCountBox_, Input::sampleCount, data.sampleCount);
    setUserDataHelper(timeStepField_, Input::timeStep, data.timeStep);

    const bool newValidity = isDataValid();

    if (oldValidity != newValidity)
        emit dataValidityChanged(newValidity);

    emit errorDataChanged(getErrorData());
    emit userDataChanged(getUserData());
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

    const bool oldValidity = isDataValid();

    const bool wheelbaseWidthEmpty =
            !wheelbaseWidthDisabled &&
            !errorData_.contains(Input::wheelbaseWidth) &&
            wheelbaseWidthField_->text().isEmpty();
    const bool wheelbaseDepthEmpty =
            !wheelbaseDepthDisabled &&
            !errorData_.contains(Input::wheelbaseDepth) &&
            wheelbaseDepthField_->text().isEmpty();

    if (wheelbaseWidthEmpty || wheelbaseDepthEmpty) {
        if (wheelbaseWidthEmpty)
            errorData_.insert(Input::wheelbaseWidth);
        if (wheelbaseDepthEmpty)
            errorData_.insert(Input::wheelbaseDepth);

        if (oldValidity)
            emit dataValidityChanged(false);

        emit errorDataChanged(getErrorData());
    } else {
        const bool wasWheelbaseWidthErrored =
                wheelbaseWidthDisabled && errorData_.remove(wheelbaseWidth);
        const bool wasWheelbaseDepthErrored =
                wheelbaseDepthDisabled && errorData_.remove(wheelbaseDepth);

        if (wasWheelbaseWidthErrored || wasWheelbaseDepthErrored) {
            if (!oldValidity && isDataValid())
                emit dataValidityChanged(true);

            emit errorDataChanged(getErrorData());
        }
    }
}

void ParametersTab::fieldChanged(QString newText, Input input)
{
    const bool oldValidity = isDataValid();

    // Data in this part of the interface is never invalid, only incomplete.
    // Therefore, we check if the new text is empty
    if (newText.isEmpty()) {
        errorData_.insert(input);

        if (oldValidity)
            emit dataValidityChanged(false);

        emit errorDataChanged(getErrorData());
    } else if (errorData_.remove(input)) {
        // Code in here is executed when a field is changed from incomplete
        // to complete
        if (isDataValid())
            emit dataValidityChanged(true);

        emit errorDataChanged(getErrorData());
    }

    emit userDataChanged(getUserData());
}

void ParametersTab::comboBoxChanged(int newIndex, Input input)
{
    const bool oldValidity = isDataValid();

    if (newIndex == -1) {
        errorData_.insert(input);

        if (oldValidity)
            emit dataValidityChanged(false);

        emit errorDataChanged(getErrorData());
    } else if (errorData_.remove(input)) {
        if (isDataValid())
            emit dataValidityChanged(true);

        emit errorDataChanged(getErrorData());
    }

    emit userDataChanged(getUserData());
}

void ParametersTab::configureLineEdit(LineEdit *lineEdit)
{
    lineEdit->setValidator(fieldValidator_);
    lineEdit->setMaxLength(15);
    lineEdit->setPlaceholderText(tr("Enter a value"));
}

void ParametersTab::setUserDataHelper(LineEdit *lineEdit,
                                      Input input, QString data)
{
    int useless;

    const bool validated = QValidator::Invalid !=
            lineEdit->validator()->validate(data, useless);

    if (validated) {
        lineEdit->setText(data);
        errorData_.remove(input);
    }
}

void ParametersTab::setUserDataHelper(QComboBox *comboBox,
                                      Input input, int data)
{
    const bool validated = data >= 0 && data < comboBox->count();

    if (validated) {
        comboBox->setCurrentIndex(data);
        errorData_.remove(input);
    }
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
