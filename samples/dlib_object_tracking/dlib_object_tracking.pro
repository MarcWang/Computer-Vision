TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += $$PWD/../../3rdparty
INCLUDEPATH += $$PWD/../../3rdparty/opencv/include

include(dlib_object_tracking.inc)

win32-msvc2012{
    !contains(QMAKE_TARGET.arch, x86_64) {
        message("QMake Windows VS2012 32")
        CONFIG(debug, debug|release){
            message("QMake Debug Mode")
        } else {
            message("QMake Release Mode")
            LIBS += $$PWD/../../3rdparty/dlib/lib/vc11/dlib.lib
            LIBS += $$PWD/../../3rdparty/opencv/lib/vc11/lib/opencv_ts300.lib
            LIBS += $$PWD/../../3rdparty/opencv/lib/vc11/lib/opencv_world300.lib
        }
    }
}




