import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material
import Qt5Compat.GraphicalEffects

// C++ imports
import Minesweeper

ApplicationWindow {
    id: mainWindow
    visible: true

    minimumWidth: 550
    minimumHeight: 500
    title: qsTr("Mines Seeker")

    Rectangle {
        id: backgroundRectangle
        anchors.fill: parent
        color: "#DDDDDD"

        UIArcade {
            id: uiArcade
            anchors.fill: parent
        }
    }

    FastBlur {
        id: blurEffectPause
        visible: radius > 0
        anchors.fill: backgroundRectangle
        source: backgroundRectangle

        Behavior on radius { NumberAnimation {} }
    }

    FastBlur {
        id: blurEffectMenu
        visible: radius > 0
        anchors.fill: backgroundRectangle
        source: backgroundRectangle
        radius: uiArcade.menu.position * 128

        Behavior on radius { NumberAnimation {} }
    }
}
