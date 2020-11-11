#ifndef PLAYERS_H
#define PLAYERS_H

#include <QString>
#include <QHash>

enum class Square {
    Empty = 0,
    Cross = 1,
    Circle = 2
};

class SquareToString {
public:
    explicit SquareToString(Square player) : m_player(player)
    {
        m_conversionTable[static_cast<int>(Square::Empty)] = QString("NoMarker.png");
        m_conversionTable[static_cast<int>(Square::Circle)] = QString("RedCircle.png");
        m_conversionTable[static_cast<int>(Square::Cross)] = QString("BlueCross.png");
    }
    operator QString () const { return m_conversionTable[static_cast<int>(m_player)];}
private:
    Square m_player;
    QHash<int, QString> m_conversionTable;
};

struct Vector2{
    int x,y;
};

#endif // PLAYERS_H
