#include "FWizardSettings.h"

QString ProjectToken_S     = "<project_directory>";
QString ProjectToken_F    = "</project_directory>";
QString NestedToken_S      = "<nested_directory>";
QString NestedToken_F     = "</nested_directory>";
QString PCHToken_S         = "<pch>";
QString PCHToken_F        = "</pch>";
QString PCHSubpathToken_S  = "<pch_subpath>";
QString PCHSubpathToken_F = "</pch_subpath>";
QString PCHNameToken_S     = "<pch_name>";
QString PCHNameToken_F    = "</pch_name>";
QString HeaderToken_S      = "<header_subdirectory>";
QString HeaderToken_F     = "</header_subdirectory>";
QString SourceToken_S      = "<source_subdirectory>";
QString SourceToken_F     = "</source_subdirectory>";
QString NamespaceToken_S   = "<namespace>";
QString NamespaceToken_F  = "</namespace>";
QString PragmaToken_S      = "<pragma_guard>";
QString PragmaToken_F     = "</pragma_guard>";
QString DefineToken_S      = "<define_guard>";
QString DefineToken_F     = "</define_guard>";

bool FWizardSettings::Save(Settings_T* Settings)
{
    QByteArray Data;

    Data += ProjectToken_S.toLatin1() + Settings->ProjectPath + ProjectToken_F.toLatin1();
    Data += '\n';
    Data += NestedToken_S.toLatin1() + Settings->NestedPath + NestedToken_F.toLatin1();
    Data += '\n';
    Data += PCHToken_S.toLatin1() + QString::number(Settings->b_PCH).toLatin1() + PCHToken_F.toLatin1();
    Data += '\n';
    Data += PCHSubpathToken_S.toLatin1() + Settings->PCHSubpath + PCHSubpathToken_F.toLatin1();
    Data += '\n';
    Data += PCHNameToken_S.toLatin1() + Settings->PCHName + PCHNameToken_F.toLatin1();
    Data += '\n';
    Data += HeaderToken_S.toLatin1() + Settings->HeaderSubpath + HeaderToken_F.toLatin1();
    Data += '\n';
    Data += SourceToken_S.toLatin1() + Settings->SourceSubpath + SourceToken_F.toLatin1();
    Data += '\n';
    Data += NamespaceToken_S.toLatin1() + Settings->Namespace + NamespaceToken_F.toLatin1();
    Data += '\n';
    Data += PragmaToken_S.toLatin1() + QString::number(Settings->b_PragmaGuard).toLatin1() + PragmaToken_F.toLatin1();
    Data += '\n';
    Data += DefineToken_S.toLatin1() + QString::number(Settings->b_DefineGuard).toLatin1() + DefineToken_F.toLatin1();

    QString SettigsDirectoryString = QDir::currentPath() + "/Settings/";

    QDir SettingsDirectory(SettigsDirectoryString);

    if (SettingsDirectory.exists() == false)
    {
        SettingsDirectory.mkpath(".");
    }

    QFile SettingsFile(SettigsDirectoryString + "wizard_settings.cfg");

    if (SettingsFile.open(QFile::WriteOnly | QFile::Text) == false)
    {
        Settings->ErrorString = QObject::tr("Cannot write file %1:\n%2").arg(SettingsFile.fileName()).arg(SettingsFile.errorString());

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
        Settings->ErrorString = QObject::tr("Cannot read file %1:\n%2").arg(SettingsFile.fileName()).arg(SettingsFile.errorString());

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
        if (String.startsWith(ProjectToken_S.toStdString().c_str()) && String.endsWith(ProjectToken_F.toStdString().c_str()))
        {
            Settings->ProjectPath = String.mid(ProjectToken_S.size(), String.size() - (ProjectToken_S.size() + ProjectToken_F.size()));
        }
        else if (String.startsWith(NestedToken_S.toStdString().c_str()) && String.endsWith(NestedToken_F.toStdString().c_str()))
        {
            Settings->NestedPath = String.mid(NestedToken_S.size(), String.size() - (NestedToken_S.size() + NestedToken_F.size()));
        }
        else if (String.startsWith(PCHToken_S.toStdString().c_str()) && String.endsWith(PCHToken_F.toStdString().c_str()))
        {
            QString Substring = String.mid(PCHToken_S.size(), String.size() - (PCHToken_S.size() + PCHToken_F.size()));

            Settings->b_PCH = static_cast<bool>(Substring.toInt());
        }
        else if (String.startsWith(PCHSubpathToken_S.toStdString().c_str()) && String.endsWith(PCHSubpathToken_F.toStdString().c_str()))
        {
            Settings->PCHSubpath = String.mid(PCHSubpathToken_S.size(), String.size() - (PCHSubpathToken_S.size() + PCHSubpathToken_F.size()));
        }
        else if (String.startsWith(PCHNameToken_S.toStdString().c_str()) && String.endsWith(PCHNameToken_F.toStdString().c_str()))
        {
            Settings->PCHName = String.mid(PCHNameToken_S.size(), String.size() - (PCHNameToken_S.size() + PCHNameToken_F.size()));
        }
        else if (String.startsWith(HeaderToken_S.toStdString().c_str()) && String.endsWith(HeaderToken_F.toStdString().c_str()))
        {
            Settings->HeaderSubpath = String.mid(HeaderToken_S.size(), String.size() - (HeaderToken_S.size() + HeaderToken_F.size()));
        }
        else if (String.startsWith(SourceToken_S.toStdString().c_str()) && String.endsWith(SourceToken_F.toStdString().c_str()))
        {
            Settings->SourceSubpath = String.mid(SourceToken_S.size(), String.size() - (SourceToken_S.size() + SourceToken_F.size()));
        }
        else if (String.startsWith(NamespaceToken_S.toStdString().c_str()) && String.endsWith(NamespaceToken_F.toStdString().c_str()))
        {
            Settings->Namespace = String.mid(NamespaceToken_S.size(), String.size() - (NamespaceToken_S.size() + NamespaceToken_F.size()));
        }
        else if (String.startsWith(PragmaToken_S.toStdString().c_str()) && String.endsWith(PragmaToken_F.toStdString().c_str()))
        {
            QString Substring = String.mid(PragmaToken_S.size(), String.size() - (PragmaToken_S.size() + PragmaToken_F.size()));

            Settings->b_PragmaGuard = static_cast<bool>(Substring.toInt());
        }
        else if (String.startsWith(DefineToken_S.toStdString().c_str()) && String.endsWith(DefineToken_F.toStdString().c_str()))
        {
            QString Substring = String.mid(DefineToken_S.size(), String.size() - (DefineToken_S.size() + DefineToken_F.size()));

            Settings->b_DefineGuard = static_cast<bool>(Substring.toInt());
        }
    }

    return WIZARD_SUCCESS;
}
