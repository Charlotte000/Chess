#pragma once

#include "Board.h"

class Game
{
public:
    Board board;
    PieceColor turn = PieceColor::White;

    void fill(unsigned int pawnCount = 8, unsigned int knightCount = 2, unsigned int bishopCount = 2, unsigned int rookCount = 2);

    void randomMove();

    std::vector<std::vector<Move>> evaluateBestMoves();

    void changeTurn();
};
