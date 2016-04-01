#include "hexdata.h"

HexViewModel* HexData::loadFromFile(const QString &filename)
{

    model_ = new HexViewModel(filename);
    emit dataChanged();
    return model_;

}

HexData::HexData() : model_(0)
{

}

HexViewModel *HexData::model() const
{
    return model_;
}

