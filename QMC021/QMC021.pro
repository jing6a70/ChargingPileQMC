# MCQ021
# jingpeng
# Log:
#   <2024-01-13> 添加组件库
#   <2024-01-14> 添加设定C++11标准
#   <2024-01-20> Add CM017

QT       += core gui widgets
DEFINES  += GOOGLE_CHINESE_LIB CM017

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QMC021
TEMPLATE = app

CONFIG += c++11

SOURCES += main.cpp\
        mainwindow.cpp \
    appbarsettingseditor.cpp \
    app_cgmode.cpp \
    app_password.cpp \
    Keyboard/Keyboard.cpp \
    Keyboard/KeyButton.cpp \
    Keyboard/NumberKeyboard.cpp \
    systemconfig.cpp


HEADERS  += mainwindow.h \
    appbarsettingseditor.h \
    app_cgmode.h \
    app_password.h \
    mpdef.h \
    Keyboard/AbstractKeyboard.h \
    Keyboard/Keyboard.h \
    Keyboard/KeyButton.h \
    Keyboard/NumberKeyboard.h \
    systemconfig.h


contains(DEFINES, CM017) {
    SOURCES += dev/mcm_can_thread.cpp \
                dev/mcm_can.cpp \
                MCM/mcm_data.cpp \
                MCM/devmcm.cpp

    HEADERS += dev/mcm_can_thread.h \
                dev/mcm_can.h \
                MCM/mcm_data.h \
                MCM/devmcm.h
}


contains(DEFINES, ENABLED_CHINESE_LIB) {
    RESOURCES += Resources/ChineseLib.qrc
}

contains(DEFINES, ENABLED_CHINESE_PHRASE_LIB) {
    RESOURCES += Resources/ChinesePhraseLib.qrc
}

contains(DEFINES, GOOGLE_CHINESE_LIB) {
    RESOURCES += Resources/GoogleChineseLib.qrc
}

contains(DEFINES, ENABLED_WQY_FONT) {
    RESOURCES += Resources/Font.qrc
}


# 引用Qt组件库
# Library

unix:!macx: LIBS += -L$$OUT_PWD/../components/ -lcomponents

INCLUDEPATH += $$PWD/../components
DEPENDPATH += $$PWD/../components

unix:!macx: PRE_TARGETDEPS += $$OUT_PWD/../components/libcomponents.a

FORMS += \
    appbarsettingsform.ui \
    app_cgmode.ui \
    app_password.ui \
    systemconfig.ui
