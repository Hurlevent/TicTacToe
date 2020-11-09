#include "tictactoeboard.h"

#include <stdexcept>

#include <iostream>

TicTacToeBoard::TicTacToeBoard()
    : m_board{{Player::Empty, Player::Empty, Player::Empty}, {Player::Empty, Player::Empty, Player::Empty}, {Player::Empty, Player::Empty, Player::Empty}}
{}

TicTacToeBoard::TicTacToeBoard(const TicTacToeBoard &other)
{
    for(auto x = 0; x < BoardSizeX; ++x){
        for(auto y = 0; y < BoardSizeY; ++y){
            m_board[x][y] = other.m_board[x][y];
        }
    }
}

TicTacToeBoard& TicTacToeBoard::operator=(const TicTacToeBoard &other)
{
    for(auto x = 0; x < BoardSizeX; ++x){
        for(auto y = 0; y < BoardSizeY; ++y){
            m_board[x][y] = other.m_board[x][y];
        }
    }
    return *this;
}

void TicTacToeBoard::reset_board()
{
    for(auto x = 0; x < BoardSizeX; ++x){
        for(auto y = 0; y < BoardSizeY; ++y){
            m_board[x][y] = Player::Empty;
        }
    }

    std::cout << "Reset board" << std::endl;

    m_moves.clear();

    emit squaresChanged();
}

bool positionOutOfBounds(Vector2 position)
{
    return position.x >= TicTacToeBoard::BoardSizeX || position.x < 0 || position.y >= TicTacToeBoard::BoardSizeY || position.y < 0;
}


void TicTacToeBoard::place_marker(Vector2 position, Player marker)
{
    std::cout << "player marker for " << (marker == Player::Circle ? "Circle" : "Cross") << std::endl;

    if(positionOutOfBounds(position))
        std::cerr << "Position out of bounds" << std::endl;

    if(m_board[position.x][position.y] != Player::Empty)
        std::cerr << "Cannot place marker on top of existing marker" << std::endl;

    m_board[position.x][position.y] = marker;
    m_moves.push_back(position);

    emit squareChanged(position);
}

Player TicTacToeBoard::getSquare(Vector2 position) const
{
    if(positionOutOfBounds(position))
        throw std::out_of_range("Position out of bounds");

    return m_board[position.x][position.y];
}

int get_unique_values(std::array<Player, 3> line){
    std::vector<Player> v(std::begin(line), std::end(line));

    auto last = std::unique(v.begin(), v.end());

    v.erase(last, v.end());

    return v.size();
}

Player TicTacToeBoard::has_winner() const
{
    auto r1 = std::array<Player, 3>{m_board[0][0], m_board[0][1], m_board[0][2]};
    if(get_unique_values(r1) == 1 && r1[0] != Player::Empty) return r1[0];

    auto r2 = std::array<Player, 3>{m_board[1][0], m_board[1][1], m_board[1][2]};
    if(get_unique_values(r2) == 1 && r2[0] != Player::Empty) return r2[0];

    auto r3 = std::array<Player, 3>{m_board[2][0], m_board[2][1], m_board[2][2]};
    if(get_unique_values(r3) == 1 && r3[0] != Player::Empty) return r3[0];

    auto c1 = std::array<Player, 3>{m_board[0][0], m_board[1][0], m_board[2][0]};
    if(get_unique_values(c1) == 1 && c1[0] != Player::Empty) return c1[0];

    auto c2 = std::array<Player, 3>{m_board[0][1], m_board[1][1], m_board[2][1]};
    if(get_unique_values(c2) == 1 && c2[0] != Player::Empty) return c2[0];

    auto c3 = std::array<Player, 3>{m_board[0][2], m_board[1][2], m_board[2][2]};
    if(get_unique_values(c3) == 1 && c3[0] != Player::Empty) return c3[0];

    auto d1 = std::array<Player, 3>{m_board[0][0], m_board[1][1], m_board[2][2]};
    if(get_unique_values(d1) == 1 && d1[0] != Player::Empty) return d1[0];

    auto d2 = std::array<Player, 3>{m_board[2][0], m_board[1][1], m_board[0][2]};
    if(get_unique_values(d2) == 1 && d2[0] != Player::Empty) return d2[0];

    return Player::Empty;
}

bool TicTacToeBoard::has_space_left() const
{
    for(auto x = 0; x < BoardSizeX; ++x){
        for(auto y = 0; y < BoardSizeY; ++y){
            if(m_board[x][y] == Player::Empty){
                return true;
            }
        }
    }

    return false;
}

std::vector<Vector2> TicTacToeBoard::legal_moves() const
{
    std::vector<Vector2> options;

    for(auto x = 0; x < BoardSizeX; ++x){
        for(auto y = 0; y < BoardSizeY; ++y){
            if(m_board[x][y] == Player::Empty){
                options.push_back({x,y});
            }
        }
    }

    return options;
}

Vector2 TicTacToeBoard::last_move() const
{
    return m_moves.back();
}

