import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3
import com.igorsiemienowicz.ppcore 1.0

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("PhotoPres")

    PpCore {
        id: core

        onMessageBox: {
            messageBoxHeading.text = mbHeading
            messageBoxText.text = mbText
            messageBox.open()
        }
    }

    ColumnLayout {

        Text {
            text: "Version: " + core.version
        }

        Button {
            text: "Open"
            onClicked: core.makeAnError()
        }

    }

    Popup {

        id: messageBox
        x: 100
        y: 100
        width: 200
        height: 300
        modal: true
        focus: true
        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside

        ColumnLayout {

            Text {
                id: messageBoxHeading
            }

            Text {
                id: messageBoxText
            }

        }

    }
}
