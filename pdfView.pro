QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = pdfView
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
        pdf.cpp

HEADERS += \
        mainwindow.h \
        pdf.h

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

## de schimbat
LIBS +="C:\Users\gengi\Documents\pdfView\lib\libmupdf.lib"
INCLUDEPATH +="C:\Users\gengi\Documents\pdfView\include"
