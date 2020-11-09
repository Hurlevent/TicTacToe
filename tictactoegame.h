#ifndef TICTACTOEGAME_H
#define TICTACTOEGAME_H

#include <memory>
#include <functional>

#include <QObject>

#include "tictactoeboard.h"
#include "Players.h"
#include "tictactoestrategy.h"

class TicTacToeGame : public QObject
{
    Q_OBJECT
public:
    explicit TicTacToeGame();
    ~TicTacToeGame();

    void init(Player player_marker);
    void reset();
    bool has_started() const;
    void update(Vector2 player_clicked);

    Player get_square(Vector2 position) const;

signals:
    void squareChanged(Vector2 position);
    void squaresChanged();
    void gameOver(QString message);

private:
    Player has_winner() const;
    bool check_for_winners();

    std::shared_ptr<TicTacToeBoard> m_board;
    Player m_player_marker;
    Player m_opponent_marker;

    TicTacToeStrategy m_opponent_behavour;
};

#endif // TICTACTOEGAME_H
