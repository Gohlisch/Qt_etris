#ifndef GAMEINPUTCONTROLLER_HPP
#define GAMEINPUTCONTROLLER_HPP

#include "input_controller.hpp"
#include "player_action.hpp"

class GameInputController : public InputController {
    PlayerAction userInput_;
public:
    GameInputController();

    [[nodiscard]] PlayerAction consumeInput() override;
    [[nodiscard]] virtual PlayerAction peekInput() override;
    void rotate();
    void moveLeft();
    void moveRight();
    void moveDown();
    void moveDownFast();
    void pause();
};

#endif // GAMEINPUTCONTROLLER_HPP
