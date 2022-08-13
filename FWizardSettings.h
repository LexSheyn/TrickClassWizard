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
        QByteArray ProjectPath;
        QByteArray NestedPath;
        bool       b_PCH;
        QByteArray PCHSubpath;
        QByteArray PCHName;
        QByteArray HeaderSubpath;
        QByteArray SourceSubpath;
        QByteArray Namespace;
        QString    ErrorString;
        bool       b_PragmaGuard;
        bool       b_DefineGuard;
    };

    static bool             Save (Settings_T* Settings);
    static EWizardFileError Load (Settings_T* Settings);
};

#endif // FWIZARDSETTINGS_H
