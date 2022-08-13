#include "FClassWizard.h"

#include <QApplication>

int32_t main(int32_t ArgC, char* ArgV[])
{
    QApplication Application(ArgC, ArgV);

    FClassWizard Wizard;

    Wizard.show();

    return Application.exec();
}
