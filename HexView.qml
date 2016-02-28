import QtQuick 2.0
import QtQuick.Layouts 1.1

RowLayout {

    id: rl

    anchors.fill: parent

    property int commonContentTopY : 0

    function handleTopChanged() {

        gvOffsets.contentY = commonContentTopY;
        gvHex.contentY = commonContentTopY;
        gvAscii.contentY = commonContentTopY ;
        gvOffsets.y = rl.y
        gvHex.y = rl.y
        gvAscii.y  = rl.y
    }

    onCommonContentTopYChanged: {
        handleTopChanged();
    }

    ListView {


        id:gvOffsets
        Layout.fillHeight: true
        Layout.alignment: Qt.AlignTop
        Layout.preferredWidth: 100
        boundsBehavior: Flickable.StopAtBounds
        topMargin:  0

        visibleArea.onYPositionChanged: {
            rl.commonContentTopY = contentY
        }

        model: gvHex.contentHeight / gvHex.cellHeight


        delegate: Rectangle {

            id: r

            height: 20
            width: 80

           Text {
                font.family: "Courier"
                text:   xmodel.getHexNumber( index * gvHex.bytesPerRow , 6 , true );
            }
        }
    }


    GridView {

        id: gvHex
        boundsBehavior: Flickable.StopAtBounds
        Layout.fillHeight: true
        Layout.fillWidth: true
    //    Layout.alignment: Qt.AlignTop
        visibleArea.onYPositionChanged: {
           rl.commonContentTopY = contentY
        }

        model: xmodel

        cacheBuffer: 140
        cellWidth:20
        cellHeight: 20


        property int bytesPerRow : {
            return  Math.floor( gvHex.width / gvHex.cellWidth );
        }

        delegate: Rectangle {
            height: 20
            width: 20

           Text {

                font.family: "Courier"
                text:   hexdata
            }
        }


    }


    GridView {


        id: gvAscii

        boundsBehavior: Flickable.StopAtBounds
        Layout.fillHeight: true
        Layout.fillWidth: true
     //   Layout.alignment: Qt.AlignTop


        visibleArea.onYPositionChanged: {
         //   console.log( visibleArea.yPosition + " " + contentY);
            rl.commonContentTopY = contentY
        }

        model: xmodel

        cacheBuffer: 140
        cellWidth:20
        cellHeight: 20


        property int bytesPerRow : {
            return  Math.floor( gvHex.width / gvHex.cellWidth );
        }


        delegate: Rectangle {
            height: 20
            width: 20

           Text {

                font.family: "Courier"
                text:   asciidata
            }
        }


    }


}
