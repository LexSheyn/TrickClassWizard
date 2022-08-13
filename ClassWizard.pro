QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    FAssert.cpp \
    FClassInfoPage.cpp \
    FClassWizard.cpp \
    FCodeStylePage.cpp \
    FMessageBox.cpp \
    FOutputFilePage.cpp \
    FWizardSettings.cpp \
    main.cpp

HEADERS += \
    EPropagation.h \
    FAssert.h \
    FClassInfoPage.h \
    FClassWizard.h \
    FCodeStylePage.h \
    FEvent.h \
    FMessageBox.h \
    FOutputFilePage.h \
    FWizardSettings.h \
    TEvent.h \
    TFunction.h \
    TrickAPI.h \
    TrickTypes.h

RC_ICONS = Wizard_48_Green.ico

RESOURCES = application.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
