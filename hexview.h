#ifndef HEXVIEW_H
#define HEXVIEW_H

#include <QQuickPaintedItem>
#include <QRect>
#include <QPainter>
#include <QString>
#include <hexmodel.h>

class HexView : public QQuickPaintedItem
{
    Q_OBJECT

public:

    Q_PROPERTY(HexModel* model READ model WRITE setModel NOTIFY modelChanged)
    Q_PROPERTY(int offsetLen READ offsetLen WRITE setOffsetLen )
    Q_PROPERTY(int spacer READ spacer WRITE setSpacer )
    Q_PROPERTY(int hexSpacer READ hexSpacer WRITE setHexSpacer)
    Q_PROPERTY(int asciiSpacer READ asciiSpacer WRITE setAsciiSpacer )
    Q_PROPERTY(int bytesPerRow READ bytesPerRow WRITE setBytesPerRow )
    Q_PROPERTY(int offsetsWidth READ offsetsWidth WRITE setOffsetsWidth )
    Q_PROPERTY(int rowHeight READ rowHeight WRITE setRowHeight )
    Q_PROPERTY(int contentHeight READ contentHeight  NOTIFY contentHeightChanged)
    Q_PROPERTY(int contentWidth READ contentWidth  NOTIFY contentWidthChanged)
    Q_PROPERTY(int rowCount READ rowCount  )
    Q_PROPERTY(bool showOffsets WRITE setShowOffsets READ showOffsets  )
    Q_PROPERTY(bool showHex WRITE setShowHex READ showHex  )
    Q_PROPERTY(bool showAscii WRITE setShowAscii READ showAscii )
    Q_PROPERTY(QRect viewport READ viewport WRITE setViewport )


    HexView();
    void paint(QPainter *painter);

    int offsetLen() const;
    void setOffsetLen(int offsetLen);

    int spacer() const;
    void setSpacer(int spacer);

    int hexSpacer() const;
    void setHexSpacer(int hexSpacer);

    int asciiSpacer() const;
    void setAsciiSpacer(int asciiSpacer);

    int bytesPerRow() const;
    void setBytesPerRow(int bytesPerRow);


    QRect getRectforByteHexValue(int offset);
    QRect getRectforByteAscii(int offset);
    int getRowForY(int y);
    int getColForX(int x);


    int offsetsWidth() const;
    void setOffsetsWidth(int offsetsWidth);

    int rowHeight() const;
    void setRowHeight(int rowHeight);

    int contentWidth() const;
    int contentHeight() const;



    int contentLength() const;
    void setContentLength(int contentLength);

    int rowCount() const;
    void setRowCount(int rowCount);

    bool showAscii() const;
    void setShowAscii(bool showAscii);

    bool showHex() const;
    void setShowHex(bool showHex);

    bool showOffsets() const;
    void setShowOffsets(bool showOffsets);

    QRect viewport() const;
    void setViewport( QRect viewport);

    HexModel *model() const;
    void setModel(HexModel *model);

signals:

    void contentHeightChanged();
    void contentWidthChanged();
    void modelChanged();



public slots:
    void sizeChanged();

private:

    HexModel* model_;

    int offsetLen_;
    int spacer_;
    int hexSpacer_;
    int asciiSpacer_;
    int bytesPerRow_;
    int offsetsWidth_;
    int rowHeight_;
    int contentWidth_;
    int contentHeight_;

    int contentLength_;
    int rowCount_;

    bool showAscii_;
    bool showHex_;
    bool showOffsets_;
     QRect viewport_;

    bool showGuidelines_;

    void setContentWidth(int contentWidth);
    void setContentHeight(int contentHeight);

    void recalcWidth();
    void recalcHeight();
    void rowsChanged();
    void columnsChanged();


    int value(int offset);

    QString getHexNumber(int number,int padding=0,bool formatted=false);

    void paintOffsets(QPainter* painter,int& left,int first,int last);
    void paintHex(QPainter* painter,int& left,int first, int last);
    void paintAscii(QPainter* painter,int& left,int first, int last);


};

#endif // HEXVIEW_H
