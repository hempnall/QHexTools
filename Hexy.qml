import QtQuick 2.0

Canvas {
    id: canvas

    width: 1000
    height : 50000
    antialiasing: true
    renderStrategy: Canvas.Immediate

    onPaint: {
        console.log("please paint: "+ region)
        var ctx = canvas.getContext('2d');



        ctx.strokeStyle = Qt.rgba(1, 0, 0, 1);
        ctx.lineWidth = 1;
        ctx.beginPath();
        ctx.moveTo(20, 0);//start point
        ctx.bezierCurveTo(-10, 90, 210, 90, 180, 0);
        ctx.stroke();

        ctx.text(10,10,"Hello");

    }

}

