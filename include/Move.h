#pragma once

#include <iostream>

struct Coordinate
{
    int x, y;

    Coordinate operator+(const Coordinate& coord) const;

    bool operator==(const Coordinate& coord) const;

    friend std::ostream& operator<<(std::ostream& os, const Coordinate& coord);
};

struct Move
{
    Coordinate begin;
    Coordinate end;

    friend std::ostream& operator<<(std::ostream& os, const Move& coord);
};
