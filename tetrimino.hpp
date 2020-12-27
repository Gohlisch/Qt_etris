#ifndef TETRIMINO_HPP
#define TETRIMINO_HPP

#include <array>

constexpr static int TETRIMINO_SIZE = 4;
using Form = std::array<std::array<bool, TETRIMINO_SIZE>, TETRIMINO_SIZE>;

struct Tetrimino {
    Form form_;

    explicit Tetrimino(const Form form)
        : form_{form} {}
    void rotate_r();
    void rotate_back();
    void rotate_l();
};

struct Hero: public Tetrimino {
    Hero(): Tetrimino({{
        {0, 0, 1, 0},
        {0, 0, 1, 0},
        {0, 0, 1, 0},
        {0, 0, 1, 0}
    }}) {}
};

struct TeeWee: public Tetrimino {
    TeeWee(): Tetrimino({{
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 1, 0, 0},
        {1, 1, 1, 0}
    }}) {}
};


struct Orange_Ricky: public Tetrimino {
    Orange_Ricky(): Tetrimino({{
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 1},
        {0, 1, 1, 1}
    }}) {}
};

struct Blue_Ricky: public Tetrimino {
    Blue_Ricky(): Tetrimino({{
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {1, 0, 0, 0},
        {1, 1, 1, 0}
    }}) {}
};

struct Cleveland_Z: public Tetrimino {
    Cleveland_Z(): Tetrimino({{
        {0, 0, 1, 0},
        {0, 1, 1, 0},
        {0, 1, 0, 0},
        {0, 0, 0, 0}
    }}) {}
};

struct Rohde_Island_Z: public Tetrimino {
    Rohde_Island_Z(): Tetrimino({{
        {0, 1, 0, 0},
        {0, 1, 1, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 0}
    }}) {}
};



struct Smashboy: public Tetrimino {
    Smashboy(): Tetrimino({{
        {0, 0, 0, 0},
        {0, 1, 1, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0}
    }}) {}
};

#endif // TETRIMINO_HPP
