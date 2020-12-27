#ifndef INPUT_CONTROLLER_HPP
#define INPUT_CONTROLLER_HPP

#include "player_action.hpp"

struct InputController {
    [[nodiscard]] virtual PlayerAction getUserInput() = 0;
    virtual ~InputController() { }
};

#endif // INPUT_CONTROLLER_HPP
