#include "MouseManipulator.h"


MouseHandle::MouseHandle()
{
    this->selectObject = false;
    this->processing   = false;
}
MouseHandle::~MouseHandle()
{

}

MouseManipulator::MouseManipulator()
{
    mouseHandler = new MouseHandle();
}

MouseManipulator::~MouseManipulator()
{
    if( mouseHandler != NULL ){
        delete mouseHandler;
    }
}

void MouseManipulator::initialize( const std::string &windowName )
{
    if( mouseHandler == NULL ){
        return;
    }
    cv::setMouseCallback( windowName, onMouse, mouseHandler );
}

bool MouseManipulator::hasSelection()
{
    if( mouseHandler->selectObject ){
        return true;
    }
    else{
        return false;
    }
}

cv::Rect MouseManipulator::getSelectRect()
{
    return mouseHandler->selecRect;
}

void MouseManipulator::clear()
{
    mouseHandler->processing   = false;
    mouseHandler->selecRect    = cv::Rect();
    mouseHandler->selectObject = false;

}

void MouseManipulator::onMouse( int event, int x, int y, int, void *ptr )
{
    MouseHandle *mouseHandler = (MouseHandle*)ptr;
    if( mouseHandler->processing ){
        mouseHandler->selecRect.x      = MIN( x, mouseHandler->point.x );
        mouseHandler->selecRect.y      = MIN( y, mouseHandler->point.y );
        mouseHandler->selecRect.width  = std::abs( x - mouseHandler->point.x );
        mouseHandler->selecRect.height = std::abs( y - mouseHandler->point.y );
    }
    switch( event )
    {
    case CV_EVENT_LBUTTONDOWN:
        mouseHandler->point        = cv::Point( x, y );
        mouseHandler->selecRect    = cv::Rect( x, y, 0, 0 );
        mouseHandler->processing   = true;
        mouseHandler->selectObject = false;
        break;
    case CV_EVENT_LBUTTONUP:
        mouseHandler->processing = false;
        if( mouseHandler->selecRect.width > 0 &&
            mouseHandler->selecRect.height > 0 ){
            mouseHandler->selectObject = true;
        }
        break;
    }
}
