greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QMCProj
TEMPLATE = subdirs
SUBDIRS = \
    components\
    QMC021

# CONFIG += ordered
DEFINES += QT_DEPRECATED_WARNINGS
