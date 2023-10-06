#include "Game.h"
#include <iostream>

using namespace std;

int main()
{
    srand(time(NULL));

    Game game;

    game.fill();
    for (int i = 0; i < 30; i++)
    {
        game.randomMove();
    }

    cout << game.board << endl;

    for (const vector<Move>& moves : game.evaluateBestMoves())
    {
        for (const Move& move : moves)
        {
            cout << move.begin << '-' << move.end << "; ";
        }

        cout << endl;
    }

    return 0;
}
