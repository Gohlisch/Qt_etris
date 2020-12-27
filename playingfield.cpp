#include "playingfield.hpp"

PlayingField::PlayingField(): field_{}, factory_{}, currentPieceCords_{} {}

const Field& PlayingField::field() const {
    return field_;
}

const std::array<int,2>& PlayingField::currentPieceCords() const {
    return currentPieceCords_;
}

const Tetrimino& PlayingField::currentPiece() const{
    return factory_.getCurrent();
}

void PlayingField::draw() const {
    constexpr char freeSpot[] {"_"};
    constexpr char taken[] {"#"};
    constexpr char locked[] {""};

    for(int i{}; i < 25; ++i) std::cout  << '\n';

    std::cout << locked;
    for(int i{}; i < F_WIDTH; ++i) std::cout << locked << locked;
    std::cout << locked << '\n';

    for(const auto row : field_) {
        std::cout << locked;
        for(const auto column : row) {
            std::cout << (column ? taken : freeSpot) << (column ? taken : freeSpot);
        }
        std::cout << locked << '\n';
    }

    std::cout << locked;
    for(int i{}; i < F_WIDTH; ++i) std::cout << locked << locked;
    std::cout << locked << std::endl;
}

signed char PlayingField::handleTetris() {
    signed char rowsWithTetris{};

    for(auto row = field_.begin(); row != field_.end(); ++row) {
        for(auto it = row->begin(); it != row->end(); ++it) {
            if(!(*it)) break;
            else if(it == (row->end())-1) {
                clearRow(row);
                ++rowsWithTetris;
            }
        }
    }

    return rowsWithTetris;
}

void PlayingField::clearRow(std::array<bool, F_WIDTH>* row) {
    for(auto it = row; *it != field_[0]; --it) {
        it->swap(*(it-1));
    }
    field_[0].fill(false);
}

bool PlayingField::dropPieceAndResetCords() {
    resetCords();
    factory_.produceNext();
    return dropPiece(factory_.getCurrent(), currentPieceCords_[0], currentPieceCords_[1]);
}

void PlayingField::resetCords() {
    currentPieceCords_[0] = 0;
    currentPieceCords_[1] = F_SPAWN_POINT;
}

bool PlayingField::dropPiece(const Tetrimino* tet, const int currentColumn, const int currentRow) {
    for(int row = 0; row < TETRIMINO_SIZE; ++row)
        for(int column = 0; column < TETRIMINO_SIZE; ++column)
            if((tet->form_[column][row] && !isInBounds(column+currentColumn, row+currentRow))
               || (tet->form_[column][row] && field_[column+currentColumn][row+currentRow]))
                return false;

    for(int row = 0; row < TETRIMINO_SIZE; ++row)
        for(int column = 0; column < TETRIMINO_SIZE; ++column)
            if(tet->form_[column][row]) field_[column+currentColumn][row+currentRow] = true ;
    return true;
}

bool PlayingField::movePieceRight() {
    pickUpPiece(factory_.getCurrent(), currentPieceCords_[0], currentPieceCords_[1]);
    if(dropPiece(factory_.getCurrent(), currentPieceCords_[0], ++currentPieceCords_[1])) {
        return true;
    }
    dropPiece(factory_.getCurrent(), currentPieceCords_[0], --currentPieceCords_[1]);
    return false;
}

bool PlayingField::movePieceLeft() {
    pickUpPiece(factory_.getCurrent(), currentPieceCords_[0], currentPieceCords_[1]);
    if(dropPiece(factory_.getCurrent(), currentPieceCords_[0], --currentPieceCords_[1])) {
        return true;
    }
    dropPiece(factory_.getCurrent(), currentPieceCords_[0], ++currentPieceCords_[1]);
    return false;
}

bool PlayingField::rotatePiece() {
    pickUpPiece(factory_.getCurrent(), currentPieceCords_[0], currentPieceCords_[1]);
    factory_.getCurrent()->rotate_r();
    if(dropPiece(factory_.getCurrent(), currentPieceCords_[0], currentPieceCords_[1])) {
        return true;
    }
    factory_.getCurrent()->rotate_back();
    dropPiece(factory_.getCurrent(), currentPieceCords_[0], currentPieceCords_[1]);
    return false;
}

bool PlayingField::tick() {
    pickUpPiece(factory_.getCurrent(), currentPieceCords_[0], currentPieceCords_[1]);
    if(dropPiece(factory_.getCurrent(), ++currentPieceCords_[0], currentPieceCords_[1])) {
        return true;
    }
    dropPiece(factory_.getCurrent(), --currentPieceCords_[0], currentPieceCords_[1]);
    return false;
}

void PlayingField::pickUpPiece(const Tetrimino* tet, const int currentColumn, const int currentRow) {
    for(int row = 0; row < TETRIMINO_SIZE; ++row)
        for(int column = 0; column < TETRIMINO_SIZE; ++column)
            if(tet->form_[column][row]&&isInBounds(column+currentColumn, row+currentRow))
                field_[column+currentColumn][row+currentRow] = false;
}

inline bool PlayingField::isInBounds(const int x, const int y) const {
    return x>-1 && y>-1 && x<F_HEIGHT && y<F_WIDTH;
}



