#ifndef TICTACTOEGAME_H
#define TICTACTOEGAME_H

#include <memory>

#include <QObject>

#include "tictactoeboard.h"
#include "Players.h"

class TicTacToeGame : public QObject
{
    Q_OBJECT
public:
    explicit TicTacToeGame();
    ~TicTacToeGame();

signals:
    void squareChanged(Vector2 position);
    void squaresChanged();

private:
    std::shared_ptr<TicTacToeBoard> m_board;
    Player m_player_marker;
    Player m_opponent_marker;
};

#endif // TICTACTOEGAME_H
