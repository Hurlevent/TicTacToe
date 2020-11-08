#include "tictactoestrategy.h"

#include "tictactoeboard.h"
#include <vector>
#include <algorithm>

TicTacToeStrategy::TicTacToeStrategy()
{

}

Vector2 TicTacToeStrategy::get_square_for_opponent(const Player ** board, Player player)
{
    // check for player win conditions

    auto opponent = player == Player::Circle ? Player::Cross : Player::Circle;



    return Vector2{1,1};
}

void TicTacToeStrategy::minimax(const Player **board, Player player, int depth)
{
    auto win = winner(board);


}

Player TicTacToeStrategy::winner(const Player **board)
{
    auto r1 = row1(board);
    if(get_unique_values(r1) == 1 && r1[0] != Player::Empty) return r1[0];

    auto r2 = row2(board);
    if(get_unique_values(r2) == 1 && r2[0] != Player::Empty) return r2[0];

    auto r3 = row3(board);
    if(get_unique_values(r3) == 1 && r3[0] != Player::Empty) return r3[0];

    auto c1 = col1(board);
    if(get_unique_values(c1) == 1 && c1[0] != Player::Empty) return c1[0];

    auto c2 = col2(board);
    if(get_unique_values(c2) == 1 && c2[0] != Player::Empty) return c2[0];

    auto c3 = col3(board);
    if(get_unique_values(c3) == 1 && c3[0] != Player::Empty) return c3[0];

    auto d1 = diag1(board);
    if(get_unique_values(d1) == 1 && d1[0] != Player::Empty) return d1[0];

    auto d2 = diag2(board);
    if(get_unique_values(d2) == 1 && d2[0] != Player::Empty) return d2[0];

    return Player::Empty;
}

int TicTacToeStrategy::get_unique_values(std::array<Player, 3> line)
{
   std::vector<Player> v(std::begin(line), std::end(line));

   auto last = std::unique(v.begin(), v.end());

   v.erase(last, v.end());

   return v.size();
}

std::array<Player, 3>  TicTacToeStrategy::diag2(const Player **board)
{
    return std::array<Player, 3>{board[2][0], board[1][1], board[0][2]};
}


std::array<Player, 3>  TicTacToeStrategy::diag1(const Player **board)
{
    return std::array<Player, 3>{board[0][0], board[1][1], board[2][2]};
}

std::array<Player, 3> TicTacToeStrategy::col3(const Player **board)
{
    return std::array<Player, 3>{board[0][2], board[1][2], board[2][2]};
}

std::array<Player, 3> TicTacToeStrategy::col2(const Player **board)
{
    return std::array<Player, 3>{board[0][1], board[1][1], board[2][1]};
}

std::array<Player, 3> TicTacToeStrategy::col1(const Player **board)
{
    return std::array<Player, 3>{board[0][0], board[1][0], board[2][0]};
}

std::array<Player, 3> TicTacToeStrategy::row3(const Player **board)
{
    return std::array<Player, 3>{board[2][0], board[2][1], board[2][2]};
}

std::array<Player, 3> TicTacToeStrategy::row2(const Player **board)
{
    return std::array<Player, 3>{board[1][0], board[1][1], board[1][2]};
}

std::array<Player, 3> TicTacToeStrategy::row1(const Player **board)
{
    return std::array<Player, 3>{board[0][0], board[0][1], board[0][2]};
}
