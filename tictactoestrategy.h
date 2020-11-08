#ifndef TICTACTOESTRATEGY_H
#define TICTACTOESTRATEGY_H


#include "Players.h"

#include <array>

class TicTacToeStrategy
{
public:
    explicit TicTacToeStrategy();

    Vector2 get_square_for_opponent(const Player ** board, Player player);

    static void minimax(const Player ** board, Player player, int depth);
    static Player winner(const Player ** board);

    static int get_unique_values(std::array<Player, 3> line);

    static std::array<Player, 3> row1(const Player ** board);
    static std::array<Player, 3> row2(const Player ** board);
    static std::array<Player, 3> row3(const Player ** board);
    static std::array<Player, 3> col1(const Player ** board);
    static std::array<Player, 3> col2(const Player ** board);
    static std::array<Player, 3> col3(const Player ** board);
    static std::array<Player, 3> diag1(const Player ** board);
    static std::array<Player, 3> diag2(const Player ** board);


};

#endif // TICTACTOESTRATEGY_H
