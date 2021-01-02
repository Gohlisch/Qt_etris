#include "game.hpp"
#include "game_input_controller.hpp"
#include "gradient_raster_window.hpp"
#include "keyboard_handler.hpp"
#include "touch_handler.hpp"

#include <iostream>

#define TOUCH_PLATTFORM

int main(int argc, char** argv) {
    QGuiApplication app(argc, argv);
    GameInputController* gameInputController = new GameInputController();
    Game game{gameInputController};
    GradientRasterWindow window{QGradient::FabledSunset, &game};

    game.setRenderFunc([&app, &window](){ app.postEvent(&window, new QEvent{QEvent::UpdateRequest}); });

#ifdef KEYBOARD_PLATTFORM
    KeyboardHandler globalKeyboardHandler{};
    std::function<void(QKeyEvent*)> inputFunc = [&gameInputController](QKeyEvent* event) {
        if(event->key() == Qt::Key::Key_W) {
            gameInputController->rotate();
        } else if(event->key() == Qt::Key::Key_A) {
            gameInputController->moveLeft();
        } else if(event->key() == Qt::Key::Key_S) {
            gameInputController->moveDown();
        } else if(event->key() == Qt::Key::Key_D) {
            gameInputController->moveRight();
        } else if(event->key() == Qt::Key::Key_Space) {
            gameInputController->moveDownFast();
        }
    };
    globalKeyboardHandler.setCallback(inputFunc);
    app.installEventFilter(&globalKeyboardHandler);
#endif //KEYBOARD_PLATTFORM

#ifdef TOUCH_PLATTFORM
    TouchHandler globalTouchHandler{};
    globalTouchHandler.setRightCallback([&gameInputController](auto){ gameInputController->moveRight(); });
    globalTouchHandler.setLeftCallback([&gameInputController](auto){ gameInputController->moveLeft(); });
    globalTouchHandler.setDownwardsCallback([&gameInputController](auto){ gameInputController->rotate(); });
    globalTouchHandler.setUpwardsCallback([&gameInputController](auto){ gameInputController->moveDown(); });
    app.installEventFilter(&globalTouchHandler);
#endif //TOUCH_PLATTFORM


    window.show();
    std::thread gameThread{&Game::start, std::ref(game)};
    gameThread.detach();
    return app.exec();
}
