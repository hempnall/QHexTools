import QtQuick 2.0
import QtQuick.Layouts 1.1
import HexTools 1.0
import QtQml.Models 2.2

RowLayout {

    id: rl

    anchors.fill: parent

    property int commonContentTopY : 0
    property HexData xmodel
    property string selectedColour : "cyan"
    property string unselectedColour : "white"


//    function onModelDataChanged() {
//        gvHex.model = model.model
//        gvAscii.model = model.model
//    }


    function selectRange(start,len) {
        //gvHex.;
    }

    property int idx_start : -1
    property int idx_end : -1


    function selection(start,end) {
        if (start > end) {
            idx_start = end;
            idx_end = start;
        } else {
            idx_start = start;
            idx_end = end;
        }
        gvHex.positionViewAtIndex(start,GridView.Visible);
    }

    function endSelect() {
        idx_start = -1;
        idx_end = -1;
    }


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
               verticalAlignment: Text.AlignVCenter
                font.family: "Courier"
                text:  "0x" + ("000000" + (+(index * gvHex.bytesPerRow)).toString(16)).substr(-6) //   getOffset(index)// rl.model.model.getHexNumber( index * gvHex.bytesPerRow , 6 , true );
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


        focus: true

        delegate: Rectangle {
            height: 20
            width: 20

            property bool isSelected : (index >= rl.idx_start && index <= rl.idx_end)
            color:  isSelected ? selectedColour : unselectedColour


           Text {
                verticalAlignment: Text.AlignVCenter
                font.family: "Courier"
                text:   hexdata ? hexdata : ""
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

        model: gvHex.model

        cacheBuffer: 140
        cellWidth:20
        cellHeight: 20


        property int bytesPerRow : {
            return  Math.floor( gvHex.width / gvHex.cellWidth );
        }


        delegate: Rectangle {
            height: 20
            width: 20


            property bool isSelected : (index >= rl.idx_start && index <= rl.idx_end)
            color:  isSelected ? selectedColour : unselectedColour

           Text {
                verticalAlignment: Text.AlignVCenter
                font.family: "Courier"
                text:   asciidata ? asciidata : ""
            }
        }


    }


}
