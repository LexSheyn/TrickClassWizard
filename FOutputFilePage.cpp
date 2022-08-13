#include "FOutputFilePage.h"

FOutputFilePage::FOutputFilePage(QWidget* Parent)
    : QWizardPage (Parent)
{
    setTitle(tr("Output files"));
    setSubTitle(tr("Specify file names and directories."));
    //setPixmap(QWizard::LogoPixmap, QPixmap(":/images/logo3.png"));

    // Directories:

    ProjectDirectoryLineEdit = new QLineEdit();

    connect(ProjectDirectoryLineEdit, &QLineEdit::textEdited, this, &FOutputFilePage::SetProjectDirectoryString);

    ProjectDirectoryLabel = new QLabel(tr("Project directory:"));
    ProjectDirectoryLabel->setBuddy(ProjectDirectoryLineEdit);

    ProjectDirectoryPushButton = new QPushButton(tr("Browse..."), this);
    ProjectDirectoryPushButton->setDefault(false);

    connect(ProjectDirectoryPushButton, &QPushButton::clicked, this, &FOutputFilePage::BrowseProject);

    NestedDirectoryLineEdit = new QLineEdit();

    connect(NestedDirectoryLineEdit, &QLineEdit::textEdited, this, &FOutputFilePage::SetNestedDirectoryString);

    NestedDirectoryLabel = new QLabel(tr("Nested directory"));
    NestedDirectoryLabel->setBuddy(NestedDirectoryLineEdit);

    ProjectLayout = new QGridLayout();
    ProjectLayout->addWidget(ProjectDirectoryLabel     , 0, 0);
    ProjectLayout->addWidget(ProjectDirectoryLineEdit  , 0, 1);
    ProjectLayout->addWidget(ProjectDirectoryPushButton, 0, 2);
    ProjectLayout->addWidget(NestedDirectoryLabel      , 1, 0);
    ProjectLayout->addWidget(NestedDirectoryLineEdit   , 1, 1);

    ProjectGroupBox = new QGroupBox(tr("Project"));
    ProjectGroupBox->setLayout(ProjectLayout);

    // Header:

    HeaderSubdirectoryLineEdit = new QLineEdit();

    connect(HeaderSubdirectoryLineEdit, &QLineEdit::textEdited, this, &FOutputFilePage::SetHeaderSubdirectoryString);

    HeaderSubdirectoryString = "include";

    HeaderSubdirectoryLabel = new QLabel(tr("Header subdirectory:"));
    HeaderSubdirectoryLabel->setBuddy(HeaderSubdirectoryLineEdit);

    HeaderLineEdit = new QLineEdit();

    HeaderLabel = new QLabel(tr("Header name:"));
    HeaderLabel->setBuddy(HeaderLineEdit);

    HeaderLayout = new QGridLayout();
    HeaderLayout->addWidget(HeaderSubdirectoryLabel   , 0, 0);
    HeaderLayout->addWidget(HeaderSubdirectoryLineEdit, 0, 1);
    HeaderLayout->addWidget(HeaderLabel               , 1, 0);
    HeaderLayout->addWidget(HeaderLineEdit            , 1, 1);

    HeaderGroupBox = new QGroupBox(tr("Header"));
    HeaderGroupBox->setLayout(HeaderLayout);

    // Source:

    SourceSubdirectoryLineEdit = new QLineEdit();

    connect(SourceSubdirectoryLineEdit, &QLineEdit::textEdited, this, &FOutputFilePage::SetSourceSubdirectoryString);

    SourceSubdirectoryString = "src";

    SourceSubdirectoryLabel = new QLabel(tr("Source subdirectory:"));
    SourceSubdirectoryLabel->setBuddy(SourceSubdirectoryLineEdit);

    SourceLineEdit = new QLineEdit();

    SourceLabel = new QLabel(tr("Source name:"));
    SourceLabel->setBuddy(SourceLineEdit);

    SourceLayout = new QGridLayout();
    SourceLayout->addWidget(SourceSubdirectoryLabel   , 0, 0);
    SourceLayout->addWidget(SourceSubdirectoryLineEdit, 0, 1);
    SourceLayout->addWidget(SourceLabel               , 1, 0);
    SourceLayout->addWidget(SourceLineEdit            , 1, 1);

    SourceGroupBox = new QGroupBox(tr("Source"));
    SourceGroupBox->setLayout(SourceLayout);

    // Page composing:

    registerField("ProjectDirectory"  , ProjectDirectoryLineEdit);
    registerField("NestedDirectory"   , NestedDirectoryLineEdit);
    registerField("HeaderSubdirectory", HeaderSubdirectoryLineEdit);
    registerField("HeaderName"        , HeaderLineEdit);
    registerField("SourceSubdirectory", SourceSubdirectoryLineEdit);
    registerField("SourceName"        , SourceLineEdit);

    Layout = new QVBoxLayout();
    Layout->addWidget(ProjectGroupBox);
    Layout->addWidget(HeaderGroupBox);
    Layout->addWidget(SourceGroupBox);

    setLayout(Layout);

    t3d::FEvent::SettingsLoaded.Subscribe(this, &FOutputFilePage::OnSettingsLoaded);
}

