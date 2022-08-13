#include "FClassInfoPage.h"

FClassInfoPage::FClassInfoPage(QWidget* Parent)
    : QWizardPage (Parent)
{
    setTitle(tr("Class information"));
    setSubTitle(tr("Specify basic information about the class."));
    //setPixmap(QWizard::LogoPixmap, QPixmap(":/images/logo1.png"));

    Validator = new QRegularExpressionValidator(QRegularExpression("\\w{1,}"), this);

    ClassNameLineEdit = new QLineEdit();
    ClassNameLineEdit->setValidator(Validator);

    ClassNameLabel = new QLabel(tr("Class name:"));
    ClassNameLabel->setBuddy(ClassNameLineEdit);

    BaseClassLineEdit = new QLineEdit();
    BaseClassLineEdit->setValidator(Validator);

    BaseClassLabel = new QLabel(tr("Base class:"));
    BaseClassLabel->setBuddy(BaseClassLineEdit);

    HeaderOnlyCheckBox = new QCheckBox(tr("Header only"));

    NoCopyCheckBox      = new QCheckBox(tr("No"));
    DefaultCopyCheckBox = new QCheckBox(tr("Default"));
    NoMoveCheckBox      = new QCheckBox(tr("No"));
    DefaultMoveCheckBox = new QCheckBox(tr("Default"));

    connect(NoCopyCheckBox     , &QCheckBox::toggled, this, &FClassInfoPage::UncheckDefaultCopy);
    connect(DefaultCopyCheckBox, &QCheckBox::toggled, this, &FClassInfoPage::UncheckNoCopy);
    connect(NoMoveCheckBox     , &QCheckBox::toggled, this, &FClassInfoPage::UncheckDefaultMove);
    connect(DefaultMoveCheckBox, &QCheckBox::toggled, this, &FClassInfoPage::UncheckNoMove);

    registerField("ClassName*" , ClassNameLineEdit);
    registerField("BaseClass"  , BaseClassLineEdit);
    registerField("HeaderOnly" , HeaderOnlyCheckBox);
    registerField("NoCopy"     , NoCopyCheckBox);
    registerField("NoMove"     , NoMoveCheckBox);
    registerField("DefaultCopy", DefaultCopyCheckBox);
    registerField("DefaultMove", DefaultMoveCheckBox);

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

    Layout = new QGridLayout();
    Layout->addWidget(ClassNameLabel    , 0, 0);
    Layout->addWidget(ClassNameLineEdit , 0, 1);
    Layout->addWidget(BaseClassLabel    , 1, 0);
    Layout->addWidget(BaseClassLineEdit , 1, 1);
    Layout->addWidget(HeaderOnlyCheckBox, 2, 0, 1, 2);
    Layout->addWidget(CopyGroupBox      , 3, 0, 1, 2);
    Layout->addWidget(MoveGroupBox      , 4, 0, 1, 2);

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























































