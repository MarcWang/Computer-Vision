TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += ../../3rdparty
INCLUDEPATH += ../../3rdparty/opencv/include

#DEFINES += "_ITERATOR_DEBUG_LEVEL=0"

include(deployment.pri)
include(Face_Detection.inc)

win32-msvc2012{
    !contains(QMAKE_TARGET.arch, x86_64) {
        message("QMake Windows VS2012 32")
        CONFIG(debug, debug|release){
            message("QMake Debug Mode")
        } else {
            message("QMake Release Mode")
            LIBS += C:/work/Projects/GitHub/Computer-Vision/3rdparty/opencv/lib/vc11/lib/opencv_ts300.lib
            LIBS += C:/work/Projects/GitHub/Computer-Vision/3rdparty/opencv/lib/vc11/lib/opencv_world300.lib
            LIBS += C:/work/Projects/GitHub/Computer-Vision/3rdparty/dlib/lib/vc11/dlib.lib
        }
    }
}




