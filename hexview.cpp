#include "hexview.h"
#include <QDebug>

#include <cctype>

HexView::HexView()
    : showGuidelines_(false),model_(0)
{

    setBytesPerRow( 16 );
    setRowHeight( 20 );
  //  setContentLength(0);
    setShowAscii(true);
    setShowHex(true);
    setShowOffsets(true);
    setOffsetsWidth(100);
    setSpacer(35);
    setHexSpacer(25);
    setAsciiSpacer(15);
    setOffsetLen(6);
     setContentLength(273);
    recalcHeight();
    recalcWidth();
    setRenderTarget(QQuickPaintedItem::FramebufferObject);
}

void HexView::paint(QPainter *painter)
{
    int left = 0;
    int firstRow =  getRowForY( viewport_.y() )  - 1;
    int lastRow =  getRowForY( viewport_.y() + viewport_.height() )  + 1;

    if (firstRow <  0) firstRow = 0;
    if (lastRow >  rowCount() ) lastRow = rowCount();

    painter->setFont(QFont("Courier"));
    qDebug() << "contentlength=" << contentLength()  << " firstrow=" << firstRow << " lastRow=" << lastRow << " viewport="  << viewport_;

    if (showGuidelines_)    {
        QPen backpen(QColor(255,0,0));
        painter->setPen(backpen);
        //painter->drawRect(viewport_);
    }

    if (showOffsets()) {
        paintOffsets(painter,left,firstRow,lastRow);
    }

    if (showHex()) {
        paintHex(painter,left,firstRow,lastRow);
    }

    if (showAscii()) {
        paintAscii(painter,left,firstRow,lastRow);
    }

}

int HexView::offsetLen() const
{
    return offsetLen_;
}

void HexView::setOffsetLen(int offsetLen)
{
    if (offsetLen != offsetLen_) {
        offsetLen_ = offsetLen;
        recalcWidth();
    }
}

int HexView::spacer() const
{

    return spacer_;
}

void HexView::setSpacer(int spacer)
{
    if (spacer != spacer_) {
        spacer_ = spacer;
        recalcWidth();
    }
}

int HexView::hexSpacer() const
{

    return hexSpacer_;
}

void HexView::setHexSpacer(int hexSpacer)
{
    if (hexSpacer_ != hexSpacer) {
        hexSpacer_ = hexSpacer;
        recalcWidth();
    }
}

int HexView::asciiSpacer() const
{
    return asciiSpacer_;
}

void HexView::setAsciiSpacer(int asciiSpacer)
{
    if (asciiSpacer_ != asciiSpacer) {
        asciiSpacer_ = asciiSpacer;
        recalcWidth();
    }
}

int HexView::bytesPerRow() const
{
    return bytesPerRow_;
}

void HexView::setBytesPerRow(int bytesPerRow)
{
    if (bytesPerRow != bytesPerRow_ ) {
        bytesPerRow_ = bytesPerRow;
        recalcWidth();
    }
}

QRect HexView::getRectforByteHexValue(int offset)
{

}

QRect HexView::getRectforByteAscii(int offset)
{

}

int HexView::getRowForY(int y)
{

    float prop  = (float) y / (float) contentHeight();
    return prop * rowCount();
}

int HexView::getColForX(int x)
{

}

int HexView::offsetsWidth() const
{
    return offsetsWidth_;
}

void HexView::setOffsetsWidth(int offsetsWidth)
{
    if (offsetsWidth_ != offsetsWidth) {
        offsetsWidth_ = offsetsWidth;

    }
}

int HexView::rowHeight() const
{
    return rowHeight_;
}

void HexView::setRowHeight(int rowHeight)
{
    if (rowHeight != rowHeight_ ) {
        rowHeight_ = rowHeight;

        recalcHeight();

    }
}

int HexView::contentWidth() const
{
    return contentWidth_;
}

int HexView::contentHeight() const
{
    return contentHeight_;
}

int HexView::contentLength() const
{
    return contentLength_;
}

void HexView::setContentLength(int contentLength)
{
    if (contentLength != contentLength_) {
        contentLength_ = contentLength;
        rowsChanged();
    }
}

int HexView::rowCount() const
{
    return rowCount_;
}

void HexView::setRowCount(int rowCount)
{
    if (rowCount != rowCount_) {
        rowCount_ = rowCount;
        recalcHeight();
    }
}

bool HexView::showAscii() const
{
    return showAscii_;
}

void HexView::setShowAscii(bool showAscii)
{
    showAscii_ = showAscii;
    recalcWidth();
}

bool HexView::showHex() const
{
    return showHex_;

}

void HexView::setShowHex(bool showHex)
{
    showHex_ = showHex;
    recalcWidth();
}

bool HexView::showOffsets() const
{
    return showOffsets_;
}

void HexView::setShowOffsets(bool showOffsets)
{
    showOffsets_ = showOffsets;
    recalcWidth();
}

 QRect HexView::viewport() const
{
    return viewport_;
}

