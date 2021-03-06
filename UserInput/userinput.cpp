#include "userinput.h"

UserInput::UserInput(QWidget *parent) : QTabWidget(parent), fieldValidator_(new QDoubleValidator(this))
{
    QPalette palette = QPalette();
    palette.setColor(QPalette::Window, QColor(QStringLiteral("#434343")));
    setAutoFillBackground(true);
    setPalette(palette);

    setFocusPolicy(Qt::ClickFocus);

    fieldValidator_->setBottom(0);

    TabBar *tabBar = new TabBar();
    setTabBar(tabBar);
    tabBar->setGeometry(0, 0, width(), 50);

    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addWidget(getFieldParametersGroupBox());
    mainLayout->addWidget(getRobotParametersGroupBox());
    mainLayout->addWidget(getTrajectoryParametersGroupBox());
    mainLayout->addStretch();

    QWidget *parametersWidget = new QWidget();
    parametersWidget->setLayout(mainLayout);

    QGridLayout *tableLayout = new QGridLayout();

    //Add code for the table buttons
    tableAddRowButton_ = new QPushButton(QStringLiteral("Add Row"));
    tableRemoveRowButton_ = new QPushButton(QStringLiteral("Remove Row"));
    tableClearButton_ = new QPushButton(QStringLiteral("Clear Table"));

    tableLayout->addWidget(tableAddRowButton_, 0, 0);
    tableLayout->addWidget(tableRemoveRowButton_, 0, 1);
    tableLayout->addWidget(tableClearButton_, 0, 2);
    tableLayout->addWidget(getWaypointTable(), 1, 0, 1, 3);

    QWidget *waypointsWidget = new QWidget();
    waypointsWidget->setLayout(tableLayout);
    waypointsWidget->setContentsMargins(5, 5, 5, 5);

    addTab(parametersWidget, QStringLiteral("Parameters"));
    addTab(waypointsWidget, QStringLiteral("Waypoints"));

    connect(fieldWidthField_, &LineEdit::userChangedText, this,
            [=](QString oldText, QString newText)
    { Q_UNUSED(oldText); waypointTableDelegate_->setYRange(0, newText.toDouble()); });
    connect(fieldLengthField_, &LineEdit::userChangedText, this,
            [=](QString oldText, QString newText)
    { Q_UNUSED(oldText); waypointTableDelegate_->setXRange(0, newText.toDouble()); });
    updateDisabledRobotFields(trajectoryTypeBox_->currentIndex());

    connect(tableAddRowButton_, &QPushButton::clicked, waypointTableModel_,
            [=](){ waypointTableModel_->appendRow(new QStandardItem); });
    connect(tableRemoveRowButton_, &QPushButton::clicked, waypointTableModel_,
            [=]()
    {
        QItemSelectionModel *model = waypointTableView_->selectionModel();
        if (model->hasSelection()) {
            waypointTableModel_->removeRow(model->selectedRows().front().row());
        }
    });
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

QTableView *UserInput::getWaypointTable()
{
    waypointTableModel_ = new WaypointTableModel(10, 3, this);

    waypointTableDelegate_ = new WaypointTableDelegate(waypointTableModel_, this);

    waypointTableView_ = new QTableView();
    waypointTableView_->setModel(waypointTableModel_);
    waypointTableView_->setItemDelegate(waypointTableDelegate_);
    waypointTableView_->setSelectionBehavior(QAbstractItemView::SelectRows);
    waypointTableView_->setSelectionMode(QAbstractItemView::SingleSelection);

    return waypointTableView_;
}
