#include "TicTocTableModel.h"

#include <iostream>

TicTocTableModel::TicTocTableModel(QObject * parent) : m_game(), m_hasStarted(false), m_gameOverMessage(QString())
{
    connect(&m_game, &TicTacToeGame::squareChanged, this, [this](Vector2 position){
        emit dataChanged(index(position.x, position.y), index(position.x, position.y));
    });

    connect(&m_game, &TicTacToeGame::squaresChanged, this, [this](){
        emit dataChanged(index(0,0), index(rowCount() - 1, columnCount() - 1));
    });

    connect(&m_game, &TicTacToeGame::gameOver, this, [this](QString message){
        m_hasStarted = false;
        emit hasStartedChanged();
        m_gameOverMessage = message;
        emit gameOverMessageChanged();
    });
}

TicTocTableModel::~TicTocTableModel()
{
    m_game.disconnect(); // TODO: Read up on this function
}

int TicTocTableModel::rowCount(const QModelIndex &parent) const
{
    return TicTacToeBoard::BoardSizeX;
}

int TicTocTableModel::columnCount(const QModelIndex &parent) const
{
    return TicTacToeBoard::BoardSizeY;
}

QVariant TicTocTableModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
            return QVariant();

    switch(role){
        case ImagePathRole:
        return QVariant(PlayerToString(m_game.get_square({index.row(), index.column()})));
    }

    return QVariant();
}

QHash<int, QByteArray> TicTocTableModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[ImagePathRole] = "path";

    return roles;
}

void TicTocTableModel::interact(const int row, const int column)
{
    try {
        m_game.update({row, column});
    }  catch (std::logic_error e) {
        std::cerr << e.what() << std::endl;
    }
}

void TicTocTableModel::player_set_piece(int piece_id)
{
    m_game.init(static_cast<Player>(piece_id));
    m_hasStarted = true;
    emit hasStartedChanged();
}

QString TicTocTableModel::getGameOverMessage() const
{
    return m_gameOverMessage;
}

bool TicTocTableModel::getHasStarted() const
{
    return m_hasStarted;
}


