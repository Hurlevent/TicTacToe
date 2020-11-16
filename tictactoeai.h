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
    Choice(Choice && other);
    Choice & operator=(Choice && other);

    Vector2 move;
    int value;
    int depth;

};

class TicTacToeAI {
public:
    virtual Vector2 choose_move(const std::shared_ptr<TicTacToeBoard> & board, Square opponent) = 0;
};


class TicTacToeMinimaxAI : public TicTacToeAI
{
public:
    explicit TicTacToeMinimaxAI();

    Vector2 choose_move(const std::shared_ptr<TicTacToeBoard> & board, Square opponent) override;

private:
    Choice minimax(const TicTacToeBoard * board, bool maximize, Square player, int depth);

};

#endif // TICTACTOESTRATEGY_H
