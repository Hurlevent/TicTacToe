#include "tictactoegame.h"

#include <array>
#include <iostream>

TicTacToeGame::TicTacToeGame() : m_board(std::make_shared<TicTacToeBoard>()), m_opponent_behavour()
{
    connect(m_board.get(), &TicTacToeBoard::squareChanged, this, [this](Vector2 position){
        emit squareChanged(position);
    });

    connect(m_board.get(), &TicTacToeBoard::squaresChanged, this, [this](){
        emit squaresChanged();
    });
}

TicTacToeGame::~TicTacToeGame()
{
    m_board->disconnect();
}

void TicTacToeGame::init(Square player_marker)
{
    m_player_marker = player_marker;
    m_opponent_marker = player_marker == Square::Circle ? Square::Cross : Square::Circle;

    m_board->reset_board();
}

void TicTacToeGame::reset()
{
    m_board->reset_board();
}

bool TicTacToeGame::has_started() const
{
    return m_player_marker != Square::Empty && m_opponent_marker != Square::Empty;
}

void TicTacToeGame::update(Vector2 player_clicked)
{
    assert(has_started());

    try{
        m_board->place_marker(player_clicked, m_player_marker);

        if(!check_for_winners()){
            auto opponent_move = m_opponent_behavour.choose_move(m_board, m_opponent_marker);

            m_board->place_marker(opponent_move, m_opponent_marker);

            check_for_winners();
        }

    } catch(std::logic_error e){
        std::cerr << e.what() << std::endl;
    }
}

Square TicTacToeGame::get_square(Vector2 position) const
{
    return m_board->getSquare(position);
}

bool TicTacToeGame::check_for_winners()
{
    auto winner = m_board->has_winner();

    if(winner == Square::Circle){
        emit gameOver(QString("Circle has won!"));
        return true;
    }
    else if(winner == Square::Cross){
        emit gameOver(QString("Cross has won!"));
        return true;
    }
    else if(!m_board->has_space_left())
    {
        emit gameOver(QString("It's a draw!"));
        return true;
    }
    return false;
}

