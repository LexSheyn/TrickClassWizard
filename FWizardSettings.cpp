#include "FWizardSettings.h"

QString ProjectStartToken    = "<project_directory>";
QString ProjectFinishToken   = "</project_directory>";
QString NestedStartToken     = "<nested_directory>";
QString NestedFinishToken    = "</nested_directory>";
QString HeaderStartToken     = "<header_subdirectory>";
QString HeaderFinishToken    = "</header_subdirectory>";
QString SourceStartToken     = "<source_subdirectory>";
QString SourceFinishToken    = "</source_subdirectory>";
QString NamespaceStartToken  = "<namespace>";
QString NamespaceFinishToken = "</namespace>";
QString PragmaStartToken     = "<pragma_guard>";
QString PragmaFinishToken    = "</pragma_guard>";
QString DefineStartToken     = "<define_guard>";
QString DefineFinishToken    = "</define_guard>";

bool FWizardSettings::Save(Settings_T* Settings)
{
    QByteArray Data;

    Data += ProjectStartToken.toLatin1() + Settings->ProjectDirectory + ProjectFinishToken.toLatin1();
    Data += '\n';
    Data += NestedStartToken.toLatin1() + Settings->NestedDirectory + NestedFinishToken.toLatin1();
    Data += '\n';
    Data += HeaderStartToken.toLatin1() + Settings->HeaderSubdirectory + HeaderFinishToken.toLatin1();
    Data += '\n';
    Data += SourceStartToken.toLatin1() + Settings->SourceSubdirectory + SourceFinishToken.toLatin1();
    Data += '\n';
    Data += NamespaceStartToken.toLatin1() + Settings->Namespace + NamespaceFinishToken.toLatin1();
    Data += '\n';
    Data += PragmaStartToken.toLatin1() + QString::number(Settings->PragmaGuard).toLatin1() + PragmaFinishToken.toLatin1();
    Data += '\n';
    Data += DefineStartToken.toLatin1() + QString::number(Settings->DefineGuard).toLatin1() + DefineFinishToken.toLatin1();

    QString SettigsDirectoryString = QDir::currentPath() + "/Settings/";

    QDir SettingsDirectory(SettigsDirectoryString);

    if (SettingsDirectory.exists() == false)
    {
        SettingsDirectory.mkpath(".");
    }

    QFile SettingsFile(SettigsDirectoryString + "wizard_settings.cfg");

    if (SettingsFile.open(QFile::WriteOnly | QFile::Text) == false)
    {
        (*Settings).ErrorString = QObject::tr("Cannot write file %1:\n%2").arg(SettingsFile.fileName()).arg(SettingsFile.errorString());

        return false;
    }

    SettingsFile.write(Data);
    SettingsFile.close();

    return true;
}

EWizardFileError FWizardSettings::Load(Settings_T* Settings)
{
    QString SettigsDirectoryString = QDir::currentPath() + "/Settings/";

    QDir SettingsDirectory(SettigsDirectoryString);

    if (SettingsDirectory.exists() == false)
    {
        return WIZARD_DIRECTORY_DOESNT_EXIST;
    }

    QFile SettingsFile(SettigsDirectoryString + "wizard_settings.cfg");

    if (SettingsFile.open(QFile::ReadOnly | QFile::Text) == false)
    {
        (*Settings).ErrorString = QObject::tr("Cannot read file %1:\n%2").arg(SettingsFile.fileName()).arg(SettingsFile.errorString());

        return WIZARD_CANT_OPEN_FILE;
    }

    QTextStream Input(&SettingsFile);

    QVector<QByteArray> FileContents;

    while(Input.atEnd() == false)
    {
        FileContents.push_back(Input.readLine().toLatin1());
    }

    SettingsFile.close();

    for (auto& String : FileContents)
    {
        if (String.startsWith(ProjectStartToken.toStdString().c_str()) && String.endsWith(ProjectFinishToken.toStdString().c_str()))
        {
            (*Settings).ProjectDirectory = String.mid(ProjectStartToken.size(), String.size() - (ProjectStartToken.size() + ProjectFinishToken.size()));
        }
        else if (String.startsWith(NestedStartToken.toStdString().c_str()) && String.endsWith(NestedFinishToken.toStdString().c_str()))
        {
            (*Settings).NestedDirectory = String.mid(NestedStartToken.size(), String.size() - (NestedStartToken.size() + NestedFinishToken.size()));
        }
        else if (String.startsWith(HeaderStartToken.toStdString().c_str()) && String.endsWith(HeaderFinishToken.toStdString().c_str()))
        {
            (*Settings).HeaderSubdirectory = String.mid(HeaderStartToken.size(), String.size() - (HeaderStartToken.size() + HeaderFinishToken.size()));
        }
        else if (String.startsWith(SourceStartToken.toStdString().c_str()) && String.endsWith(SourceFinishToken.toStdString().c_str()))
        {
            (*Settings).SourceSubdirectory = String.mid(SourceStartToken.size(), String.size() - (SourceStartToken.size() + SourceFinishToken.size()));
        }
        else if (String.startsWith(NamespaceStartToken.toStdString().c_str()) && String.endsWith(NamespaceFinishToken.toStdString().c_str()))
        {
            (*Settings).Namespace = String.mid(NamespaceStartToken.size(), String.size() - (NamespaceStartToken.size() + NamespaceFinishToken.size()));
        }
        else if (String.startsWith(PragmaStartToken.toStdString().c_str()) && String.endsWith(PragmaFinishToken.toStdString().c_str()))
        {
            QString Substring = String.mid(PragmaStartToken.size(), String.size() - (PragmaStartToken.size() + PragmaFinishToken.size()));

            (*Settings).PragmaGuard = static_cast<bool>(Substring.toInt());
        }
        else if (String.startsWith(DefineStartToken.toStdString().c_str()) && String.endsWith(DefineFinishToken.toStdString().c_str()))
        {
            QString Substring = String.mid(DefineStartToken.size(), String.size() - (DefineStartToken.size() + DefineFinishToken.size()));

            (*Settings).DefineGuard = static_cast<bool>(Substring.toInt());
        }
    }

    return WIZARD_SUCCESS;
}
