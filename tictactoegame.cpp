#include "tictactoegame.h"

TicTacToeGame::TicTacToeGame()
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
