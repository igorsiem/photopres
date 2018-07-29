import QtQuick 2.9
import QtQuick.Controls 2.3
import QtQuick.Dialogs 1.2
import Qt.labs.handlers 1.0
import QtQuick.Layouts 1.3
import QtQuick.Window 2.2

import com.igorsiemienowicz.mainwindow 1.0

ApplicationWindow {

    visible: true
    width: 640
    height: 480
    title: qsTr("PhotoPres")

    // --- Functionality ---

    // After the main window loads, start a timer for the launch sequence. We
    // can't actually *do* the launch sequence after the window has loaded,
    // because Qt is, in fact, still doing some setup stuff internally.
    //
    // Instead, we invoke a zero-time timer which does the launch sequence when
    // it  triggers. This probably works because the timer trigger is processed
    // the event loop, which may not be running properly when `onCompleted` is
    // called.
    Component.onCompleted: {
        launcher.start()
    }

    // Timer to run whatever things need to run at startup. In this iteration,
    // this is just to open the Folder Chooser, but may run to other things in
    // the future.
    Timer {
        id: launcher
        triggeredOnStart: true
        onTriggered: {
            // openAct.trigger()
            mainWindow.currentImageIndex = 0
            updateImagesListModel()

        }
    }

    // -- Actions --

    /**
     * @brief Update the list model for the images
     *
     * This method is called when the images List Model needs
     */
    function updateImagesListModel() {

        imagesListModel.clear()

        var idx
        for (idx = 0; idx < mainWindow.imagesCount; idx++)
        {
            imagesListModel.append({
                "fileName": mainWindow.imageFileName(idx),
                "fileUrl": mainWindow.imageFileNameUrl(idx) })
        }

        imagesListView.currentIndex = 0

    }   // end updateImagesListModel function

    // Action to Open / Set the active folder
    Action {
        id: openAct
        text: "Open"
        icon.source: "qrc:/folder"

        onTriggered: {
            folderChooser.folder = mainWindow.currentFolderUrl
            folderChooser.open()
        }
    }   // end openAction

    /**
     * @brief Finish editing, saving the updated caption and un-checking the
     * `editAct` action.
     */
    function closeEditing() {
        console.log("exiting edit mode")
        console.log("text is: " + textEdt.text)

        mainWindow.currentCaption = textEdt.text
        textEdt.readOnly = true
        textEdt.cursorVisible = false

        editAct.checked = false
    }

    // Action to  start or finish caption editing
    Action {
        id: editAct
        text: "Edit Caption"
        checkable: true
        icon.source: "qrc:/pencil"

        onTriggered: {
            if (editAct.checked) {
                console.log("entering edit mode")

                // Make edit box editable
                textEdt.readOnly = false
                if (textEdt.text === "") {
                    textEdt.text = "[placeholder]"
                }
                textEdt.cursorVisible = true
            }
            else closeEditing()
        }
    }

    // Action to move to the previous image in the folder
    Action {
        id: previousImageAct
        text: "Previous Image"
        icon.source: "qrc:/back-arrow"

        onTriggered: {
            if (editAct.checked) closeEditing()
            mainWindow.currentImageIndex =
                    mainWindow.currentImageIndex - 1

            imagesListView.currentIndex = mainWindow.currentImageIndex

        }
    }   // end previousImageAct

    // Action to move to the next image in the folder
    Action {
        id: nextImageAct
        text: "Next Image"
        icon.source: "qrc:/forward-arrow"

        onTriggered: {
            // If we are in editing mode, save the edits first.
            if (editAct.checked) closeEditing()

            mainWindow.currentImageIndex =
                    mainWindow.currentImageIndex + 1

            imagesListView.currentIndex = mainWindow.currentImageIndex

        }
    }   // end nextImageAct

    // Action to open the image drawer
    Action {
        id: openImagesDrawerAct
        text: "Images"

        onTriggered: {
            imagesDrawer.open()
        }
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
                previousImageAct.enabled = false
            else previousImageAct.enabled = true

            if (mainWindow.currentImageIndex >= mainWindow.imagesCount-1)
                nextImageAct.enabled = false
            else nextImageAct.enabled = true
        }

    }   // end mainWindow

    // --- User Interface ---

    // -- Main UI Elements --

    header: ToolBar {
        id: headerToolBar

        ToolButton {
            id: openImagesDrawerBtn
            action: openImagesDrawerAct
        }
    }

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

            // Handle taps on the left side or right side of the image to go to
            // the previous or next image
            TapHandler {
                onTapped: {
                    // console.log("tapped " + point.position.x)
                    if (point.position.x < image.width / 2) {
                        console.log("left-side tap - previous image")
                        previousImageAct.trigger()
                    }
                    else {
                        console.log("right-side tap - next image")
                        nextImageAct.trigger()
                    }
                }
            }   // end TapHandler

        }   // end image

        // The caption that can be edited
        TextEdit {

            id: textEdt
            text: "[text]"
            readOnly: true
            color: "blue"

            Layout.row: 0
            Layout.column: 1
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

    // Side-drawer for navigating images
    Drawer {
        id: imagesDrawer
        width: 0.66 * parent.width
        height: parent.height


        // List view of images in the current folder
        ListView {

            id: imagesListView
            width: parent.width
            height: parent.height

            // The model supplying the data for the list view
            model: ListModel {
                id: imagesListModel

                ListElement {
                    fileName: "No files"
                    fileUrl: ""
                }
            }

            // Display item delegate - this is the structure that represents
            // an item in the list - it is recreated for each item in
            // `imagesListModel`.
            delegate: Component {

                // An item to hold all the visual components
                Item {

                    width: parent.width
                    height: 100

                    // A row to space out the image and the file name text
                    Row {

                        spacing: 10

                        // The image thumbnail
                        Image {
                            source: fileUrl
                            width: 100
                            height: 100
                            fillMode: Image.PreserveAspectFit
                        }

                        // The filename text
                        Text {
                            text: fileName
                        }

                    }   // end Row

                    // Mouse area - picks up clicks on the item for selection
                    MouseArea {

                        anchors.fill: parent
                        onClicked: {
                            mainWindow.currentImageIndex = index
                            imagesListView.currentIndex = index
                        }

                    }   // end Mouse Area

                }   // end Item

            }   // end item delegate component

            // A rectangle to hightlight the selected item
            highlight: Rectangle {

                width: parent.width
                height: 100
                color: "lightsteelblue"

            }   // end highlight rectangle

        }   // end imagesListView

    }   // end imageNavigationDrawer

    // The tool bar on the footer of the Main Window
    footer: ToolBar {

        id: footerToolBar
        RowLayout {

            // Choose a folder of images
            ToolButton {
                id: openBtn
                action: openAct
            }   // end openBtn

            // Edit the caption for the current image
            ToolButton {
                id: editBtn
                action: editAct
            }   // end editBtn

            // The "previous image" button
            ToolButton {
                id: previousImageBtn
                action: previousImageAct
            }   // end previousImageBtn

            // The "next image" buton
            ToolButton {
                id: nextImageBtn
                action: nextImageAct
            }   // end previousImageBtn

        }   // end RowLayout

    }   // end footerToolbar

    // -- Dialogs --

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

            updateImagesListModel()
        }

    }   // end fileDialog

}   // end ApplicationWindow
