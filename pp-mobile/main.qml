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

    // Main Window implementation
    MainWindow {
        id: mainWindow

        onMessageBox: {
            messageDialog.title = mbHeading
            messageDialog.text = mbText
            messageDialog.icon = iconCode
            messageDialog.open()
        }

        onDisplayImage: {
            image.source = path
        }

    }   // end MainWindow

    // Main Layout of the Application Window
    ColumnLayout {

        Text {
            text: "Version: " + mainWindow.version
        }

        Button {
            text: "Open"
            onClicked: {
                // console.log(mainWindow.currentFolder)
                // folderChooser.folder = "file:" + mainWindow.currentFolder
                folderChooser.folder = mainWindow.currentFolderUrl
                folderChooser.open()
            }
        }

        Image {
            id: image
        }

    }   // end main ColumnLayout

    // Multi-purpose message dialog
    MessageDialog {
        id: messageDialog
    }

    FileDialog {
        id: folderChooser
        title: "Image folder"
        selectMultiple: false
        selectExisting: true
        selectFolder: true
        onAccepted: {
            // mainWindow.currentFolder = folderChooser.folder
            mainWindow.currentFolderUrl = folderChooser.folder
            mainWindow.currentImageIndex = 0

            // TODO remove demo code
            // MainWindow.loadAndDisplayImage(0);
        }
    }

}   // end ApplicationWindow
