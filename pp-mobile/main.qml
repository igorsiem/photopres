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

///    Component.onCompleted: {
///        mainWindow.currentImageIndex = 0;
///    }

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

    // Main layout of the application in a gird
    GridLayout {

        id: mainGrid
        anchors.top: parent.top
        anchors.bottom: footerToolBar.top
        anchors.left: parent.left
        anchors.right: parent.right

        // The central display image
        Image {

            id: image
            Layout.row: 0
            Layout.column: 0

            fillMode: Image.PreserveAspectFit
            autoTransform: true

            Layout.maximumWidth: parent.width - rightText.width
            Layout.maximumHeight: parent.height - rightText.height - 10

            // When an image has finished loaded, select which text to display
            // (side or bottom)
            onStatusChanged: {
                if (image.status === Image.Ready) {

                    // Use the dimensions of the image source to determine
                    // whether the image is landscape or portrait.
                    if (image.sourceSize.width > image.sourceSize.height) {
                        rightText.visible = false
                        bottomText.visible = true

                        console.log("wide image (landscape)")
                    }
                    else {
                        rightText.visible = true
                        bottomText.visible = false

                        console.log("tall image (portrait)")
                    }
                }
            }   // end onStatusChanged event handler

        }   // end image

        // Text the right (may or may not be visible)
        Text {
            id: rightText
            text: "[right text]"

            Layout.row: 0
            Layout.column: 1
            Layout.minimumWidth: parent.width / 3
        }   // end rightText

        // Text on the bottom (may or may not be visible)
        Text {
            id: bottomText
            text: "[bottom text]"

            Layout.row: 1
            Layout.column: 0
            Layout.alignment: Qt.AlignBottom
        }   // end bottomText

    }   // end mainGrid

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
