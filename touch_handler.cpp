#include "touch_handler.hpp"

TouchHandler::TouchHandler(QObject* parent)
    : QObject{parent} { }

bool TouchHandler::eventFilter(QObject* object, QEvent* event) {
    if(event->type() == QEvent::TouchBegin) {
        QTouchEvent* touchEvent = static_cast<QTouchEvent*>(event);
        lastTouchPoint_ = touchEvent->touchPoints().last().pos();
    } else if(event->type() == QEvent::TouchUpdate) {
        QTouchEvent* touchEvent = static_cast<QTouchEvent*>(event);
        QPointF touchPoint = touchEvent->touchPoints().last().pos(); // TODO: Copy only if necessary, use reference
        if(touchPoint.x() >= lastTouchPoint_.x()+minHorizontalDrag_) {
            rightCallback_(touchEvent);
            lastTouchPoint_ = touchPoint;
        } else if(touchPoint.x() <= lastTouchPoint_.x()-minHorizontalDrag_) {
            leftCallback_(touchEvent);
            lastTouchPoint_ = touchPoint;
        } else if(touchPoint.y() <= lastTouchPoint_.y()-minVerticalDrag_) {
            upwardsCallback_(touchEvent);
            lastTouchPoint_ = touchPoint;
        } else if(touchPoint.y() >= lastTouchPoint_.y()+minVerticalDrag_) {
            downwardsCallback_(touchEvent);
            lastTouchPoint_ = touchPoint;
        }
        return true;
    } else if (event->type() == QEvent::TouchEnd) {
        QTouchEvent* touchEvent = static_cast<QTouchEvent*>(event);
        QPointF touchPoint = touchEvent->touchPoints().last().pos();
        if(touchPoint.x()==lastTouchPoint_.x() && touchPoint.y()==lastTouchPoint_.y()) {
            tapCallback_(touchEvent);
        }
    } else {
        // standard event processing
        return QObject::eventFilter(object, event);
    }

    return true;
}
