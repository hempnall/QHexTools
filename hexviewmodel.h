#ifndef HEXVIEWMODEL_H
#define HEXVIEWMODEL_H

#include <QAbstractListModel>
#include <QByteArray>

class HexViewModel : public QAbstractListModel
{
    Q_OBJECT
    QByteArray array_;


public:

    Q_INVOKABLE QString getHexNumber(int number, int padding, bool formatted) const;
    Q_PROPERTY(QString filename READ filename WRITE setFilename NOTIFY filenameChanged)

    enum AnimalRoles {
        HexDataRole = Qt::UserRole + 1,
        AsciiDataRole,
    };

    HexViewModel() {}
    HexViewModel(const QString& filename, QObject* parent=0);
    QVariant data(const QModelIndex &index, int role=Qt::DisplayRole ) const;
    virtual int rowCount(const QModelIndex & parent = QModelIndex()) const;
    QHash<int, QByteArray> roleNames() const;

    int bytesPerRow() const;
    void setBytesPerRow(int bytesPerRow);

    QString filename() const;
    void setFilename(const QString &filename);

signals:
    void bytesPerRowChanged();
    void filenameChanged();

public slots:
    void handleBytesPerRowChanged();

private:
    QString filename_;

    void loadNewFile() ;

};

#endif // HEXVIEWMODELs_H
