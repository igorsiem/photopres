import QtQuick 2.9
import QtQuick.Controls 2.1
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.3
import QtQuick.Window 2.2

import com.igorsiemienowicz.ppcore 1.0

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("PhotoPres")

    // Core Application Interface
    PpCore {
        id: core

        onMessageBox: {
            messageDialog.title = mbHeading
            messageDialog.text = mbText
            messageDialog.icon = iconCode
            messageDialog.open()
        }
    }   // end PpCore

    // Main Layout of the Application Window
    ColumnLayout {

        Text {
            text: "Version: " + core.version
        }

        Button {
            text: "Open"
            // onClicked: core.makeAnError()
            onClicked: {
                folderChooser.folder = core.currentFolder
                folderChooser.open()
            }
        }

    }   // end main ColumnLayout

    // Multi-purpose message dialog
    MessageDialog {
        id: messageDialog
    }

    FileDialog {
        id: folderChooser
        title: "Image folder"
        // folder: shortcuts.pictures
        selectMultiple: false
        selectExisting: true
        selectFolder: true
        onAccepted: {
            core.currentFolder = folderChooser.fileUrl
        }
    }

}   // end ApplicationWindow
