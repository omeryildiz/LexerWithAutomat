QT += core gui widgets printsupport

TEMPLATE = app
TARGET = LexerWithAutomat

CONFIG += c++17
CONFIG -= console

SOURCES += \
    lexer.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    lexer.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

RESOURCES += \
    Res.qrc
