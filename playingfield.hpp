#ifndef PLAYING_FIELD_HPP
#define PLAYING_FIELD_HPP

#include <utility>
#include <array>
#include <iostream>

#include "tetrimino.hpp"
#include "tetrimino_factory.hpp"

constexpr int F_WIDTH = 12;
constexpr int F_HEIGHT = 18;
constexpr int F_SPAWN_POINT = F_WIDTH / 3;

using Field = std::array<std::array<bool, F_WIDTH>, F_HEIGHT>;

class PlayingField {
    Field field_;
    TetriminoFactory factory_;
    std::array<int, 2> currentPieceCords_;

    void resetCords();
    bool dropPiece(const Tetrimino* piece, int x, int y);
    void pickUpPiece(const Tetrimino* piece, int x, int y);
    inline bool isInBounds(int x, int y) const;
    void clearRow(std::array<bool, F_WIDTH>*);
public:
    PlayingField();

    [[nodiscard]] const Field& field() const;
    [[nodiscard]] const std::array<int, 2>& currentPieceCords() const;
    [[nodiscard]] const Tetrimino& currentPiece() const;

    void draw() const; // notify renderer
    signed char handleTetris();
    bool dropPieceAndResetCords();
    bool movePieceRight();
    bool movePieceLeft();
    bool rotatePiece();
    bool tick();
};

#endif // PLAYING_FIELD_HPP
