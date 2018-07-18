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

            if (mainWindow.currentImageIndex <= 0)
                previousImageBtn.enabled = false
            else previousImageBtn.enabled = true

            if (mainWindow.currentImageIndex >= mainWindow.imagesCount-1)
                nextImageBtn.enabled = false
            else nextImageBtn.enabled = true
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

                    textEdt.text = mainWindow.currentCaption
                    console.log("text is: " + mainWindow.currentCaption)

                }   // end onStatusChanged handler

            }   // end onStatusChanged event handler

        }   // end image

        // The caption that can be edited
        TextEdit {

            id: textEdt
            text: "[text]"
            readOnly: true
            color: "blue"

            // Layout.row: 0
            // Layout.column: 1
            // Layout.minimumHeight: 50

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

                    if (editBtn.checked) {
                        console.log("entering edit mode")

                        // Make edit box editable
                        textEdt.readOnly = false
                        if (textEdt.text === "") {
                            textEdt.text = "[placeholder]"
                        }
                        textEdt.cursorVisible = true
                    }
                    else {
                        console.log("exiting edit mode")
                        console.log("text is: " + textEdt.text)

                        mainWindow.currentCaption = textEdt.text
                        textEdt.readOnly = true
                        textEdt.cursorVisible = false
                    }

                }   // end onClicked method

            }   // end editBtn

            // The "previous image" button
            ToolButton {

                id: previousImageBtn
                text: "Previous Image"

                // Move to the previous image
                onClicked: {

                    // If we are in editing mode, save the edits first.
                    if (editBtn.checked) {
                        console.log("exiting edit mode")
                        console.log("text is: " + textEdt.text)

                        mainWindow.currentCaption = textEdt.text
                        textEdt.readOnly = true
                        textEdt.cursorVisible = false

                        editBtn.checked = false
                    }

                    mainWindow.currentImageIndex =
                            mainWindow.currentImageIndex - 1

                }   // end onClicked event handler

            }   // end previousImageBtn

            // The "next image" buton
            ToolButton {

                id: nextImageBtn
                text: "Next Image"

                // Move to the next image
                onClicked: {

                    // If we are in editing mode, save the edits first.
                    if (editBtn.checked) {
                        console.log("exiting edit mode")
                        console.log("text is: " + textEdt.text)

                        mainWindow.currentCaption = textEdt.text
                        textEdt.readOnly = true
                        textEdt.cursorVisible = false

                        editBtn.checked = false
                    }

                    mainWindow.currentImageIndex =
                            mainWindow.currentImageIndex + 1

                }   // end onClicked event handler

            }   // end previousImageBtn

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
