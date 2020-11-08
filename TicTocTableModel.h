#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include "QAbstractTableModel"
#include "Players.h"

#include "tictactoeboard.h"

class TicTocTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    enum TableRoles {
       ImagePathRole = Qt::UserRole + 1,
    };

    explicit TicTocTableModel(QObject * parent = nullptr);
    virtual ~TicTocTableModel();

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE void interact(const int row, const int column);

    Q_INVOKABLE void player_set_piece(int piece_id);

private:
    TicTacToeBoard m_board;
};

#endif // TABLEMODEL_H


