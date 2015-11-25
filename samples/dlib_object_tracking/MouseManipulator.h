#ifndef MOUSEMANIPULATOR_H
#define MOUSEMANIPULATOR_H
#include "opencv2/opencv.hpp"
#include <common.h>

struct MouseHandle
{
public:
    MouseHandle();
    ~MouseHandle();
    cv::Rect selecRect;
    cv::Point2f point;
    bool selectObject;
    bool processing;
};

class LIB_DECL MouseManipulator
{
public:
    MouseManipulator();
    ~MouseManipulator();
    void initialize( const std::string &windowName );

    bool hasSelection();
    cv::Rect getSelectRect();
    void clear();

    static void onMouse( int event, int x, int y, int, void *ptr);

private:
    MouseHandle *mouseHandler;
};

#endif // MOUSEMANIPULATOR_H
