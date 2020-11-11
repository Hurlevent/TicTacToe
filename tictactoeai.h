#ifndef TICTACTOESTRATEGY_H
#define TICTACTOESTRATEGY_H

#include <memory>

#include "common.h"
#include "tictactoeboard.h"

struct Choice{

    Choice();
    Choice(Vector2 mv, int val, int dep);
    Choice(const Choice & other);
    Choice & operator=(const Choice & other);

    Vector2 move;
    int value;
    int depth;

};

class TicTacToeAI
{
public:
    explicit TicTacToeAI();

    Vector2 choose_move(const std::shared_ptr<TicTacToeBoard> & board, Square opponent);

    Choice minimax(const TicTacToeBoard * board, bool best, Square opponent, int depth);

};

#endif // TICTACTOESTRATEGY_H
