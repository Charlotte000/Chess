#include "Board.h"
#include <algorithm>

const std::vector<Coordinate> Board::knightDeltas
{ { -2, -1 }, { -1, -2 }, { 1, -2 }, { 2, -1 }, { 2, 1 }, { 1, 2 }, { -1, 2 }, { -2, 1 } };

const std::vector<Coordinate> Board::kingDeltas
{ { -1, -1 }, { 0, -1 }, { 1, -1 }, { 1, 0 }, { 1, 1 }, { 0, 1 }, { -1, 1 }, { -1, 0 } };

const std::vector<Coordinate> Board::bishopDirections
{ { -1, -1 }, { 1, -1 }, { 1, 1 }, { -1, 1 } };

const std::vector<Coordinate> Board::rookDirections
{ { -1, 0 }, { 1, 0}, { 0, -1 }, { 0, 1 } };

Board::Board()
{
    for (int y = 0; y < 8; y++)
    {
        std::vector<Piece> row;
        for (int x = 0; x < 8; x++)
        {
            row.push_back(Piece(PieceColor::Black, PieceType::Empty));
        }

        this->board.push_back(row);
    }
}

void Board::move(Move move)
{
    Piece piece = this->board[move.begin.y][move.begin.x];
    this->board[move.end.y][move.end.x] = piece;
    this->board[move.begin.y][move.begin.x] = Piece(PieceColor::Black, PieceType::Empty);

    this->updateChecks();
    this->updateEvaluations();
}

bool Board::getCheck(PieceColor color) const
{
    return color == PieceColor::White ? this->whiteCheck : this->blackCheck;
}

int Board::getEvaluation(PieceColor color) const
{
    return color == PieceColor::White ? this->whiteEvaluation : -this->whiteEvaluation;
}

std::vector<Move> Board::getAvailableMoves(PieceColor color) const
{
    std::vector<Move> moves;
    for (int y = 0; y < 8; y++)
    {
        for (int x = 0; x < 8; x++)
        {
            const Piece& piece = this->board[y][x];
            if (piece.type == PieceType::Empty || piece.color != color)
            {
                continue;
            }

            this->getAvailablePieceMove(moves, Coordinate { x, y });
        }
    }

    return moves;
}

std::vector<std::pair<int, Move>> Board::getEvaluateMoves(PieceColor color) const
{
    std::vector<std::pair<int, Move>> rating;

    for (const Move& move : this->getAvailableMoves(color))
    {
        Board boardCopy = *this;
        boardCopy.move(move);
        rating.push_back({ boardCopy.getEvaluation(color), move });
    }

    std::sort(rating.begin(), rating.end(), [](const std::pair<int, Move>& a, const std::pair<int, Move>& b) { return a.first > b.first; });
    return rating;
}

std::ostream& operator<<(std::ostream& os, const Board& board)
{
    os << "  abcdefgh" << std::endl;
    for (int y = 0; y < 8; y++)
    {
        os << 8 - y << ' ';
        for (int x = 0; x < 8; x++)
        {
            os << board.board[y][x];
        }

        os << std::endl;
    }

    return os;
}

Piece& Board::operator[](Coordinate coord)
{
    return this->board[coord.y][coord.x];
}

Piece Board::operator[](Coordinate coord) const
{
    return this->board[coord.y][coord.x];
}

