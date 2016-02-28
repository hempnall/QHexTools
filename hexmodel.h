#ifndef HEXVIEWMODEL_H
#define HEXVIEWMODEL_H

#include <QAbstractListModel>
#include <QByteArray>

class HexViewModel : public QAbstractListModel
{
    Q_OBJECT
//    Q_PROPERTY(int bytesPerRow READ bytesPerRow WRITE setBytesPerRow NOTIFY bytesPerRowChanged)
    QByteArray array_;
public:

    Q_INVOKABLE QString getHexNumber(int number, int padding, bool formatted) const;

    enum DataRoles {
        HexDataRole = Qt::UserRole + 1,
        AsciiDataRole,

    };
    HexViewModel(QObject* parent=0);
    QVariant data(const QModelIndex &index, int role=Qt::DisplayRole ) const;
    virtual int rowCount(const QModelIndex & parent = QModelIndex()) const;
    QHash<int, QByteArray> roleNames() const;

    int bytesPerRow() const;
    void setBytesPerRow(int bytesPerRow);

signals:
    void bytesPerRowChanged();
public slots:
    void handleBytesPerRowChanged();

private:
  //  int bytesPerRow_;

};

#endif // HEXVIEWMODEL_H
