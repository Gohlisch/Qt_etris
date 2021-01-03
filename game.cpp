#include "game.hpp"

Game::Game(InputController* inputController)
    : pressed_{PlayerAction::UNKNOWN},
      field_{},
      inputController_{inputController} { }

void Game::start() {
    bool gameRunning{true};
    duration<double> turnDuration{};

    field_.dropPieceAndResetCords();
    while(gameRunning) {
        renderFunc_();
        turnDuration = 0s;
        timer_ = steady_clock::now();

        while(turnDuration<1s){
            pressed_ = inputController_->getUserInput();
            if(pressed_ != PlayerAction::UNKNOWN) {
                playerAction();
                renderFunc_();
            } else {
                turnDuration = duration_cast<duration<double>>(steady_clock::now() - timer_);
                std::this_thread::sleep_for(1us);
            }
        }

        if(!field_.tick()) {
            field_.handleTetris();
            gameRunning = field_.dropPieceAndResetCords();
            renderFunc_();
        }
    }
    renderFunc_();
}

void Game::setRenderFunc(std::function<void()> func) {
    renderFunc_ = func;
}

const PlayingField& Game::playingField() const {
    return field_;
};

bool Game::playerAction() {
    bool success{false};

    if(pressed_ == PlayerAction::MOVE_RIGHT) { success = field_.movePieceRight(); }
    else if(pressed_ == PlayerAction::MOVE_LEFT) { success = field_.movePieceLeft(); }
    else if(pressed_ == PlayerAction::ROTATE) { success = field_.rotatePiece(); }
    else if(pressed_ == PlayerAction::MOVE_DOWN) { success = field_.tick(); }
    else if(pressed_ == PlayerAction::MOVE_DOWN_FAST) {
        while(field_.tick());
        success = true;
    }

    return success;
}
