#ifndef TICTACTOESTRATEGY_H
#define TICTACTOESTRATEGY_H

#include <memory>

#include "Players.h"
#include "tictactoeboard.h"

struct choice{

    choice();
    choice(Vector2 mv, int val, int dep);
    choice(const choice & other);
    choice & operator=(const choice & other);

    Vector2 move;
    int value;
    int depth;

};

class TicTacToeStrategy
{
public:
    explicit TicTacToeStrategy();

    Vector2 choose_move(const std::shared_ptr<TicTacToeBoard> & board, Player opponent);

    choice minimax(const TicTacToeBoard * board, bool best, Player opponent, int depth);

};

#endif // TICTACTOESTRATEGY_H
