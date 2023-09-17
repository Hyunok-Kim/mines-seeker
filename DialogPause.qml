import QtQuick
import QtQuick.Controls

Dialog {
    id: pauseDialog

    anchors.centerIn: parent
    implicitWidth: 250

    modal: true

    title: qsTr("PAUSED")

    Label {
        text: qsTr("Click anywhere to resume")

        MouseArea {
            anchors.fill: parent
            anchors.topMargin: -pauseDialog.header.height
            onClicked: {
                pauseDialog.close()
            }
        }
    }

    onClosed: {
        if (arcade.paused) {
            arcade.startTiming()
        }
    }
} // pauseDialog