void Board::getAvailablePieceMove(std::vector<Move>& moves, Coordinate begin) const
{
    const Piece& piece = this->board[begin.y][begin.x];
    switch (piece.type)
    {
        case PieceType::Empty:
        {
            break;
        }
        case PieceType::Pawn:
        {
            int deltaY = piece.color == PieceColor::White ? -1 : 1;

            // Move
            this->checkOccupy(moves, Move { begin, begin + Coordinate { 0, deltaY } });

            // Big move
            if (piece.color == PieceColor::White && begin.y == 6 || piece.color == PieceColor::Black && begin.y == 1)
            {
                this->checkOccupy(moves, Move { begin, begin + Coordinate { 0, deltaY * 2 } });
            }

            // Capture
            this->checkAttack(moves, piece.color, Move { begin, begin + Coordinate { -1, deltaY } });
            this->checkAttack(moves, piece.color, Move { begin, begin + Coordinate { 1, deltaY } });
            break;
        }
        case PieceType::Knight:
        {
            for (const Coordinate& delta : Board::knightDeltas)
            {
                this->checkAttackOrOccupy(moves, piece.color, Move { begin, begin + delta });
            }

            break;
        }
        case PieceType::King:
        {
            for (const Coordinate& delta : Board::kingDeltas)
            {
                this->checkAttackOrOccupy(moves, piece.color, Move { begin, begin + delta });
            }

            break;
        }
        case PieceType::Bishop:
        {
            for (const Coordinate& direction : Board::bishopDirections)
            {
                for (int i = 1; i < 8; i++)
                {
                    Move move { begin, begin + Coordinate { i * direction.x, i * direction.y } };
                    if (this->checkAttack(moves, piece.color, move) || !this->checkOccupy(moves, move))
                    {
                        break;
                    }
                }
            }

            break;
        }
        case PieceType::Rook:
        {
            for (const Coordinate& direction : Board::rookDirections)
            {
                for (int i = 1; i < 8; i++)
                {
                    Move move { begin, begin + Coordinate { i * direction.x, i * direction.y } };
                    if (this->checkAttack(moves, piece.color, move) || !this->checkOccupy(moves, move))
                    {
                        break;
                    }
                }
            }

            break;
        }
    }
}

bool Board::inBound(Coordinate coord) const
{
    return coord.y >= 0 && coord.x >= 0 && coord.y < 8 && coord.x < 8;
}

bool Board::checkOccupy(std::vector<Move>& moves, Move move) const
{
    if (!this->inBound(move.end))
    {
        return false;
    }

    const Piece& piece = this->board[move.end.y][move.end.x];
    if (piece.type != PieceType::Empty)
    {
        return false;
    }

    moves.push_back(move);
    return true;
}

bool Board::checkAttack(std::vector<Move>& moves, PieceColor originColor, Move move) const
{
    if (!this->inBound(move.end))
    {
        return false;
    }

    const Piece& piece = this->board[move.end.y][move.end.x];
    if (piece.type == PieceType::Empty || piece.color == originColor)
    {
        return false;
    }

    moves.push_back(move);
    return true;
}

bool Board::checkAttackOrOccupy(std::vector<Move>& moves, PieceColor originColor, Move move) const
{
    if (!this->inBound(move.end))
    {
        return false;
    }

    const Piece& piece = this->board[move.end.y][move.end.x];
    if (piece.type != PieceType::Empty && piece.color == originColor)
    {
        return false;
    }
    
    moves.push_back(move);
    return true;
}

void Board::updateChecks()
{
    this->whiteCheck = this->blackCheck = false;
    for (int y = 0; y < 8; y++)
    {
        for (int x = 0; x < 8; x++)
        {
            const Piece& piece = this->board[y][x];
            if (piece.type != PieceType::King)
            {
                continue;
            }

            Coordinate king { x, y };

            for (const Move& move : this->getAvailableMoves((PieceColor)(!(bool)piece.color)))
            {
                if (move.end == king)
                {
                    if (piece.color == PieceColor::White)
                    {
                        this->blackCheck = true;
                    }
                    else
                    {
                        this->whiteCheck = true;
                    }

                    break;
                }
            }
        }
    }
}

void Board::updateEvaluations()
{
    this->whiteEvaluation = 0;

    for (int y = 0; y < 8; y++)
    {
        for (int x = 0; x < 8; x++)
        {
            const Piece& piece = this->board[y][x];
            int delta = piece.color == PieceColor::White ? 1 : -1;
            switch (piece.type)
            {
                case PieceType::Empty:
                    break;
                case PieceType::Pawn:
                    this->whiteEvaluation += 1 * delta;
                    break;
                case PieceType::Knight:
                    this->whiteEvaluation += 3 * delta;
                    break;
                case PieceType::Bishop:
                    this->whiteEvaluation += 3 * delta;
                    break;
                case PieceType::Rook:
                    this->whiteEvaluation += 5 * delta;
                    break;
                case PieceType::King:
                    if (this->getCheck(PieceColor::White))
                    {
                        this->whiteEvaluation += 1000;
                    }
                    
                    if (this->getCheck(PieceColor::Black))
                    {
                        this->whiteEvaluation -= 1000;
                    }
                    break;
            }
        }
    }
}
