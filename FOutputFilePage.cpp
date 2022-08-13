#include "FOutputFilePage.h"

FOutputFilePage::FOutputFilePage(QWidget* Parent)
    : QWizardPage (Parent)
{
    setTitle(tr("Output files"));
    setSubTitle(tr("\nSpecify file names and directories."));

    // Directories:

    ProjectPathLineEdit = new QLineEdit();

    connect(ProjectPathLineEdit, &QLineEdit::textEdited, this, &FOutputFilePage::SetProjectPathString);

    ProjectPathLabel = new QLabel(tr("Path:"));
    ProjectPathLabel->setBuddy(ProjectPathLineEdit);

    ProjectPathPushButton = new QPushButton(tr("Browse..."), this);
    ProjectPathPushButton->setDefault(false);

    connect(ProjectPathPushButton, &QPushButton::clicked, this, &FOutputFilePage::BrowseProject);

    NestedPathLineEdit = new QLineEdit();

    connect(NestedPathLineEdit, &QLineEdit::textEdited, this, &FOutputFilePage::SetNestedPathString);

    NestedPathLabel = new QLabel(tr("Nested path:"));
    NestedPathLabel->setBuddy(NestedPathLineEdit);

    ProjectLayout = new QGridLayout();
    ProjectLayout->addWidget(ProjectPathLabel     , 0, 0);
    ProjectLayout->addWidget(ProjectPathLineEdit  , 0, 1);
    ProjectLayout->addWidget(ProjectPathPushButton, 0, 2);
    ProjectLayout->addWidget(NestedPathLabel      , 1, 0);
    ProjectLayout->addWidget(NestedPathLineEdit   , 1, 1);

    ProjectGroupBox = new QGroupBox(tr("Project"));
    ProjectGroupBox->setLayout(ProjectLayout);

    // PCH:

    PCHCheckBox = new QCheckBox(tr("Precompiled headers"));

    b_PCH = true;

    PCHSubpathLineEdit = new QLineEdit();

    PCHSubpathLabel = new QLabel(tr("Subpath:"));
    PCHSubpathLabel->setBuddy(PCHSubpathLineEdit);

    PCHSubpathString = "PCH";

    PCHNameLineEdit = new QLineEdit();

    PCHNameLabel = new QLabel(tr("Name:"));
    PCHNameLabel->setBuddy(PCHNameLineEdit);

    PCHNameString = "t3dpch.h";

    connect(PCHCheckBox, &QCheckBox::toggled, PCHSubpathLineEdit, &QLineEdit::setEnabled );
    connect(PCHCheckBox, &QCheckBox::toggled, PCHSubpathLabel   , &QLabel::setEnabled);
    connect(PCHSubpathLineEdit, &QLineEdit::textEdited, this, &FOutputFilePage::SetPCHSubpathString);

    connect(PCHCheckBox, &QCheckBox::toggled, PCHNameLineEdit   , &QLineEdit::setEnabled);
    connect(PCHCheckBox, &QCheckBox::toggled, PCHNameLabel      , &QLabel::setEnabled);
    connect(PCHNameLineEdit, &QLineEdit::textEdited, this, &FOutputFilePage::SetPCHNameString);

    PCHLayout = new QGridLayout();
    PCHLayout->addWidget(PCHSubpathLabel   , 0, 0);
    PCHLayout->addWidget(PCHSubpathLineEdit, 0, 1);
    PCHLayout->addWidget(PCHNameLabel      , 1, 0);
    PCHLayout->addWidget(PCHNameLineEdit   , 1, 1);

    PCHGroup = new QGroupBox();
    PCHGroup->setLayout(PCHLayout);

    // Header:

    HeaderSubpathLineEdit = new QLineEdit();

    connect(HeaderSubpathLineEdit, &QLineEdit::textEdited, this, &FOutputFilePage::SetHeaderSubpathString);

    HeaderSubpathString = "include";

    HeaderSubpathLabel = new QLabel(tr("Subpath:"));
    HeaderSubpathLabel->setBuddy(HeaderSubpathLineEdit);

    HeaderNameLineEdit = new QLineEdit();

    HeaderNameLabel = new QLabel(tr("Name:"));
    HeaderNameLabel->setBuddy(HeaderNameLineEdit);

    HeaderLayout = new QGridLayout();
    HeaderLayout->addWidget(HeaderSubpathLabel   , 0, 0);
    HeaderLayout->addWidget(HeaderSubpathLineEdit, 0, 1);
    HeaderLayout->addWidget(HeaderNameLabel      , 1, 0);
    HeaderLayout->addWidget(HeaderNameLineEdit   , 1, 1);

    HeaderGroupBox = new QGroupBox(tr("Header"));
    HeaderGroupBox->setLayout(HeaderLayout);

    // Source:

    SourceSubpathLineEdit = new QLineEdit();

    connect(SourceSubpathLineEdit, &QLineEdit::textEdited, this, &FOutputFilePage::SetSourceSubpathString);

    SourceSubpathString = "src";

    SourceSubpathLabel = new QLabel(tr("Subpath:"));
    SourceSubpathLabel->setBuddy(SourceSubpathLineEdit);

    SourceNameLineEdit = new QLineEdit();

    SourceNameLabel = new QLabel(tr("Name:"));
    SourceNameLabel->setBuddy(SourceNameLineEdit);

    SourceLayout = new QGridLayout();
    SourceLayout->addWidget(SourceSubpathLabel   , 0, 0);
    SourceLayout->addWidget(SourceSubpathLineEdit, 0, 1);
    SourceLayout->addWidget(SourceNameLabel      , 1, 0);
    SourceLayout->addWidget(SourceNameLineEdit   , 1, 1);

    SourceGroupBox = new QGroupBox(tr("Source"));
    SourceGroupBox->setLayout(SourceLayout);

    // Page composing:

    registerField("ProjectPath"  , ProjectPathLineEdit);
    registerField("NestedPath"   , NestedPathLineEdit);
    registerField("PCH"          , PCHCheckBox);
    registerField("PCHSubpath"   , PCHSubpathLineEdit);
    registerField("PCHName"      , PCHNameLineEdit);
    registerField("HeaderSubpath", HeaderSubpathLineEdit);
    registerField("HeaderName"   , HeaderNameLineEdit);
    registerField("SourceSubpath", SourceSubpathLineEdit);
    registerField("SourceName"   , SourceNameLineEdit);

    Layout = new QVBoxLayout();
    Layout->addWidget(ProjectGroupBox);
    Layout->addWidget(PCHCheckBox);
    Layout->addWidget(PCHGroup);
    Layout->addWidget(HeaderGroupBox);
    Layout->addWidget(SourceGroupBox);

    setLayout(Layout);

    t3d::FEvent::SettingsLoaded.Subscribe(this, &FOutputFilePage::OnSettingsLoaded);
}

