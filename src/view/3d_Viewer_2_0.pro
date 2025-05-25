QT       += core gui opengl openglwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

include(QtGifImage/src/gifimage/qtgifimage.pri)


CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    main.cc \
    mainwindow.cc \
    ../model/parser.cc \
    ../model/glwidget.cc \
    ../model/affinetransformation.cc \
    ../controller/controller.cc


HEADERS += \
    mainwindow.h \
    ../model/parser.h \
    ../model/glwidget.h \
    ../model/affinetransformation.h \
    ../controller/controller.h

FORMS += \
    mainwindow.ui
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

SUBDIRS += \
    ../QtGifImage/qtgifimage.pro \
    ../QtGifImage/qtgifimage.pro \
    ../QtGifImage/qtgifimage.pro \
    ../QtGifImage/qtgifimage.pro \
    ../QtGifImage/src/src.pro \
    ../QtGifImage/src/src.pro