FOutputFilePage::~FOutputFilePage()
{
    t3d::FEvent::SettingsLoaded.Unsubscribe(&FOutputFilePage::OnSettingsLoaded);
}

QString FOutputFilePage::GetHeaderDirectory()
{
    return ProjectDirectoryLineEdit->text() + '/' + HeaderSubdirectoryLineEdit->text() + '/' + NestedDirectoryLineEdit->text() + '/';
}

QString FOutputFilePage::GetSourceDirectory()
{
    return ProjectDirectoryLineEdit->text() + '/' + SourceSubdirectoryLineEdit->text() + '/' + NestedDirectoryLineEdit->text() + '/';
}

void FOutputFilePage::initializePage()
{
    // Directories:

    ProjectDirectoryLineEdit->setText(ProjectDirectoryString);
    NestedDirectoryLineEdit ->setText(NestedDirectoryString);

    // Header:

    HeaderSubdirectoryLineEdit->setText(HeaderSubdirectoryString);

    QString ClassName = field("ClassName").toString();

    HeaderLineEdit ->setText(ClassName + ".h");

    // Source:

    SourceSubdirectoryLineEdit->setText(SourceSubdirectoryString);

    SourceLineEdit->setText(ClassName + ".cpp");

    SourceGroupBox->setVisible(!field("HeaderOnly").toBool());
}

void FOutputFilePage::BrowseProject()
{
    QString Path;

    if (ProjectDirectoryLineEdit->text().isEmpty())
    {
        Path = QDir::rootPath();
    }
    else
    {
        Path = ProjectDirectoryLineEdit->text();
    }

    QString Directory = QFileDialog::getExistingDirectory(this, tr("Project directory"), Path);

    if (Directory.isEmpty() == false)
    {
        ProjectDirectoryLineEdit->setText(Directory);
    }
}

void FOutputFilePage::SetProjectDirectoryString(const QString& Text)
{
    ProjectDirectoryString = Text;
}

void FOutputFilePage::SetNestedDirectoryString(const QString& Text)
{
    NestedDirectoryString = Text;
}

void FOutputFilePage::SetHeaderSubdirectoryString(const QString &Text)
{
    HeaderSubdirectoryString = Text;
}

void FOutputFilePage::SetSourceSubdirectoryString(const QString &Text)
{
    SourceSubdirectoryString = Text;
}

t3d::EPropagation FOutputFilePage::OnSettingsLoaded(FWizardSettings::Settings_T Settings)
{
    ProjectDirectoryString    = Settings.ProjectDirectory;
    NestedDirectoryString     = Settings.NestedDirectory;
    HeaderSubdirectoryString  = Settings.HeaderSubdirectory;
    SourceSubdirectoryString  = Settings.SourceSubdirectory;

    return t3d::EPropagation::Continue;
}









































