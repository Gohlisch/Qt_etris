#ifndef GAMEINPUTCONTROLLER_HPP
#define GAMEINPUTCONTROLLER_HPP

#include "input_controller.hpp"
#include "player_action.hpp"

class GameInputController : public InputController {
    PlayerAction userInput_;
public:
    GameInputController();

    [[nodiscard]] PlayerAction getUserInput() override;
    void rotate();
    void moveLeft();
    void moveRight();
    void moveDown();
    void moveDownFast();
};

#endif // GAMEINPUTCONTROLLER_HPP
