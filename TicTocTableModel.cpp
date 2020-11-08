#include "TicTocTableModel.h"

#include <iostream>

TicTocTableModel::TicTocTableModel(QObject * parent) : m_board()
{
    connect(&m_board, &TicTacToeBoard::squareChanged, this, [this](Vector2 position){
        emit dataChanged(index(position.x, position.y), index(position.x, position.y));
    });

    connect(&m_board, &TicTacToeBoard::squaresChanged, this, [this](){
        emit dataChanged(index(0,0), index(rowCount(), columnCount()));
    });
}

TicTocTableModel::~TicTocTableModel()
{
    m_board.disconnect(); // TODO: Read up on this function
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
        return QVariant(PlayerToString(m_board.getSquare({index.row(), index.column()})));
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
        m_board.playerPlaceMarker({row, column});
    }  catch (std::logic_error e) {
        std::cerr << e.what() << std::endl;
    }
}

void TicTocTableModel::player_set_piece(int piece_id)
{
    m_board.init(static_cast<Player>(piece_id), std::make_shared<TicTacToeStrategy>());
}