FOutputFilePage::~FOutputFilePage()
{
    t3d::FEvent::SettingsLoaded.Unsubscribe(&FOutputFilePage::OnSettingsLoaded);
}

QString FOutputFilePage::GetHeaderPath()
{
    return ProjectPathLineEdit->text() + '/' + HeaderSubpathLineEdit->text() + '/' + NestedPathLineEdit->text() + '/';
}

QString FOutputFilePage::GetSourcePath()
{
    return ProjectPathLineEdit->text() + '/' + SourceSubpathLineEdit->text() + '/' + NestedPathLineEdit->text() + '/';
}

void FOutputFilePage::initializePage()
{
    // Directories:

    ProjectPathLineEdit->setText(ProjectPathString);
    NestedPathLineEdit ->setText(NestedPathString);

    // PCH:

    PCHCheckBox->setChecked(b_PCH);

    PCHSubpathLineEdit->setText(PCHSubpathString);
    PCHNameLineEdit   ->setText(PCHNameString);

    // Header:

    HeaderSubpathLineEdit->setText(HeaderSubpathString);

    QString ClassName = field("ClassName").toString();

    HeaderNameLineEdit ->setText(ClassName + ".h");

    // Source:

    SourceSubpathLineEdit->setText(SourceSubpathString);

    SourceNameLineEdit->setText(ClassName + ".cpp");

    SourceGroupBox->setVisible(!field("HeaderOnly").toBool());
}

void FOutputFilePage::BrowseProject()
{
    QString Path;

    if (ProjectPathLineEdit->text().isEmpty())
    {
        Path = QDir::rootPath();
    }
    else
    {
        Path = ProjectPathLineEdit->text();
    }

    QString Directory = QFileDialog::getExistingDirectory(this, tr("Project path"), Path);

    if (Directory.isEmpty() == false)
    {
        ProjectPathLineEdit->setText(Directory);
        ProjectPathString = ProjectPathLineEdit->text();
    }
}

void FOutputFilePage::SetProjectPathString(const QString& Text)
{
    ProjectPathString = Text;
}

void FOutputFilePage::SetNestedPathString(const QString& Text)
{
    NestedPathString = Text;
}

void FOutputFilePage::SetPCHSubpathString(const QString &Text)
{
    PCHSubpathString = Text;
}

void FOutputFilePage::SetPCHNameString(const QString &Text)
{
    PCHNameString = Text;
}

void FOutputFilePage::SetHeaderSubpathString(const QString &Text)
{
    HeaderSubpathString = Text;
}

void FOutputFilePage::SetSourceSubpathString(const QString &Text)
{
    SourceSubpathString = Text;
}

t3d::EPropagation FOutputFilePage::OnSettingsLoaded(FWizardSettings::Settings_T Settings)
{
    ProjectPathString    = Settings.ProjectPath;
    NestedPathString     = Settings.NestedPath;
    b_PCH                = Settings.b_PCH;
    PCHSubpathString     = Settings.PCHSubpath;
    PCHNameString        = Settings.PCHName;
    HeaderSubpathString  = Settings.HeaderSubpath;
    SourceSubpathString  = Settings.SourceSubpath;

    return t3d::EPropagation::Continue;
}









































