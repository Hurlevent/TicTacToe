#ifndef PLAYERS_H
#define PLAYERS_H

#include <QString>
#include <QHash>


// Rename to Tile or something
enum class Player {
    Empty = 0,
    Cross = 1,
    Circle = 2
};

class PlayerToString {
public:
    explicit PlayerToString(Player player) : m_player(player)
    {
        m_conversionTable[static_cast<int>(Player::Empty)] = QString("null");
        m_conversionTable[static_cast<int>(Player::Circle)] = QString("RedCircle.png");
        m_conversionTable[static_cast<int>(Player::Cross)] = QString("RedCross.png");
    }
    operator QString () const { return m_conversionTable[static_cast<int>(m_player)];}
private:
    Player m_player;
    QHash<int, QString> m_conversionTable;
};

struct Vector2{
    int x,y;
};

#endif // PLAYERS_H
