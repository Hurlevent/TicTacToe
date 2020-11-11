#ifndef TICTACTOEGAME_H
#define TICTACTOEGAME_H

#include <memory>

#include <QObject>

#include "tictactoeboard.h"
#include "common.h"
#include "tictactoeai.h"

class TicTacToeGame : public QObject
{
    Q_OBJECT
public:
    explicit TicTacToeGame();
    ~TicTacToeGame();

    void init(Square player_marker);
    void reset();
    bool has_started() const;
    void update(Vector2 player_clicked);

    Square get_square(Vector2 position) const;

signals:
    void squareChanged(Vector2 position);
    void squaresChanged();
    void gameOver(QString message);

private:
    Square has_winner() const;
    bool check_for_winners();

    std::shared_ptr<TicTacToeBoard> m_board;
    Square m_player_marker;
    Square m_opponent_marker;

    TicTacToeAI m_opponent_behavour;
};

#endif // TICTACTOEGAME_H
