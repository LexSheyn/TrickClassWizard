#ifndef FWIZARDSETTINGS_H
#define FWIZARDSETTINGS_H

#include <QByteArray>
#include <QString>
#include <QFile>
#include <QDir>
#include <QMessageBox>
#include <QTextStream>
#include <QVector>

enum EWizardFileError
{
      WIZARD_SUCCESS
    , WIZARD_DIRECTORY_DOESNT_EXIST
    , WIZARD_CANT_OPEN_FILE
};

class FWizardSettings
{
public:

    struct Settings_T
    {
        QByteArray ProjectDirectory;
        QByteArray NestedDirectory;
        QByteArray HeaderSubdirectory;
        QByteArray SourceSubdirectory;
        QByteArray Namespace;
        QString    ErrorString;
        bool       PragmaGuard;
        bool       DefineGuard;
    };

    static bool             Save (Settings_T* Settings);
    static EWizardFileError Load (Settings_T* Settings);
};

#endif // FWIZARDSETTINGS_H
