TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += $$PWD/../../3rdparty
INCLUDEPATH += $$PWD/../../3rdparty/opencv/include
INCLUDEPATH += $$PWD/../../3rdparty/opencv/include/face

SOURCES += main.cpp

include(deployment.pri)
qtcAddDeployment()

win32-msvc2012{
    !contains(QMAKE_TARGET.arch, x86_64) {
        message("QMake Windows VS2012 32")
        CONFIG(debug, debug|release){
            message("QMake Debug Mode")
        } else {
            message("QMake Release Mode")
            LIBS += $$PWD/../../3rdparty/opencv/lib/vc11/lib/opencv_ts300.lib
            LIBS += $$PWD/../../3rdparty/opencv/lib/vc11/lib/opencv_world300.lib
            LIBS += $$PWD/../../3rdparty/opencv/lib/vc11/lib/opencv_face300.lib
        }
    }
}


