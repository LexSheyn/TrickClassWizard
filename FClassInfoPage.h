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
    QLineEdit*                   ClassNameLineEdit;
    QLabel*                      BaseClassNameLabel;
    QLineEdit*                   BaseClassNameLineEdit;
    QRegularExpressionValidator* ClassValidator;
    QGridLayout*                 ClassLayout;
    QGroupBox*                   ClassGroup;

    QCheckBox*                   HeaderOnlyCheckBox;
    QVBoxLayout*                 HeaderOnlyLayout;
    QGroupBox*                   HeaderOnlyGroup;

    QCheckBox*                   NoCopyCheckBox;
    QCheckBox*                   DefaultCopyCheckBox;
    QVBoxLayout*                 CopyLayout;
    QGroupBox*                   CopyGroupBox;

    QCheckBox*                   NoMoveCheckBox;
    QCheckBox*                   DefaultMoveCheckBox;
    QVBoxLayout*                 MoveLayout;
    QGroupBox*                   MoveGroupBox;

    QVBoxLayout*                 Layout;
};

#endif // FCLASSINFOPAGE_H
