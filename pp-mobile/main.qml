import QtQuick 2.9
import QtQuick.Controls 2.1
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.3
import QtQuick.Window 2.2

import com.igorsiemienowicz.mainwindow 1.0

ApplicationWindow {

    visible: true
    width: 640
    height: 480
    title: qsTr("PhotoPres")

    // The Main Window implementation object
    MainWindow {
        id: mainWindow

        // Implement the `messageBox` signal by displaing the Message Dialog
        onMessageBox: {
            messageDialog.title = mbHeading
            messageDialog.text = mbText
            messageDialog.icon = iconCode
            messageDialog.open()
        }

        // Implement the `displayImage` signal
        onDisplayImage: {
            image.source = path
        }

    }   // end mainWindow

    // The main display image
    Image {
        id: image
        width: parent.width
        anchors.top: parent.top
        anchors.bottom: footerToolBar.top
        fillMode: Image.PreserveAspectFit
        autoTransform: true
    }

    // The tool bar on the footer of the Main Window
    footer: ToolBar {

        id: footerToolBar

        // Choose a folder of images
        ToolButton {
            id: openBtn
            text: "Open"
            onClicked: {
                folderChooser.folder = mainWindow.currentFolderUrl
                folderChooser.open()
            }
        }
    }   // end footerToolbar

    // Multi-purpose message dialog
    MessageDialog {
        id: messageDialog
    }

    // The Folder Chooser dialog
    FileDialog {
        id: folderChooser
        title: "Image folder"
        selectMultiple: false
        selectExisting: true
        selectFolder: true
        onAccepted: {
            mainWindow.currentFolderUrl = folderChooser.folder
            mainWindow.currentImageIndex = 0
        }
    }   // end fileDialog

}   // end ApplicationWindow
