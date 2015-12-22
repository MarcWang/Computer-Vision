TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle qt

CONFIG(debug, debug|release):BUILD_MODE = debug
else:BUILD_MODE = release

include(opencv_using_gpu.pri)

## 3rdParty Include
############################################################
INCLUDEPATH += $${PWD}/../../3rdparty/opencv/include

## Vars Setting
############################################################
BASE = $${PWD}

## DIRS
############################################################
DESTDIR     = $${PWD}/release
TMP_DIR     = $$_PRO_FILE_PWD_/.tmp/$${BUILD_MODE}
UI_DIR      = $${TMP_DIR}
MOC_DIR     = $${TMP_DIR}
RCC_DIR     = $${TMP_DIR}
OBJECTS_DIR = $${TMP_DIR}

OPENCV_DLL_PATH             = $${PWD}/../../3rdparty/opencv/lib/vc11/bin
BUILD_DIR                   = $${DESTDIR}

## File Setting
############################################################
OPENCV_DLLS = opencv_world310.dll

## Platform Setting
############################################################
win32-msvc2012{
    !contains(QMAKE_TARGET.arch, x86_64) {
        message("QMake Windows VS2012 32")
        CONFIG(debug, debug|release){
            message("QMake Debug Mode")
        } else {
            message("QMake Release Mode")
            LIBS += $$PWD/../../3rdparty/opencv/lib/vc11/lib/opencv_world310.lib

            for( files, OPENCV_DLLS ):eval( QMAKE_POST_LINK += xcopy /R /Q /Y /I $$replace( OPENCV_DLL_PATH, /, \\ )\\$${files} $$replace( BUILD_DIR, /, \\ ) & )
            export(QMAKE_POST_LINK)

        }
    }
}




