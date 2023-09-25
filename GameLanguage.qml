import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material

Menu {
    id: menuLanguage

    property color iconColor: "transparent"
    property color materialTextColor: Material.foreground

    MenuItem {
        text: "English"
        icon.source: "images/Languages/en.svg"
        icon.color: menuLanguage.iconColor
        Material.foreground: settings.language === "en" ? Material.accent : menuLanguage.materialTextColor
        onClicked: {
            settings.language = "en"
        }
    }

    MenuItem {
        text: "Español"
        icon.source: "images/Languages/ko.svg"
        icon.color: menuLanguage.iconColor
        Material.foreground: settings.language === "ko" ? Material.accent : menuLanguage.materialTextColor
        onClicked: {
            settings.language = "ko"
        }
    }
}
