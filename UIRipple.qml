import QtQuick
import QtQuick.Controls.Material.impl

Item {
    property alias clipRadius:      ripple.clipRadius
    property alias pressed:         ripple.pressed
    property alias active:          ripple.active
    property alias color:           ripple.color

    Ripple { // set clip to true to keep the ripple inside his parent:
        id: ripple
        width: parent.width
        height: parent.height
        pressed: true // true activates the ripple effect, false deactivates it
        active: false
        color: "#AA000000"
    }
}
