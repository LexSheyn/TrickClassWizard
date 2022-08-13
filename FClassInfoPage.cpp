#include "FClassInfoPage.h"

FClassInfoPage::FClassInfoPage(QWidget* Parent)
    : QWizardPage (Parent)
{
    setTitle(tr("Class information"));
    setSubTitle(tr("\nSpecify basic information about the class."));

    ClassValidator = new QRegularExpressionValidator(QRegularExpression("\\w{1,}"), this);

    ClassNameLineEdit = new QLineEdit();
    ClassNameLineEdit->setValidator(ClassValidator);

    ClassNameLabel = new QLabel(tr("Name:"));
    ClassNameLabel->setBuddy(ClassNameLineEdit);

    BaseClassNameLineEdit = new QLineEdit();
    BaseClassNameLineEdit->setValidator(ClassValidator);

    BaseClassNameLabel = new QLabel(tr("Base class name:"));
    BaseClassNameLabel->setBuddy(BaseClassNameLineEdit);

    ClassLayout = new QGridLayout();
    ClassLayout->addWidget(ClassNameLabel       , 0, 0);
    ClassLayout->addWidget(ClassNameLineEdit    , 0, 1);
    ClassLayout->addWidget(BaseClassNameLabel   , 1, 0);
    ClassLayout->addWidget(BaseClassNameLineEdit, 1, 1);

    ClassGroup = new QGroupBox("Class");
    ClassGroup->setLayout(ClassLayout);

    HeaderOnlyCheckBox = new QCheckBox(tr("Header only"));

    HeaderOnlyLayout = new QVBoxLayout();
    HeaderOnlyLayout->addWidget(HeaderOnlyCheckBox);

    HeaderOnlyGroup = new QGroupBox();
    HeaderOnlyGroup->setLayout(HeaderOnlyLayout);

    NoCopyCheckBox      = new QCheckBox(tr("No"));
    DefaultCopyCheckBox = new QCheckBox(tr("Default"));
    NoMoveCheckBox      = new QCheckBox(tr("No"));
    DefaultMoveCheckBox = new QCheckBox(tr("Default"));

    connect(NoCopyCheckBox     , &QCheckBox::toggled, this, &FClassInfoPage::UncheckDefaultCopy);
    connect(DefaultCopyCheckBox, &QCheckBox::toggled, this, &FClassInfoPage::UncheckNoCopy);
    connect(NoMoveCheckBox     , &QCheckBox::toggled, this, &FClassInfoPage::UncheckDefaultMove);
    connect(DefaultMoveCheckBox, &QCheckBox::toggled, this, &FClassInfoPage::UncheckNoMove);

    registerField("ClassName*"   , ClassNameLineEdit);
    registerField("BaseClassName", BaseClassNameLineEdit);
    registerField("HeaderOnly"   , HeaderOnlyCheckBox);
    registerField("NoCopy"       , NoCopyCheckBox);
    registerField("NoMove"       , NoMoveCheckBox);
    registerField("DefaultCopy"  , DefaultCopyCheckBox);
    registerField("DefaultMove"  , DefaultMoveCheckBox);

    CopyLayout = new QVBoxLayout();
    CopyLayout->addWidget(NoCopyCheckBox);
    CopyLayout->addWidget(DefaultCopyCheckBox);

    CopyGroupBox = new QGroupBox(tr("Copy constructor and assignment operator"));
    CopyGroupBox->setLayout(CopyLayout);

    MoveLayout = new QVBoxLayout();
    MoveLayout->addWidget(NoMoveCheckBox);
    MoveLayout->addWidget(DefaultMoveCheckBox);

    MoveGroupBox = new QGroupBox(tr("Move constructor and assignment operator"));
    MoveGroupBox->setLayout(MoveLayout);

    Layout = new QVBoxLayout();
    Layout->addWidget(ClassGroup);
    Layout->addWidget(HeaderOnlyGroup);
    Layout->addWidget(CopyGroupBox);
    Layout->addWidget(MoveGroupBox);

    setLayout(Layout);
}

void FClassInfoPage::UncheckNoCopy(bool Checked)
{
    if (Checked == false)
    {
        return;
    }

    NoCopyCheckBox->setChecked(!Checked);
}

void FClassInfoPage::UncheckDefaultCopy(bool Checked)
{
    if (Checked == false)
    {
        return;
    }

    DefaultCopyCheckBox->setChecked(!Checked);
}

void FClassInfoPage::UncheckNoMove(bool Checked)
{
    if (Checked == false)
    {
        return;
    }

    NoMoveCheckBox->setChecked(!Checked);
}

void FClassInfoPage::UncheckDefaultMove(bool Checked)
{
    if (Checked == false)
    {
        return;
    }

    DefaultMoveCheckBox->setChecked(!Checked);
}























































