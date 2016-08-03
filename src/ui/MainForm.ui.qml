import QtQuick 2.5
import QtQuick.Layouts 1.2

Item {
    id: item1
    width: 640
    height: 480
    property alias chip8ScreenImage: chip8ScreenImage

    /*property alias button1: button1
    property alias button2: button2*/

    /**/

    RowLayout {
        id: rowLayout1
        y: 110
        height: 100
        anchors.verticalCenter: parent.verticalCenter
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.left: parent.left

        Image{
            id: chip8ScreenImage;
            antialiasing: false
            enabled: false
            smooth: false
            Layout.fillHeight: true
            Layout.fillWidth: true
            cache: false;
            source: "image://chip8Screen/screen"

            /*function reload() {
            var oldSource = source;
            source = "";
            source = oldSource;
            chip8Screen.requestPaint();
        }*/
        }
    }

    /*Connections{
        target: chip8;
        imageChanged:
    }*/

    /*Canvas{
        id: chip8Screen;
        anchors.fill: parent;

        onPaint: {
            var ctx = getContext("2d")
            ctx.drawImage(chip8ScreenImage, 0, 0, chip8Screen.width, chip8Screen.height)
            //console.log("dessin\n")
            //contextImageData.data = chip8Screen.getData();
            /*context2D.beginPath()
            context2D.lineWidth = 2
            context2D.moveTo(10, 10)  // permet de se déplacer sans tracer de points
            context2D.lineTo(300, 10)    // permet de tracer une ligne
            context2D.moveTo(10, 10)
            context2D.lineTo(10, 300)
            context2D.strokeStyle = Qt.rgba(0,0,0);
            context2D.stroke()
            context2D.closePath()*/
    /*}
    }*/
    /*RowLayout {
        anchors.centerIn: parent

        Button {
            id: button1
            text: qsTr("Press Me 1")
        }

        Button {
            id: button2
            text: qsTr("Press Me 2")
        }

    }*/
}
