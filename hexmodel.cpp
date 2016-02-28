#include "hexmodel.h"
#include <QHash>
#include <QByteArray>
#include <QDebug>
#include <QFile>

QString HexViewModel::getHexNumber(int number, int padding, bool formatted) const
{

    QString result= QString::number( number, 16).toUpper();
    result= result.rightJustified( padding, '0' );
    if (formatted) result.prepend("0x");
    return result;
}


QString getPrintable(unsigned char c) {
    if (c >= 0x20 && c <= 0x7f) {
        return QString(c);
    } else {
        return ".";
    }
}

HexViewModel::HexViewModel(QObject* parent)
    : QAbstractListModel(parent)//,bytesPerRow_(16)
{
    QFile file("/Users/James/aaaaa.jpg");
    if (!file.open(QIODevice::ReadOnly)) return;

    array_ = file.readAll();
    connect( this,SIGNAL(bytesPerRowChanged()),
             this,SLOT(handleBytesPerRowChanged()) );
}



QHash<int, QByteArray> HexViewModel::roleNames() const {
    qDebug() << "getRolwName";
    QHash<int, QByteArray> roles;
    roles[HexDataRole] = "hexdata";
    roles[AsciiDataRole] = "asciidata";
    return roles;
}



void HexViewModel::handleBytesPerRowChanged()
{
    beginResetModel();
    endResetModel();
}

QVariant HexViewModel::data(const QModelIndex &index, int role) const
{


    if (index.row() < 0 || index.row() >= rowCount())
        return QVariant();

    int i = index.row();// * bytesPerRow_;
    unsigned char* data = (unsigned char*) array_.data();


    if (role == HexDataRole)   {
        return getHexNumber( data[i],2,false);
    } else {
        return getPrintable(data[i]);
    }


}

int HexViewModel::rowCount(const QModelIndex &parent) const
{
    return  array_.size() ;
}
