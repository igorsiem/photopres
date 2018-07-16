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

    // After the main window loads, ask the user for a starting directory.
    Component.onCompleted: {
        folderChooser.folder = mainWindow.currentFolderUrl
        folderChooser.open()
    }

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
            horizontalAlignment: Image.AlignLeft

            fillMode: Image.PreserveAspectFit
            autoTransform: true

            // When an image has finished loaded, update the layout, so that
            // the caption text is where we want it.
            onStatusChanged: {

                if (image.status === Image.Ready) {

                    // Use the dimensions of the image source to determine
                    // whether the image is landscape or portrait.
                    if (image.sourceSize.width > image.sourceSize.height) {
                        textEdt.setBottom()

                        Layout.maximumWidth = -1
                        Layout.maximumHeight =
                                parent.height - textEdt.height - 10

                        console.log("wide image (landscape)")
                    }
                    else {
                        textEdt.setSide()

                        Layout.maximumWidth = parent.width - textEdt.width
                        Layout.maximumHeight = parent.height

                        console.log("tall image (portrait)")
                    }

                }   // end onStatusChanged handler

            }   // end onStatusChanged event handler

        }   // end image

        // The caption that can be edited
        TextEdit {

            id: textEdt
            text: "[text]"
            readOnly: true

            // Layout.row: 0
            // Layout.column: 1

            // Put the caption text at the bottom of the grid
            function setBottom() {
                Layout.row = 1
                Layout.column = 0
                Layout.minimumWidth = -1

                console.log("set bottom")
            }

            // Put the caption text on the side of the grid
            function setSide() {
                Layout.row = 0
                Layout.column = 1
                Layout.minimumWidth = parent.width / 3

                console.log("set side")
            }

        }   // end rightText

    }   // end mainGrid

    // The tool bar on the footer of the Main Window
    footer: ToolBar {

        id: footerToolBar
        RowLayout {

            // Choose a folder of images
            ToolButton {
                id: openBtn
                text: "Open"           
                onClicked: {
                    folderChooser.folder = mainWindow.currentFolderUrl
                    folderChooser.open()
                }
            }   // end openBtn

            // Edit the caption for the current image
            ToolButton {
                id: editBtn
                text: "Edit Caption"
                checkable: true
                onClicked: {
                    mainWindow.signalError(
                                "Edit Caption",
                                "Capability not implemented yet");
                }   // end onClicked method
            }   // end editBtn

        }   // end RowLayout

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

        // When the user chooses a folder, set it in the core application
        // object, and move to the first image in the sequence
        onAccepted: {
            mainWindow.currentFolderUrl = folderChooser.folder
            mainWindow.currentImageIndex = 0
        }

    }   // end fileDialog

}   // end ApplicationWindow
