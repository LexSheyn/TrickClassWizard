#include "FClassWizard.h"

FClassWizard::FClassWizard(QWidget* Parent)
    : QWizard (Parent)
{
    setWindowTitle(tr("Trick class wizard"));
    setPixmap(QWizard::BannerPixmap    , QPixmap(":/images/banner.png"));
    setPixmap(QWizard::BackgroundPixmap, QPixmap(":/images/background.png"));

    connect(button(FinishButton), &QAbstractButton::pressed, this, &FClassWizard::CreateClass);

    ClassInfoPage  = new FClassInfoPage();
    CodeStylePage  = new FCodeStylePage();
    OutputFilePage = new FOutputFilePage();

    addPage(ClassInfoPage);
    addPage(CodeStylePage);
    addPage(OutputFilePage);

    LoadSettings();
}

void FClassWizard::CreateClass()
{
    FClassData ClassData{};

    ClassData.ClassName        = field("ClassName")       .toByteArray();
    ClassData.BaseClass        = field("BaseClass")       .toByteArray();
    ClassData.ProjectDirectory = field("ProjectDirectory").toString();
    ClassData.NestedDirectory  = field("NestedDirectory") .toString();
    ClassData.Namespace        = field("Namespace")       .toByteArray();
    ClassData.HeaderFile       = field("HeaderName")      .toString();
    ClassData.SourceFile       = field("SourceName")      .toString();

    if (ClassData.ProjectDirectory.isEmpty())
    {
        FMessageBox::Warning(this, __FUNCTION__, "Need to specify project directory where files will be created!");

        return;
    }

    CreateHeader(ClassData);
    CreateSource(ClassData);

    SaveSettings();
}

void FClassWizard::CreateHeader(FClassData& ClassData)
{
    QByteArray Data;

    if (field("PragmaGuard").toBool())
    {
        Data += FCodeStylePage::GetPragmaGuard();
        Data += "\n\n";
    }
    else if (field("DefineGuard").toBool())
    {
        Data += "#ifndef " + FCodeStylePage::GetDefineGuardName(ClassData.ClassName) + '\n';
        Data += FCodeStylePage::GetDefineGuard(ClassData.ClassName);
        Data += "\n\n";
    }

    if (ClassData.BaseClass.isEmpty() == false)
    {
        QString BaseClassName = "#include ";
        BaseClassName += '"';
        BaseClassName += ClassData.BaseClass;
        BaseClassName += ".h";
        BaseClassName += '"';
        BaseClassName += '\n';

        Data += BaseClassName.toLatin1();
        Data += '\n';
    }

    Data += FCodeStylePage::GetNamespace(ClassData.Namespace) + '\n';
    Data += "{\n";
    Data += '\t';
    Data += "class " + ClassData.ClassName;

    if (ClassData.BaseClass.isEmpty() == false)
    {
        Data += " : public " + ClassData.BaseClass;
    }

    Data += '\n';
    Data += "\t{\n";

    Data += "\tpublic:\n\n";
    Data += "\t\t//\n\n";

    if (field("NoCopy").toBool())
    {
        Data += "\t\t" + FCodeStylePage::GetNoCopyMacro(ClassData.ClassName) + '\n';
    }
    else if (field("DefaultCopy").toBool())
    {
        Data += "\t\t" + FCodeStylePage::GetDefaultCopyMacro(ClassData.ClassName) + '\n';
    }

    if (field("NoMove").toBool())
    {
        Data += "\t\t" + FCodeStylePage::GetNoMoveMacro(ClassData.ClassName) + '\n';
    }
    else if (field("DefaultMove").toBool())
    {
        Data += "\t\t" + FCodeStylePage::GetDefaultMoveMacro(ClassData.ClassName) + '\n';
    }

    Data += "\t};\n\n";
    Data += "} // " + FCodeStylePage::GetNamespace(ClassData.Namespace) + '\n';

    if (field("DefineGuard").toBool())
    {
        Data += '\n';
        Data += "#endif // " + FCodeStylePage::GetDefineGuardName(ClassData.ClassName);
    }

    QDir HeaderDirectory(OutputFilePage->GetHeaderDirectory());

    if (HeaderDirectory.exists() == false)
    {
        HeaderDirectory.mkpath(".");
    }

    QFile HeaderFile(OutputFilePage->GetHeaderDirectory() + field("HeaderName").toString());

    if (HeaderFile.open(QFile::WriteOnly | QFile::Text) == false)
    {
        FMessageBox::Error(this, __FUNCTION__, QObject::tr("Cannot write file %1:\n%2").arg(HeaderFile.fileName()).arg(HeaderFile.errorString()));

        return;
    }

    HeaderFile.write(Data);
    HeaderFile.close();
}

void FClassWizard::CreateSource(FClassData& ClassData)
{
    if (field("HeaderOnly").toBool())
    {
        return;
    }

    QByteArray Data;

    QString IncludePCH = "#include ";
    IncludePCH += '"';
    IncludePCH += "PCH/t3dpch.h";
    IncludePCH += '"';

    QString IncludeClass = "#include ";
    IncludeClass += '"';
    IncludeClass += ClassData.ClassName;
    IncludeClass += ".h";
    IncludeClass += '"';

    Data += IncludePCH.toLatin1() + '\n';
    Data += IncludeClass.toLatin1() + '\n';
    Data += '\n';

    Data += FCodeStylePage::GetNamespace(ClassData.Namespace) + '\n';
    Data += "{\n";
    Data += "} // " + FCodeStylePage::GetNamespace(ClassData.Namespace) + '\n';

    QDir SourceDirectory(OutputFilePage->GetSourceDirectory());

    if (SourceDirectory.exists() == false)
    {
        SourceDirectory.mkpath(".");
    }

    QFile SourceFile(OutputFilePage->GetSourceDirectory() + field("SourceName").toString());

    if (SourceFile.open(QFile::WriteOnly | QFile::Text) == false)
    {
        FMessageBox::Error(this, __FUNCTION__, QObject::tr("Cannot write file %1:\n%2").arg(SourceFile.fileName()).arg(SourceFile.errorString()));

        return;
    }

    SourceFile.write(Data);
    SourceFile.close();
}

void FClassWizard::SaveSettings()
{
    FWizardSettings::Settings_T Settings;

    Settings.ProjectDirectory   = field("ProjectDirectory")  .toByteArray();
    Settings.NestedDirectory    = field("NestedDirectory")   .toByteArray();
    Settings.HeaderSubdirectory = field("HeaderSubdirectory").toByteArray();
    Settings.SourceSubdirectory = field("SourceSubdirectory").toByteArray();
    Settings.Namespace          = field("Namespace")         .toByteArray();
    Settings.PragmaGuard        = field("PragmaGuard")       .toBool();
    Settings.DefineGuard        = field("DefineGuard")       .toBool();

    if (FWizardSettings::Save(&Settings) == false)
    {
        FMessageBox::Error(this, __FUNCTION__, Settings.ErrorString);

        return;
    }

    t3d::FEvent::SettingsSaved.Invoke(Settings);
}

void FClassWizard::LoadSettings()
{
    FWizardSettings::Settings_T Settings;

    auto Result = FWizardSettings::Load(&Settings);

    if (Result == WIZARD_CANT_OPEN_FILE)
    {
        FMessageBox::Error(this, __FUNCTION__, Settings.ErrorString);

        return;
    }
    else if (Result == WIZARD_DIRECTORY_DOESNT_EXIST)
    {
        return;
    }

    t3d::FEvent::SettingsLoaded.Invoke(Settings);
}





















































