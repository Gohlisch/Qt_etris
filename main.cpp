#include "game.hpp"
#include "game_input_controller.hpp"
#include "gradient_raster_window.hpp"
#include "keyboard_handler.hpp"

#include <iostream>

int main(int argc, char** argv) {
    QGuiApplication app(argc, argv);
    GradientRasterWindow window{QGradient::GlassWater};

    GameInputController* gameInputController = new GameInputController();

    KeyboardHandler globalKeyboardHandler{};

    Game game{gameInputController};

    std::function<void(QKeyEvent*)> inputFunc = [&gameInputController, &window, &game](QKeyEvent* event) {
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
        window.renderGame(game);
    };

    globalKeyboardHandler.setCallback(inputFunc);

    app.installEventFilter(&globalKeyboardHandler);


    window.show();
    //std::function<void()> render = [&window, &game](){ window.renderGame(game); };
    game.setRenderFunc([&game](){ game.playingField().draw(); });
    std::thread gameThread{&Game::start, std::ref(game)};



    return app.exec();
}
