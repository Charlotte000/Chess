#include "Game.h"
#include <limits>

void Game::fill(unsigned int pawnCount, unsigned int knightCount, unsigned int bishopCount, unsigned int rookCount)
{
    pawnCount = std::min(pawnCount, 8u);
    knightCount = std::min(knightCount, 2u);
    bishopCount = std::min(bishopCount, 2u);
    rookCount = std::min(rookCount, 2u);

    // === Black ===

    // 1 row
    for (int i = 0; i < rookCount; i++)
    {
        this->board[Coordinate { i * 7, 0 }] = Piece(PieceColor::Black, PieceType::Rook);
    }

    for (int i = 0; i < knightCount; i++)
    {
        this->board[Coordinate { i * 5 + 1, 0 }] = Piece(PieceColor::Black, PieceType::Knight);
    }

    for (int i = 0; i < bishopCount; i++)
    {
        this->board[Coordinate { i * 3 + 2, 0 }] = Piece(PieceColor::Black, PieceType::Bishop);
    }

    this->board[Coordinate { 4, 0 }] = Piece(PieceColor::Black, PieceType::King);
    
    // 2 row
    for (int i = 0; i < pawnCount; i++)
    {
        this->board[Coordinate { i, 1 }] = Piece(PieceColor::Black, PieceType::Pawn);
    }

    // === White ===

    // 1 row
    for (int i = 0; i < pawnCount; i++)
    {
        this->board[Coordinate { i, 6 }] = Piece(PieceColor::White, PieceType::Pawn);
    }

    // 2 row
    for (int i = 0; i < rookCount; i++)
    {
        this->board[Coordinate { i * 7, 7 }] = Piece(PieceColor::White, PieceType::Rook);
    }

    for (int i = 0; i < knightCount; i++)
    {
        this->board[Coordinate { i * 5 + 1, 7 }] = Piece(PieceColor::White, PieceType::Knight);
    }

    for (int i = 0; i < bishopCount; i++)
    {
        this->board[Coordinate { i * 3 + 2, 7 }] = Piece(PieceColor::White, PieceType::Bishop);
    }

    this->board[Coordinate { 4, 7 }] = Piece(PieceColor::White, PieceType::King);
}

void Game::randomMove()
{
    std::vector<Move> availableMoves = this->board.getAvailableMoves(this->turn);
    if (availableMoves.size() <= 0)
    {
        return;
    }

    const Move& move = availableMoves[std::rand() % availableMoves.size()];
    this->board.move(move);
    this->changeTurn();
}

std::vector<std::vector<Move>> Game::evaluateBestMoves()
{
    std::vector<std::vector<Move>> result;
    for (int i = 0; i < 3; i++)
    {
        std::vector<Move> moves;
        Board boardCopy = this->board;
        for (int j = 0; j < 3; j++)
        {
            Move move = boardCopy.getEvaluateMoves(this->turn)[i].second;
            boardCopy.move(move);
            moves.push_back(move);

            if (boardCopy.getCheck(this->turn))
            {
                break;
            }
        }

        result.push_back(moves);
    }

    return result;
}

void Game::changeTurn()
{
    this->turn = (PieceColor)(!(bool)this->turn);
}
