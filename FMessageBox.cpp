#include "FMessageBox.h"

void FMessageBox::Info(QWidget* Parent, QString Function, QString Message)
{
    QString InfoMessage;
    InfoMessage += "Function: ";
    InfoMessage += Function;
    InfoMessage += '\n';
    InfoMessage += "Message: ";
    InfoMessage += Message;

    QMessageBox::information(Parent, "Info", InfoMessage);
}

void FMessageBox::Warning(QWidget* Parent, QString Function, QString Message)
{
    QString WarningMessage;
    WarningMessage += "Function: ";
    WarningMessage += Function;
    WarningMessage += '\n';
    WarningMessage += "Message: ";
    WarningMessage += Message;

    QMessageBox::warning(Parent, "Warning", WarningMessage);
}

void FMessageBox::Error(QWidget* Parent, QString Function, QString Message)
{
    QString ErrorMessage;
    ErrorMessage += "Function: ";
    ErrorMessage += Function;
    ErrorMessage += '\n';
    ErrorMessage += "Message: ";
    ErrorMessage += Message;

    QMessageBox::critical(Parent, "Error", ErrorMessage);
}
