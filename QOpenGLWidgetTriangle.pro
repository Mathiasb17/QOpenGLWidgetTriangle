#-------------------------------------------------
#
# Project created by QtCreator 2016-06-14T15:41:39
#
#-------------------------------------------------

QT       += core gui widgets

LIBS += -lassimp

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QOpenGLWidgetTriangle
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    gldisplay.cpp \
    triangle.cpp \
    particles.cpp \
    mesh.cpp

HEADERS  += mainwindow.h \
    gldisplay.h \
    triangle.h \
    particles.h \
    mesh.h

FORMS    += mainwindow.ui

DISTFILES += \
    simple.vert \
    simple.frag


RESOURCES += shaders.qrc
