#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include "QAbstractTableModel"
#include "common.h"

#include "tictactoegame.h"

class TicTacToeTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    enum TableRoles {
       ImagePathRole = Qt::UserRole + 1,
    };

    explicit TicTacToeTableModel(QObject * parent = nullptr);
    virtual ~TicTacToeTableModel();

    Q_PROPERTY(bool started MEMBER m_hasStarted READ getHasStarted NOTIFY hasStartedChanged)
    Q_PROPERTY(QString message MEMBER m_gameOverMessage READ getGameOverMessage NOTIFY gameOverMessageChanged)

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE void interact(const int row, const int column);
    Q_INVOKABLE void player_set_piece(int piece_id);
    Q_INVOKABLE void reset_board();

    bool getHasStarted() const;
    QString getGameOverMessage()const;

signals:
    void hasStartedChanged();
    void gameOverMessageChanged();

private:
    TicTacToeGame m_game;
    bool m_hasStarted;
    QString m_gameOverMessage;
};

#endif // TABLEMODEL_H


