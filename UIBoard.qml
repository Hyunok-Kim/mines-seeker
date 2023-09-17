import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material
import QtQuick.Layouts

// C++ imports
import Minesweeper

// Here are dependencies with C++ code: max rows and columns. update each as appropiate

Rectangle {
    id: root

    property Board board;

    property int mode:                  board.mode
    property int rows:                  board.uiRows
    property int columns:               board.uiCols
    property int mines:                 board.mines
    property int minesDiscovered:       board.minesDiscovered
    property real progress:             board.progress
    property bool uiReady:              false

    property real widthHeightRootReason: width/height
    property real rowColumnReason: columns/rows

    Material.primary: "#DDDDDD"

    color: "transparent"

    Grid {
        id: grid
        anchors.centerIn: parent
        horizontalItemAlignment: Grid.AlignHCenter
        verticalItemAlignment: Grid.AlignVCenter
        rows: root.rows
        columns: root.columns
        spacing: -1

        Repeater {
            model: 480
            onItemAdded: (index) => {
                if ((index + 1) % 10 === 0) {
                    startupManager.progress = (index + 1)/480
                }
                if (index === 479) {
                    uiReady = true
                }
            }

            delegate: UICell {
                size: !uiReady ? 0 : root.widthHeightRootReason < root.rowColumnReason ? (root.width)/columns : (root.height)/rows
                visible: uiReady && row >= 0 && column >= 0
                cell: board.itemAt(index)
                gameRunning: board.running
            }
        }
    }
}
