#ifndef FCLASSINFOPAGE_H
#define FCLASSINFOPAGE_H

#include <QWizardPage>
#include <QLabel>
#include <QLineEdit>
#include <QRegularExpressionValidator>
#include <QCheckBox>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QGridLayout>

class FClassInfoPage : public QWizardPage
{
    Q_OBJECT

public:

    FClassInfoPage (QWidget* Parent = nullptr);

private slots:

    void UncheckNoCopy      (bool Checked);
    void UncheckDefaultCopy (bool Checked);
    void UncheckNoMove      (bool Checked);
    void UncheckDefaultMove (bool Checked);

private:

    QLabel*                      ClassNameLabel;
    QLabel*                      BaseClassLabel;
    QLineEdit*                   ClassNameLineEdit;
    QLineEdit*                   BaseClassLineEdit;
    QRegularExpressionValidator* Validator;
    QCheckBox*                   HeaderOnlyCheckBox;
    QCheckBox*                   NoCopyCheckBox;
    QCheckBox*                   NoMoveCheckBox;
    QCheckBox*                   DefaultCopyCheckBox;
    QCheckBox*                   DefaultMoveCheckBox;
    QGroupBox*                   CopyGroupBox;
    QGroupBox*                   MoveGroupBox;
    QVBoxLayout*                 CopyLayout;
    QVBoxLayout*                 MoveLayout;
    QGridLayout*                 Layout;
};

#endif // FCLASSINFOPAGE_H
