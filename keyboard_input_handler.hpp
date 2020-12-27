#ifndef KEYBOARDINPUTHANDLER_HPP
#define KEYBOARDINPUTHANDLER_HPP

#include <QObject>

class KeyboardInputHandler : public QObject
{
    Q_OBJECT
public:
    explicit KeyboardInputHandler(QFunctionPointer callback, QObject *parent = nullptr);

signals:

};

#endif // KEYBOARDINPUTHANDLER_HPP
