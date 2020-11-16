#include "TicTacToeTableModel.h"

#include <iostream>

TicTacToeTableModel::TicTacToeTableModel(QObject * parent) : m_board(std::make_shared<TicTacToeBoard>()), m_game(m_board), m_hasStarted(false), m_gameOverMessage(QString())
{
    connect(m_board.get(), &TicTacToeBoard::squareChanged, this, [this](Vector2 position){
        emit dataChanged(index(position.x, position.y), index(position.x, position.y));
    });

    connect(m_board.get(), &TicTacToeBoard::squaresChanged, this, [this](){
        emit dataChanged(index(0,0), index(rowCount() - 1, columnCount() - 1));
    });

    connect(&m_game, &TicTacToeGame::gameOver, this, [this](QString message){
        m_hasStarted = false;
        emit hasStartedChanged();
        m_gameOverMessage = message;
        emit gameOverMessageChanged();
    });
}

TicTacToeTableModel::~TicTacToeTableModel()
{
    m_game.disconnect(); // TODO: Read up on this function
}

int TicTacToeTableModel::rowCount(const QModelIndex &parent) const
{
    return TicTacToeBoard::BoardSizeX;
}

int TicTacToeTableModel::columnCount(const QModelIndex &parent) const
{
    return TicTacToeBoard::BoardSizeY;
}

QVariant TicTacToeTableModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
            return QVariant();

    switch(role){
        case ImagePathRole:
        return QVariant(SquareToString(m_board->getSquare({index.row(), index.column()})));
    }

    return QVariant();
}

QHash<int, QByteArray> TicTacToeTableModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[ImagePathRole] = "path";

    return roles;
}

void TicTacToeTableModel::interact(const int row, const int column)
{
    try {
        m_game.update({row, column});
    }  catch (std::logic_error e) {
        std::cerr << e.what() << std::endl;
    }
}

void TicTacToeTableModel::player_set_piece(int piece_id)
{
    m_game.init(static_cast<Square>(piece_id));
    m_hasStarted = true;
    emit hasStartedChanged();
}

void TicTacToeTableModel::reset_board()
{
    m_board->reset_board();

    m_gameOverMessage = QString();
    emit gameOverMessageChanged();
}

QString TicTacToeTableModel::getGameOverMessage() const
{
    return m_gameOverMessage;
}

bool TicTacToeTableModel::getHasStarted() const
{
    return m_hasStarted;
}


