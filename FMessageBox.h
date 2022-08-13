#ifndef FMESSAGEBOX_H
#define FMESSAGEBOX_H

#include <QMessageBox>
#include <QString>

struct FMessageBox
{
    static void Info    (QWidget* Parent, QString Function, QString Message);
    static void Warning (QWidget* Parent, QString Function, QString Message);
    static void Error   (QWidget* Parent, QString Function, QString Message);
};

#endif // FMESSAGEBOX_H
