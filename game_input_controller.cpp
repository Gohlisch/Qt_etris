#include "game_input_controller.hpp"

GameInputController::GameInputController()
    : userInput_{PlayerAction::UNKNOWN} {}

PlayerAction GameInputController::getUserInput() {
    PlayerAction input = userInput_;
    userInput_ = PlayerAction::UNKNOWN;
    return input;
}

void GameInputController::rotate() {
    userInput_ = PlayerAction::ROTATE;
}

void GameInputController::moveLeft() {
    userInput_ = PlayerAction::MOVE_LEFT;
}

void GameInputController::moveRight() {
    userInput_ = PlayerAction::MOVE_RIGHT;
}

void GameInputController::moveDown() {
    userInput_ = PlayerAction::MOVE_DOWN;
}

void GameInputController::moveDownFast() {
    userInput_ = PlayerAction::MOVE_DOWN_FAST;
}
