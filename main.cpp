#include "game.hpp"
#include "game_input_controller.hpp"
#include "gradient_raster_window.hpp"
#include "keyboard_handler.hpp"

#include <iostream>

int main(int argc, char** argv) {
    QGuiApplication app(argc, argv);

    GameInputController* gameInputController = new GameInputController();

    KeyboardHandler globalKeyboardHandler{};

    Game game{gameInputController};
    GradientRasterWindow window{QGradient::FabledSunset, &game};

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

    window.show();
    game.setRenderFunc([&window](){ window.renderLater(); });
    std::thread gameThread{&Game::start, std::ref(game)};
    gameThread.detach();
    return app.exec();
}
