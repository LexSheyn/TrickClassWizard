#ifndef FOUTPUTFILEPAGE_H
#define FOUTPUTFILEPAGE_H

#include <QWizardPage>
#include <QLabel>
#include <QLineEdit>
#include <QGroupBox>
#include <QGridLayout>
#include <QPushButton>
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

    QString GetHeaderDirectory ();
    QString GetSourceDirectory ();

protected:

    void initializePage () override;

private slots:

    void BrowseProject               ();
    void SetProjectDirectoryString   (const QString& Text);
    void SetNestedDirectoryString    (const QString& Text);
    void SetHeaderSubdirectoryString (const QString& Text);
    void SetSourceSubdirectoryString (const QString& Text);

private:

    t3d::EPropagation OnSettingsLoaded (FWizardSettings::Settings_T Settings);

    QLabel*      ProjectDirectoryLabel;
    QLabel*      NestedDirectoryLabel;
    QLabel*      HeaderSubdirectoryLabel;
    QLabel*      SourceSubdirectoryLabel;
    QLabel*      HeaderLabel;
    QLabel*      SourceLabel;
    QLineEdit*   ProjectDirectoryLineEdit;
    QLineEdit*   NestedDirectoryLineEdit;
    QLineEdit*   HeaderSubdirectoryLineEdit;
    QLineEdit*   SourceSubdirectoryLineEdit;
    QLineEdit*   HeaderLineEdit;
    QLineEdit*   SourceLineEdit;
    QPushButton* ProjectDirectoryPushButton;
    QGroupBox*   ProjectGroupBox;
    QGroupBox*   HeaderGroupBox;
    QGroupBox*   SourceGroupBox;
    QGridLayout* ProjectLayout;
    QGridLayout* HeaderLayout;
    QGridLayout* SourceLayout;
    QVBoxLayout* Layout;
    QString      ProjectDirectoryString;
    QString      NestedDirectoryString;
    QString      HeaderSubdirectoryString;
    QString      SourceSubdirectoryString;
};

#endif // FOUTPUTFILEPAGE_H
