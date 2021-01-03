#ifndef TOUCHHANDLER_HPP
#define TOUCHHANDLER_HPP

#include "gradient_raster_window.hpp"

#include <QObject>
#include <QKeyEvent>

typedef std::function<void(QTouchEvent*)> TouchCallbackFunc;

class TouchHandler : public QObject
{
    Q_OBJECT
    QPointF lastTouchPoint_;
    qreal minHorizontalDrag_ = BLOCK_SIZE; // TODO: set according to device
    qreal minVerticalDrag_ = BLOCK_SIZE/2; // TODO: set according to device
    TouchCallbackFunc rightCallback_ = [](auto){};
    TouchCallbackFunc leftCallback_ = [](auto){};
    TouchCallbackFunc upwardsCallback_ = [](auto){};
    TouchCallbackFunc downwardsCallback_ = [](auto){};
    TouchCallbackFunc tapCallback_ = [](auto){};

public:
    explicit TouchHandler(QObject* parent = 0);
    void setRightCallback(TouchCallbackFunc func) { rightCallback_ = func; }
    void setLeftCallback(TouchCallbackFunc func) { leftCallback_ = func; }
    void setUpwardsCallback(TouchCallbackFunc func) { upwardsCallback_ = func; }
    void setDownwardsCallback(TouchCallbackFunc func) { downwardsCallback_ = func; }
    void setTapCallback(TouchCallbackFunc func) { tapCallback_ = func; }

protected:
    bool eventFilter(QObject* obj, QEvent* event) override;
};

#endif // TOUCHHANDLER_HPP
