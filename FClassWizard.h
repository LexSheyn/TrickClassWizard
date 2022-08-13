#ifndef FCLASSWIZARD_H
#define FCLASSWIZARD_H

#include <QWizard>
#include <QByteArray>
#include <QDir>
#include <QFile>
#include <QString>
#include <QMessageBox>
#include <QLineEdit>
#include "FClassInfoPage.h"
#include "FCodeStylePage.h"
#include "FOutputFilePage.h"
#include "FWizardSettings.h"
#include "FMessageBox.h"
#include "FEvent.h"

struct FClassData
{
    QByteArray ClassName;
    QByteArray BaseClass;
    QString    ProjectDirectory;
    QString    NestedDirectory;
    QByteArray Namespace;
    QString    HeaderFile;
    QString    SourceFile;
};

class FClassWizard : public QWizard
{
    Q_OBJECT

public:

    FClassWizard (QWidget* Parent = nullptr);

private slots:

    void CreateClass  ();
    void CreateHeader (FClassData& ClassData);
    void CreateSource (FClassData& ClassData);
    void SaveSettings ();
    void LoadSettings ();

private:

    FClassInfoPage*  ClassInfoPage;
    FCodeStylePage*  CodeStylePage;
    FOutputFilePage* OutputFilePage;
};
#endif // FCLASSWIZARD_H
