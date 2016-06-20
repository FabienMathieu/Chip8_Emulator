import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.2

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    menuBar: MenuBar {
        Menu {
            title: qsTr("File")
            MenuItem {
                text: qsTr("&Open")
                onTriggered: fileDialog.open();
            }
            MenuItem {
                text: qsTr("&Run")
                onTriggered: {
                    paintingTimer.start();//  <--- Celui là
                    chip8.startEmulation();
                }
            }
            MenuItem {
                text: qsTr("Exit")
                onTriggered: {
                    chip8.stopEmulation();
                    paintingTimer.stop();
                    Qt.quit();
                }
            }
        }
    }

    onClosing: {
        chip8.stopEmulation();
        paintingTimer.stop();
        close.accepted = true;
    }

    MainForm {
        id: mainForm;
        anchors.fill: parent

        function reload() {
            var oldSource = chip8ScreenImage.source;
            chip8ScreenImage.source = "";
            chip8ScreenImage.source = oldSource;
        }
    }

    MessageDialog {
        id: messageDialog
        title: qsTr("May I have your attention, please?")

        function show(caption) {
            messageDialog.text = caption;
            messageDialog.open();
        }
    }

    FileDialog {
        id: fileDialog
        title: "Please choose a Chip8 file"
        nameFilters: ["Chip Rom (*.ch8)"]
        onAccepted: {
            chip8.loadRom(fileDialog.fileUrl);
        }
        onRejected: {
            console.log("Canceled")
        }
    }

    Timer {
            id: paintingTimer
            interval: 16;
            repeat: true;
            running: false;
            triggeredOnStart: true;
            //onTriggered: chip8Screen.requestPaint()
            onTriggered: mainForm.reload();

        }
}
