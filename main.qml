import QtQuick 2.5
import QtQuick.Controls 1.4


ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")



    Flickable {
        id:f
        anchors.fill: parent
        clip: true
       // interactive: true

        contentHeight: hv.contentHeight
        contentWidth:  hv.contentWidth

        HexView {
            id: hv
        }

        focus: true
        Keys.onDownPressed:  f.flick(0,-300);
        Keys.onUpPressed:   f.flick(0,300);

        visibleArea.onYPositionChanged: {
         refresh();
        }



        function refresh() {
            var y = f.visibleArea.yPosition * hv.contentHeight;
            var dy = f.visibleArea.heightRatio * hv.contentHeight;
            hv.viewport = Qt.rect(0,y,hv.contentWidth,dy);;
            hv.update();
        }

        Component.onCompleted: {
            refresh();
        }



    }

}

