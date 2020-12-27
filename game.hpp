#ifndef GAME_HPP
#define GAME_HPP

#include <chrono>
#include <thread>

#include "playingfield.hpp"
#include "input_controller.hpp"

using namespace std::chrono;

class Game {
    PlayerAction pressed_;
    steady_clock::time_point timer_;
    PlayingField field_;
    InputController* inputController_;
    std::function<void()> renderFunc_;

    bool playerAction();
public:
    Game(InputController* inputController);

    void start();
    void setRenderFunc(std::function<void()> func);
    [[nodiscard]] const PlayingField& playingField() const;
};

#endif // GAME_HPP
