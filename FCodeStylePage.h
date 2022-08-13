#ifndef FCODESTYLEPAGE_H
#define FCODESTYLEPAGE_H

#include <QWizardPage>
#include <QLabel>
#include <QLineEdit>
#include <QRegularExpressionValidator>
#include <QRadioButton>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QString>
#include <QVariant>
#include "FWizardSettings.h"
#include "FEvent.h"

class FCodeStylePage : public QWizardPage
{
    Q_OBJECT

public:

     FCodeStylePage (QWidget* Parent = nullptr);
    ~FCodeStylePage ();

    static QByteArray GetNamespace        (QByteArray Namespace);
    static QByteArray GetPragmaGuard      ();
    static QByteArray GetDefineGuard      (QByteArray ClassName = "");
    static QByteArray GetDefineGuardName  (QByteArray ClassName);
    static QByteArray GetNoCopyMacro      (QByteArray ClassName);
    static QByteArray GetNoMoveMacro      (QByteArray ClassName);
    static QByteArray GetDefaultCopyMacro (QByteArray ClassName);
    static QByteArray GetDefaultMoveMacro (QByteArray ClassName);

protected:

    void initializePage () override;

private slots:

    void SetNamespace       (const QString& Text);
    void SetPragmaGuardBool (t3d::bool8 Checked);
    void SetDefineGuardBool (t3d::bool8 Checked);

private:

    t3d::EPropagation OnSettingsLoaded (FWizardSettings::Settings_T Settings);

    QLabel*                      NamespaceLabel;
    QLineEdit*                   NamespaceLineEdit;
    QRegularExpressionValidator* NamespaceValidator;
    QString                      NamespaceString;
    QGroupBox*                   NamespaceGroup;
    QHBoxLayout*                 NamespaceLayout;
    QRadioButton*                PragmaRadioButton;
    QRadioButton*                DefineRadioButton;
    QGroupBox*                   GuardGroup;
    QVBoxLayout*                 GuardLayout;
    QGridLayout*                 Layout;
    t3d::bool8                   b_PragmaGuard;
    t3d::bool8                   b_DefineGuard;
};

#endif // FCODESTYLEPAGE_H
