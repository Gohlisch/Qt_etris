#include "keyboard_handler.hpp"

KeyboardHandler::KeyboardHandler(QObject* parent)
    : QObject{parent} { }

KeyboardHandler::KeyboardHandler(CallbackFunc callback, QObject* parent)
    : QObject{parent},
      callback_{callback} { }

bool KeyboardHandler::eventFilter(QObject* object, QEvent* event)
{
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
        callback_(keyEvent);
        return true;
    } else {
        // standard event processing
        return QObject::eventFilter(object, event);
    }
}

