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

/*! \class Game
 *  \brief Connects all necessary components runs the games main loop
 */

/*! \fn Game::Game(InputController* inputController)
 *  \brief Constructor of Game
 *  @param inputController Pointer to the given Controller, from which
 *         the last User
 */

/*! \fn void Game::start()
 *  \brief start games main loop
 *  \warning to provide visualizatipn provide a callback function using setRenderFunc
 */

/*! \fn void Game::setRenderFunc(std::function<void ()> func)
 *  \brief set the function to request rendering
 *  @param func a callback function, called after the state of Game has changed
 */

/*! \func const PlayingField& Game::playingField() const
 *  \return the current state of the PlayingField, administrated by Game
 */

#endif // GAME_HPP
