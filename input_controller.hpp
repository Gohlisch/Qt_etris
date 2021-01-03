#ifndef INPUT_CONTROLLER_HPP
#define INPUT_CONTROLLER_HPP

#include "player_action.hpp"

struct InputController {
    [[nodiscard]] virtual PlayerAction consumeInput() = 0;
    [[nodiscard]] virtual PlayerAction peekInput() = 0;
    virtual ~InputController() { }
};

#endif // INPUT_CONTROLLER_HPP
