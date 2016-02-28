import QtQuick 2.5
import QtQuick.Controls 1.4
import Forensics 1.0


ApplicationWindow {
    visible: true
    width: 700
    height: 480
    title: qsTr("Hello World")

    HexModel2 {
        id: mod
        filename: "/Users/James/dev/projects/QHexTools/photo.jpg"


    }


    Flickable {
        id: x
        anchors.fill: parent
        clip: true

        Hexy    {




        }
    }





//    Flickable {



//        id:f
//        anchors.fill: parent
//      //  viewport: Button { text:"123"}
//        clip: true
//        interactive: true


//        contentHeight: hv.contentHeight
//        contentWidth: hv.contentHeight


//            HexView2 {
//            id: hv
//                height: 14900
//                width: 1000

//        }

//        visibleArea.onYPositionChanged: {
//         refresh();
//        }



//        function refresh() {
//            var y = f.visibleArea.yPosition * hv.contentHeight;
//            var dy = f.visibleArea.heightRatio * hv.contentHeight;
//            console.log("y=" + y + " dy=" + dy);
//            hv.viewport = Qt.rect(0,y,hv.contentWidth,dy);
//            hv.update();
//        }

//        Component.onCompleted: {

//        }



//    }


}

