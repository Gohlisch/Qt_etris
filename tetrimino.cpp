#include "tetrimino.hpp"

void Tetrimino::rotate_r() {
    Form tmp {};
    std::copy(form_.begin(), form_.end(), tmp.begin());
    for(int row = 0 ; row < TETRIMINO_SIZE; ++row )
        for(int column = 0; column < TETRIMINO_SIZE; ++column)
            form_[column][TETRIMINO_SIZE-1-row] = tmp[row][column];
}

void Tetrimino::rotate_back() {
    Form tmp {};
    std::copy(form_.begin(), form_.end(), tmp.begin());
    for(int row = 0 ; row < TETRIMINO_SIZE; ++row )
        for(int column = 0; column < TETRIMINO_SIZE; ++column)
            form_[row][column] = tmp[column][TETRIMINO_SIZE-1-row];
}

void Tetrimino::rotate_l() {
    Form tmp {};
    std::copy(form_.begin(), form_.end(), tmp.begin());
    for(int row = 0; row < TETRIMINO_SIZE; ++row )
        for(int column = 0; column < TETRIMINO_SIZE; ++column)
            form_[column][row] = tmp[row][column];
}