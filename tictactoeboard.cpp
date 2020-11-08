#include "tictactoeboard.h"

#include <stdexcept>

#include <iostream>

TicTacToeBoard::TicTacToeBoard()
    : m_board{{Player::Empty, Player::Empty, Player::Empty}, {Player::Empty, Player::Empty, Player::Empty}, {Player::Empty, Player::Empty, Player::Empty}},
      m_player_marker(Player::Empty),
      m_opponent(nullptr)
{}

void TicTacToeBoard::init(Player player_marker, std::shared_ptr<TicTacToeStrategy> opponent)
{
    for(auto x = 0; x < BoardSizeX; ++x){
        for(auto y = 0; y < BoardSizeY; ++y){
            m_board[x][y] = Player::Empty;
        }
    }
    m_player_marker = player_marker;
    m_opponent = opponent;

    std::cout << "Board has been initialized with player marker " << static_cast<int>(m_player_marker) << std::endl;

    emit squaresChanged();
}

void TicTacToeBoard::playerPlaceMarker(Vector2 position)
{
    if(positionOutOfBounds(position))
        throw std::out_of_range("Position out of bounds");

    if(m_player_marker == Player::Empty)
        throw std::logic_error("Player marker cannot be empty");

    if(m_board[position.x][position.y] != Player::Empty)
        throw std::logic_error("Cannot place marker on top of existing marker");

    m_board[position.x][position.y] = m_player_marker;

    emit squareChanged(position);
}

Player TicTacToeBoard::getSquare(Vector2 position) const
{
    if(positionOutOfBounds(position))
        throw std::out_of_range("Position out of bounds");

    return m_board[position.x][position.y];
}

bool TicTacToeBoard::positionOutOfBounds(Vector2 position)
{
    return position.x >= BoardSizeX || position.x < 0 || position.y >= BoardSizeY || position.y < 0;
}
