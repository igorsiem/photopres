import QtQuick 2.9
import QtQuick.Window 2.2
import com.igorsiemienowicz.ppcore 1.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    PpCore {
        id: core
    }

    Text {
        text: "Version: " + core.version
    }
}
