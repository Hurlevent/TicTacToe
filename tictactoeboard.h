#ifndef TICTACTOEBOARD_H
#define TICTACTOEBOARD_H

#include "Players.h"
#include "tictactoestrategy.h"

#include <memory>

#include <QObject>

// Either make the board an QObject, or change board to table of QObjects

class TicTacToeBoard : public QObject
{
    Q_OBJECT

public:
    explicit TicTacToeBoard();

    void init(Player player_marker, std::shared_ptr<TicTacToeStrategy> opponent);
    void playerPlaceMarker(Vector2 position);
    Player getSquare(Vector2 position) const;
    static const unsigned short BoardSizeX = 3;
    static const unsigned short BoardSizeY = 3;

signals:
    void squareChanged(Vector2 position);
    void squaresChanged();

private:
    static bool positionOutOfBounds(Vector2 position);

    Player m_board[BoardSizeX][BoardSizeY];
    Player m_player_marker;

    std::shared_ptr<TicTacToeStrategy> m_opponent;
};

#endif // TICTACTOEBOARD_H
