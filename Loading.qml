import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material
import QtQuick.Layouts

Item {
   width: 720
   height: 500

   LoadingSplash {
       id: loading
       x: (parent.width - width) / 2
       y: (parent.height - height) / 2
       parent: Overlay.overlay

       implicitWidth: 630
       implicitHeight: 380
   }
}
