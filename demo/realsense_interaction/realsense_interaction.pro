TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG += qt

INCLUDEPATH += $$PWD/../../3rdparty
INCLUDEPATH += $$PWD/../../3rdparty/opencv/include
INCLUDEPATH += $$PWD/../../3rdparty/intel/RSSDK/include

include(realsense_interaction.inc)

win32-msvc2012{
    !contains(QMAKE_TARGET.arch, x86_64) {
        message("QMake Windows VS2012 32")
        CONFIG(debug, debug|release){
            message("QMake Debug Mode")
        } else {
            message("QMake Release Mode")
            LIBS += $$PWD/../../3rdparty/opencv/lib/vc11/lib/opencv_ts300.lib
            LIBS += $$PWD/../../3rdparty/opencv/lib/vc11/lib/opencv_world300.lib
            LIBS += $$PWD/../../3rdparty/intel/RSSDK/lib/Win32/libpxc.lib
        }
    }
}

LIBS += -lAdvapi32 -lkernel32 -lgdi32 -luser32
