#ifndef KEYBOARDHANDLER_HPP
#define KEYBOARDHANDLER_HPP

#include <QObject>
#include <QKeyEvent>

typedef std::function<void(QKeyEvent*)> CallbackFunc;

class KeyboardHandler : public QObject
{
    Q_OBJECT
    CallbackFunc callback_;
public:
    explicit KeyboardHandler(QObject* parent = 0);
    explicit KeyboardHandler(CallbackFunc callback, QObject* parent = 0);
    void setCallback(CallbackFunc func) { callback_ = func; }

protected:
    bool eventFilter(QObject* obj, QEvent* event) override;
};

#endif // KEYBOARDHANDLER_HPP
