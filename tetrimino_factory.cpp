#include "tetrimino_factory.hpp"

TetriminoFactory::TetriminoFactory():
    engine_{std::random_device{}()},current_{getRandomTetrimino()}, next_{getRandomTetrimino()} {}

void TetriminoFactory::produceNext() {
    current_ = next_;
    next_ = getRandomTetrimino();
}

Tetrimino TetriminoFactory::getRandomTetrimino() {
    std::uniform_int_distribution<int> w7{0, 6};
    switch(w7(engine_)) {
        case(0): return Hero{};
        case(1): return TeeWee{};
        case(2): return Orange_Ricky{};
        case(3): return Blue_Ricky{};
        case(4): return Cleveland_Z{};
        case(5): return Rohde_Island_Z{};
        default: return Smashboy{};
    }
}
