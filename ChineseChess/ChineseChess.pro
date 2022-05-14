QT       += core gui
CONFIG += c++11 console
CONFIG -=app_bundle
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QMAKE_CXXFLAGS += /utf-8
CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    board.cpp \
    chess.cpp \
    gamemanager.cpp \
    main.cpp \
    mainwindow.cpp \
    viewer.cpp

HEADERS += \
    board.h \
    chess.h \
    gamemanager.h \
    mainwindow.h \
    viewer.h

FORMS += \
    gamemanager.ui \
    mainwindow.ui

TRANSLATIONS += \
    ChineseChess_zh_TW.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
