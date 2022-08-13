#include "FClassWizard.h"

FClassWizard::FClassWizard(QWidget* Parent)
    : QWizard (Parent)
{
    setStyleSheet("QWizard { background-color: #FFFFFF }");
    setPixmap(QWizard::LogoPixmap, QPixmap(":Wizard_64_L.png"));

    setWindowTitle(tr("Trick class wizard"));
    setWizardStyle(QWizard::ModernStyle);

    connect(button(FinishButton), &QAbstractButton::pressed, this, &FClassWizard::CreateClass);

    ClassInfoPage  = new FClassInfoPage();
    CodeStylePage  = new FCodeStylePage();
    OutputFilePage = new FOutputFilePage();

    addPage(ClassInfoPage);
    addPage(CodeStylePage);
    addPage(OutputFilePage);

    setMinimumSize(500, 500); // PAGE SIZE HOT FIX

    LoadSettings();
}

void FClassWizard::CreateClass()
{
    FClassData ClassData{};

    ClassData.ClassName     = field("ClassName")    .toByteArray();
    ClassData.BaseClassName = field("BaseClassName").toByteArray();
    ClassData.ProjectPath   = field("ProjectPath")  .toString();
    ClassData.NestedPath    = field("NestedPath")   .toString();
    ClassData.PCHSubpath    = field("PCHSubpath")   .toString();
    ClassData.PCHName       = field("PCHName")      .toString();
    ClassData.Namespace     = field("Namespace")    .toByteArray();
    ClassData.HeaderName    = field("HeaderName")   .toString();
    ClassData.SourceName    = field("SourceName")   .toString();

    if (ClassData.ProjectPath.isEmpty())
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

    if (ClassData.BaseClassName.isEmpty() == false)
    {
        QString BaseClassName = "#include ";
        BaseClassName += '"';
        BaseClassName += ClassData.BaseClassName;
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

    if (ClassData.BaseClassName.isEmpty() == false)
    {
        Data += " : public " + ClassData.BaseClassName;
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

    QDir HeaderDirectory(OutputFilePage->GetHeaderPath());

    if (HeaderDirectory.exists() == false)
    {
        HeaderDirectory.mkpath(".");
    }

    QFile HeaderFile(OutputFilePage->GetHeaderPath() + field("HeaderName").toString());

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

    if (field("PCH").toBool())
    {
        QString IncludePCH = "#include ";
        IncludePCH += '"';

        if (ClassData.PCHSubpath.isEmpty() == false)
        {
            IncludePCH += ClassData.PCHSubpath + '/';
        }

        IncludePCH += ClassData.PCHName;
        IncludePCH += '"';

        Data += IncludePCH.toLatin1() + '\n';
    }

    QString IncludeClass = "#include ";
    IncludeClass += '"';

    if (ClassData.NestedPath.isEmpty() == false)
    {
        IncludeClass += ClassData.NestedPath + '/';
    }

    IncludeClass += ClassData.ClassName;
    IncludeClass += ".h";
    IncludeClass += '"';

    Data += IncludeClass.toLatin1() + '\n';
    Data += '\n';

    Data += FCodeStylePage::GetNamespace(ClassData.Namespace) + '\n';
    Data += "{\n";
    Data += "} // " + FCodeStylePage::GetNamespace(ClassData.Namespace) + '\n';

    QDir SourceDirectory(OutputFilePage->GetSourcePath());

    if (SourceDirectory.exists() == false)
    {
        SourceDirectory.mkpath(".");
    }

    QFile SourceFile(OutputFilePage->GetSourcePath() + field("SourceName").toString());

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

    Settings.ProjectPath   = field("ProjectPath")  .toByteArray();
    Settings.NestedPath    = field("NestedPath")   .toByteArray();
    Settings.b_PCH         = field("PCH")          .toBool();
    Settings.PCHSubpath    = field("PCHSubpath")   .toByteArray();
    Settings.PCHName       = field("PCHName")      .toByteArray();
    Settings.HeaderSubpath = field("HeaderSubpath").toByteArray();
    Settings.SourceSubpath = field("SourceSubpath").toByteArray();
    Settings.Namespace     = field("Namespace")    .toByteArray();
    Settings.b_PragmaGuard = field("PragmaGuard")  .toBool();
    Settings.b_DefineGuard = field("DefineGuard")  .toBool();

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





















