void HexView::setViewport( QRect viewport)
{
    qDebug() << viewport;
    viewport_ = viewport;
    update();
}

HexModel *HexView::model() const
{
    return model_;
}

void HexView::setModel(HexModel *model)
{
    model_ = model;
    qDebug() << "size=" << model->size();
    connect(model,SIGNAL(sizeChanged()),this,SLOT(sizeChanged()));
    setContentLength(model->size());
}

void HexView::sizeChanged()
{
//    if (0 != model_)  {
//        setContentLength(model_->size());
//    }

}

int HexView::value(int offset)
{
    return offset % 256;
    // return model_->getValue(offset);
}

QString HexView::getHexNumber(int number, int padding, bool formatted)
{

    QString result= QString::number(number, 16).toUpper();
    result= result.rightJustified( padding, '0' );
    if (formatted) result.prepend("0x");
    return result;
}

void HexView::paintOffsets(QPainter *painter, int &left,int first, int last)
{
    QPen pen;

    for (int i=first; i<=last ; ++i) {
        QRect offsets(left,rowHeight() * i,offsetsWidth(),rowHeight());

        if (showGuidelines_) {
            pen.setColor(Qt::green);
            painter->setPen(pen);
            painter->drawRect(offsets);
        }

        pen.setColor(Qt::black);
        painter->setPen(pen);
        QString offset = getHexNumber(i * bytesPerRow(),offsetLen(),true);
        painter->drawText( offsets ,Qt::AlignCenter ,offset  );
    }

    left += offsetsWidth();

    if (showGuidelines_) {
        QRect space(left,0,spacer() ,contentHeight());
        pen.setColor(Qt::blue);
        painter->setPen(pen);
        painter->drawRect(space);
    }

    left += spacer();
}

void HexView::paintHex(QPainter *painter, int &left,int first, int last)
{
    QPen pen;

    for (int i=first ;i<=last;++i) {
        for (int j=0;j<bytesPerRow_;++j) {

            int validx = (i * bytesPerRow()) + j;


            if (validx < contentLength_)    {
                int valueint = value(validx);
                QRectF hex(left + (j * hexSpacer()),i * rowHeight() , hexSpacer(),rowHeight());

                if (showGuidelines_) {
                    pen.setColor(Qt::green);
                    painter->setPen(pen);
                    painter->drawRect(hex);
                }


                QString valuestr = getHexNumber(valueint,2);

                pen.setColor(Qt::black);
                painter->setPen(pen);
                painter->drawText( hex ,Qt::AlignCenter,valuestr  );
            }
        }

    }


    left += (bytesPerRow() * hexSpacer());

    if (showGuidelines_) {
        QRect space(left,0,spacer() ,contentHeight());
        pen.setColor(Qt::blue);
        painter->setPen(pen);
        painter->drawRect(space);
    }

   left += spacer();
}

void HexView::paintAscii(QPainter *painter, int &left,int first, int last)
{
    for (int i=first ;i<=last;++i) {
        for (int j=0;j<bytesPerRow_;++j) {

            int validx = (i * bytesPerRow()) + j;

            if (validx < contentLength_) {
                int valueint = value(validx);


                QRectF ascii(left + (j * asciiSpacer()),i * rowHeight(),asciiSpacer(),rowHeight());
                QPen pen;
                pen.setColor(Qt::black);
                 painter->setPen(pen);
                 if (std::isprint(valueint)) {
                     QChar c(valueint);
                     painter->drawText( ascii ,Qt::AlignCenter,QString(c)  );
                 } else {
                     painter->drawText( ascii ,Qt::AlignCenter,"."  );
                 }
            }
        }
    }

}

void HexView::setContentWidth(int contentWidth)
{
    if (contentWidth != contentWidth_ ) {
        contentWidth_ = contentWidth;
        emit contentWidthChanged();
    }
}

void HexView::setContentHeight(int contentHeight)
{
    if (contentHeight != contentHeight_ ) {
        contentHeight_ = contentHeight;
        emit contentHeightChanged();
    }
}

void HexView::recalcWidth()
{
    int sizeOfOffsets = (2 + offsetLen()) * asciiSpacer();
    int spacers = 0;
    if (showOffsets()) {
        spacers += spacer() + sizeOfOffsets;
    }
    if (showHex()) {
        spacers += spacer() + (bytesPerRow() * hexSpacer());
    }
    if (showAscii()) {
        spacers += bytesPerRow() * asciiSpacer();
    }
    setContentWidth( spacers );

}

void HexView::recalcHeight()
{
    setContentHeight( (1 + rowCount() ) * rowHeight()  );
}

void HexView::rowsChanged()
{
    int remainder = contentLength() % bytesPerRow();
    int rowCount = (remainder > 0) ? 1 : 0;

    setRowCount( rowCount + (  contentLength() / bytesPerRow() )  );
}

void HexView::columnsChanged()
{
    int remainder = contentLength() % bytesPerRow();
    int rowCount = (remainder > 0) ? 1 : 0;

    setRowCount( rowCount + (  contentLength() / bytesPerRow() )  );
}
