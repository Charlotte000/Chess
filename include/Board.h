#pragma once

#include "Piece.h"
#include "Move.h"
#include <iostream>
#include <vector>

class Board
{
public:
    Board();

    void move(Move move);

    bool getCheck(PieceColor color) const;

    int getEvaluation(PieceColor color) const;

    std::vector<Move> getAvailableMoves(PieceColor color) const;

    std::vector<std::pair<int, Move>> getEvaluateMoves(PieceColor color) const;

    friend std::ostream& operator<<(std::ostream& os, const Board& board);

    Piece operator[](Coordinate coord) const;

    Piece& operator[](Coordinate coord);
private:
    const static std::vector<Coordinate> knightDeltas;
    const static std::vector<Coordinate> kingDeltas;
    const static std::vector<Coordinate> bishopDirections;
    const static std::vector<Coordinate> rookDirections;

    std::vector<std::vector<Piece>> board;
    bool whiteCheck, blackCheck;
    int whiteEvaluation;

    void getAvailablePieceMove(std::vector<Move>& moves, Coordinate begin) const;

    bool inBound(Coordinate coord) const;

    bool checkOccupy(std::vector<Move>& moves, Move move) const;

    bool checkAttack(std::vector<Move>& moves, PieceColor originColor, Move move) const;

    bool checkAttackOrOccupy(std::vector<Move>& moves, PieceColor originColor, Move move) const;

    void updateChecks();

    void updateEvaluations();
};
