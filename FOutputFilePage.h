#ifndef FOUTPUTFILEPAGE_H
#define FOUTPUTFILEPAGE_H

#include <QWizardPage>
#include <QLabel>
#include <QLineEdit>
#include <QGroupBox>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QCheckBox>
#include <QFileDialog>
#include <QDir>
#include <QString>
#include "FWizardSettings.h"
#include "FEvent.h"

class FOutputFilePage : public QWizardPage
{
    Q_OBJECT

public:

     FOutputFilePage (QWidget* Parent = nullptr);
    ~FOutputFilePage ();

    QString GetHeaderPath ();
    QString GetSourcePath ();

protected:

    void initializePage () override;

private slots:

    void BrowseProject          ();
    void SetProjectPathString   (const QString& Text);
    void SetNestedPathString    (const QString& Text);
    void SetPCHSubpathString    (const QString& Text);
    void SetPCHNameString       (const QString& Text);
    void SetHeaderSubpathString (const QString& Text);
    void SetSourceSubpathString (const QString& Text);

private:

    t3d::EPropagation OnSettingsLoaded (FWizardSettings::Settings_T Settings);

    QLabel*      ProjectPathLabel;
    QLineEdit*   ProjectPathLineEdit;
    QPushButton* ProjectPathPushButton;
    QString      ProjectPathString;
    QLabel*      NestedPathLabel;
    QLineEdit*   NestedPathLineEdit;
    QString      NestedPathString;
    QGroupBox*   ProjectGroupBox;
    QGridLayout* ProjectLayout;

    QCheckBox*   PCHCheckBox;
    bool         b_PCH;
    QLineEdit*   PCHSubpathLineEdit;
    QLabel*      PCHSubpathLabel;
    QString      PCHSubpathString;
    QLineEdit*   PCHNameLineEdit;
    QLabel*      PCHNameLabel;
    QString      PCHNameString;
    QGridLayout* PCHLayout;
    QGroupBox*   PCHGroup;

    QLabel*      HeaderSubpathLabel;
    QLineEdit*   HeaderSubpathLineEdit;
    QString      HeaderSubpathString;
    QLabel*      HeaderNameLabel;
    QLineEdit*   HeaderNameLineEdit;
    QGridLayout* HeaderLayout;
    QGroupBox*   HeaderGroupBox;

    QLabel*      SourceSubpathLabel;
    QLineEdit*   SourceSubpathLineEdit;
    QString      SourceSubpathString;
    QLabel*      SourceNameLabel;
    QLineEdit*   SourceNameLineEdit;
    QGridLayout* SourceLayout;
    QGroupBox*   SourceGroupBox;

    QVBoxLayout* Layout;
};

#endif // FOUTPUTFILEPAGE_H
