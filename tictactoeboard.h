#ifndef TICTACTOEBOARD_H
#define TICTACTOEBOARD_H

#include "Players.h"

#include <memory>
#include <vector>

#include <QObject>

// Either make the board an QObject, or change board to table of QObjects

class TicTacToeBoard : public QObject
{
    Q_OBJECT

public:
    explicit TicTacToeBoard();
    explicit TicTacToeBoard(const TicTacToeBoard & other);
    TicTacToeBoard & operator=(const TicTacToeBoard & other);

    void reset_board();
    void place_marker(Vector2 position, Player marker);
    Player getSquare(Vector2 position) const;
    static const unsigned short BoardSizeX = 3;
    static const unsigned short BoardSizeY = 3;

    Player has_winner() const;
    bool has_space_left() const;
    std::vector<Vector2> legal_moves() const;
    Vector2 last_move() const;

signals:
    void squareChanged(Vector2 position);
    void squaresChanged();

private:
    Player m_board[BoardSizeX][BoardSizeY];
    std::vector<Vector2> m_moves; // chould this be done another way?
};

#endif // TICTACTOEBOARD_H
