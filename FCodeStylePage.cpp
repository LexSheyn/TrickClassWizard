#include "FCodeStylePage.h"

FCodeStylePage::FCodeStylePage(QWidget* Parent)
    : QWizardPage (Parent)
{
    setTitle(tr("Code style options"));
    setSubTitle("\nChoose the formatting of the generated code.");

    // Namespace:

    NamespaceValidator = new QRegularExpressionValidator(QRegularExpression("\\w{1,}"), this);

    NamespaceLineEdit = new QLineEdit();
    NamespaceLineEdit->setValidator(NamespaceValidator);

    connect(NamespaceLineEdit, &QLineEdit::textEdited, this, &FCodeStylePage::SetNamespace);

    NamespaceLabel = new QLabel(tr("namespace"));
    NamespaceLabel->setBuddy(NamespaceLineEdit);

    NamespaceString = "t3d";

    NamespaceLayout = new QHBoxLayout();
    NamespaceLayout->addWidget(NamespaceLabel);
    NamespaceLayout->addWidget(NamespaceLineEdit);

    NamespaceGroup = new QGroupBox();
    NamespaceGroup->setLayout(NamespaceLayout);

    // Pragma:

    PragmaRadioButton = new QRadioButton(GetPragmaGuard());
    b_PragmaGuard = true;

    connect(PragmaRadioButton, &QRadioButton::toggled, this, &FCodeStylePage::SetPragmaGuardBool);

    // Define:

    DefineRadioButton = new QRadioButton(GetDefineGuard());
    b_DefineGuard = false;

    connect(DefineRadioButton, &QRadioButton::toggled, this, &FCodeStylePage::SetDefineGuardBool);

    // Page composing:

    GuardLayout = new QVBoxLayout();
    GuardLayout->addWidget(PragmaRadioButton);
    GuardLayout->addWidget(DefineRadioButton);

    GuardGroup = new QGroupBox(tr("Multiple inclusions header protection"));
    GuardGroup->setLayout(GuardLayout);

    registerField("Namespace"  , NamespaceLineEdit);
    registerField("PragmaGuard", PragmaRadioButton);
    registerField("DefineGuard", DefineRadioButton);

    Layout = new QGridLayout();
    Layout->addWidget(NamespaceGroup, 0, 0);
    Layout->addWidget(GuardGroup    , 1, 0);

    setLayout(Layout);

    t3d::FEvent::SettingsLoaded.Subscribe(this, &FCodeStylePage::OnSettingsLoaded);
}

FCodeStylePage::~FCodeStylePage()
{
    t3d::FEvent::SettingsLoaded.Unsubscribe(&FCodeStylePage::OnSettingsLoaded);
}

QByteArray FCodeStylePage::GetNamespace(QByteArray Namespace)
{
    return "namespace " + Namespace;
}

QByteArray FCodeStylePage::GetPragmaGuard()
{
    return "#pragma once";
}

QByteArray FCodeStylePage::GetDefineGuard(QByteArray ClassName)
{
    return "#define " + ClassName.toUpper() + "_H";
}

QByteArray FCodeStylePage::GetDefineGuardName(QByteArray ClassName)
{
    return ClassName.toUpper() + "_H";
}

QByteArray FCodeStylePage::GetNoCopyMacro(QByteArray ClassName)
{
    return "T3D_NO_COPY(" + ClassName + ");";
}

QByteArray FCodeStylePage::GetNoMoveMacro(QByteArray ClassName)
{
    return "T3D_NO_MOVE(" + ClassName + ");";
}

QByteArray FCodeStylePage::GetDefaultCopyMacro(QByteArray ClassName)
{
    return "T3D_DEFAULT_COPY(" + ClassName + ");";
}

QByteArray FCodeStylePage::GetDefaultMoveMacro(QByteArray ClassName)
{
    return "T3D_DEFAULT_MOVE(" + ClassName + ");";
}

void FCodeStylePage::initializePage()
{
    NamespaceLineEdit->setText(NamespaceString);

    PragmaRadioButton->setChecked(b_PragmaGuard);
    DefineRadioButton->setChecked(b_DefineGuard);

    DefineRadioButton->setText(GetDefineGuard(field("ClassName").toByteArray()));
}

void FCodeStylePage::SetNamespace(const QString &Text)
{
    NamespaceString = Text;
}

void FCodeStylePage::SetPragmaGuardBool(t3d::bool8 Checked)
{
    b_PragmaGuard = Checked;
}

void FCodeStylePage::SetDefineGuardBool(t3d::bool8 Checked)
{
    b_DefineGuard = Checked;
}

t3d::EPropagation FCodeStylePage::OnSettingsLoaded(FWizardSettings::Settings_T Settings)
{
    NamespaceString = Settings.Namespace;
    b_PragmaGuard   = Settings.b_PragmaGuard;
    b_DefineGuard   = Settings.b_DefineGuard;

    return t3d::EPropagation::Continue;
}







































