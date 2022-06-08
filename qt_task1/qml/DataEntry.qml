import QtQuick 2.8
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.8

ColumnLayout {
    id: root
    property alias labelText: label.text
    property bool bold: false
    property alias placeholderText: textField.placeholderText
    property alias text: textField.text
    property alias inputMask: textField.inputMask
    property alias readOnly: textField.readOnly
    signal done(string text)

    Layout.fillWidth: true

    Label {
        id: label
        font.pixelSize: 10
        font.bold: root.bold
        Layout.alignment: Qt.AlignLeft | Qt.AlignBottom
    }

    TextField {
        id: textField
        Layout.fillWidth: true
        font.bold: root.bold
        onEditingFinished: root.done(text)
    }
}
