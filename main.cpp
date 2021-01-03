#include "game.hpp"
#include "game_input_controller.hpp"
#include "gradient_raster_window.hpp"
#include "keyboard_handler.hpp"
#include "touch_handler.hpp"

#include <iostream>

#define TOUCH_PLATFORM // define KEYBOARD_PLATFORM or TOUCH_PLATFORM depending on target platformd

int main(int argc, char** argv) {
    QGuiApplication app(argc, argv);
    GameInputController* gameInputController = new GameInputController();
    Game game{gameInputController};
    GradientRasterWindow window{QGradient::FabledSunset, &game};

    game.setRenderFunc([&app, &window](){ app.postEvent(&window, new QEvent{QEvent::UpdateRequest}); });

#ifdef KEYBOARD_PLATFORM
    KeyboardHandler inputHandler{};
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
        } else if(event->key() == Qt::Key::Key_Escape) {
            gameInputController->pause();
        }
    };
    inputHandler.setCallback(inputFunc);
#endif //KEYBOARD_PLATFORM

#ifdef TOUCH_PLATFORM
    TouchHandler inputHandler{};
    inputHandler.setRightCallback([&gameInputController](auto){ gameInputController->moveRight(); });
    inputHandler.setLeftCallback([&gameInputController](auto){ gameInputController->moveLeft(); });
    inputHandler.setUpwardsCallback([&gameInputController](auto){ gameInputController->pause(); });
    inputHandler.setDownwardsCallback([&gameInputController](auto){ gameInputController->moveDown(); });
    inputHandler.setTapCallback([&gameInputController](auto){ gameInputController->rotate(); });
#endif //TOUCH_PLATFORM

    app.installEventFilter(&inputHandler);

    window.show();
    std::thread gameThread{&Game::start, std::ref(game)};
    gameThread.detach();
    return app.exec();
}
