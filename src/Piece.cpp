#include "Piece.h"

Piece::Piece(PieceColor isWhite, PieceType type)
    : color(isWhite), type(type)
{
}

std::ostream& operator<<(std::ostream& os, const Piece& piece)
{
    switch (piece.color)
    {
        case PieceColor::White:
            os << "\033[97m";
            break;
        case PieceColor::Black:
            os << "\033[90m";
    }
    
    switch (piece.type)
    {
        case PieceType::Empty:
            os << " ";
            break;
        case PieceType::Pawn:
            os << "P";
            break;
        case PieceType::Knight:
            os << "N";
            break;
        case PieceType::King:
            os << "K";
            break;
        case PieceType::Bishop:
            os << "B";
            break;
        case PieceType::Rook:
            os << "R";
            break;
    }

    os << "\033[0m";
    return os;
}
