QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/aboutdialog.cpp \
    src/createdialog.cpp \
    src/csvview.cpp \
    src/editdialog.cpp \
    main.cpp \
    src/mainwindow.cpp \
    src/sourcedialog.cpp

HEADERS += \
    src/aboutdialog.h \
    src/createdialog.h \
    src/csvview.h \
    src/editdialog.h \
    src/mainwindow.h \
    src/queue.h \
    src/sourcedialog.h

FORMS += \
    forms/aboutdialog.ui \
    forms/createdialog.ui \
    forms/csvview.ui \
    forms/editdialog.ui \
    forms/mainwindow.ui \
    forms/sourcedialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res/package.qrc \
    test/demo_package.qrc

DISTFILES +=
