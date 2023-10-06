#pragma once

#include <iostream>
#include <vector>

enum class PieceType
{
    Empty,
    Pawn,
    Knight,
    King,
    Bishop,
    Rook,
};

enum class PieceColor : bool
{
    White = true,
    Black = false,
};

struct Piece
{
public:
    PieceColor color;
    PieceType type;

    Piece(PieceColor color, PieceType type);

    friend std::ostream& operator<<(std::ostream& os, const Piece& piece);
};
