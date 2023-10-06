#include "Move.h"

Coordinate Coordinate::operator+(const Coordinate& coord) const
{
    return { this->x + coord.x, this->y + coord.y };
}

bool Coordinate::operator==(const Coordinate& coord) const
{
    return this->x == coord.x && this->y == coord.y;
}

std::ostream& operator<<(std::ostream& os, const Coordinate& coord)
{
    os << (char)(97 + coord.x) << 8 - coord.y;
    return os;
}

std::ostream& operator<<(std::ostream& os, const Move& move)
{
    os << move.begin << " -> " << move.end;
    return os;
}
