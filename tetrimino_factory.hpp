#ifndef TETRIMINO_FACTORY_HPP
#define TETRIMINO_FACTORY_HPP

#include <random>
#include "tetrimino.hpp"

class TetriminoFactory {
    std::default_random_engine engine_;
    Tetrimino current_;
    Tetrimino next_;
    Tetrimino getRandomTetrimino();
public:
    TetriminoFactory();

    void produceNext();
    [[nodiscard]] const Tetrimino& getCurrent() const { return current_; }
    Tetrimino* getCurrent() { return &const_cast<Tetrimino&>(const_cast<const TetriminoFactory*> (this)->getCurrent()); }
    Tetrimino* getNext() { return &next_; }
};

#endif // TETRIMINO_FACTORY_HPP
