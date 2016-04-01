#ifndef HEXDATA_H
#define HEXDATA_H

#include <QQuickItem>
#include "hexviewmodel.h"

class HexData : public QQuickItem
{
    Q_OBJECT
public:
    Q_INVOKABLE HexViewModel* loadFromFile(const QString& filename);
    Q_PROPERTY(HexViewModel* model READ model NOTIFY modelChanged);

    HexData();

    HexViewModel *model() const;


signals:
    void modelChanged();
    void dataChanged();

public slots:

private:
    HexViewModel* model_;

};

#endif // HEXDATA_H
