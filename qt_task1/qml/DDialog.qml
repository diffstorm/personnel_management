import QtQuick 2.8
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.8

Frame {
    id: root

    property int value: 0

    visible: index === value

    background: Rectangle {
         color: "white"
         border.color: "black"
         radius: 2
     }

    signal hide(int _index);

    function getCurrentIndex(list, element) {
        if (list && element) {
            for (var i = 0; i < list.length; i++) {
                if (list[i] === element) {
                    return i
                }
            }
        }
        return 0
    }

    GridLayout {
        id: gridLayout
        anchors.fill: parent
        columns: 1

        Text {
            text: model.type + " Employee";
            font.pixelSize: 22
            font.bold: true
            Layout.fillWidth: true
        }

        Button {
            Layout.alignment: Qt.AlignRight
            Layout.rightMargin: 5
            background: Rectangle { color: "transparent" }
            Image {
                anchors.centerIn: parent
                source: "qrc:///ok.png"
                width: 32
                height: 32
            }
            onClicked: root.hide(index);
        }

        DataEntry {
            labelText: "Full Name"
            bold: true
            placeholderText: "Name Surname"
            text: model.name
            onDone: model.name = text
        }

        DataEntry {
            labelText: "Social Security Number"
            inputMask: "999999999"
            text: model.ssn
            onDone: model.ssn = text
        }

        DataEntry {
            visible: model.type === "Hourly"
            labelText: "Hourly Compensation"
            placeholderText: "22"
            text: visible ? model.hourlyCompensation : -1
            onDone: model.hourlyCompensation = text
        }

        DataEntry {
            visible: model.type === "Hourly"
            labelText: "Done Hours"
            placeholderText: "18"
            inputMask: "999"
            text: visible ? model.doneHours.toFixed(3) : -1
            onDone: model.doneHours = text;
        }

        DataEntry {
            visible: (model.type === "Monthly" || model.type === "Sales")
            labelText: "Monthly Compensation"
            placeholderText: "4000"
            inputMask: "9999"
            text: visible ? model.monthlyCompensation : -1
            onDone: model.monthlyCompensation = text;
        }

        DataEntry {
            visible: model.type === "Sales"
            labelText: "Bonus Percent %"
            placeholderText: "10"
            inputMask: "99"
            text: visible ? model.bonusPercent.toFixed(2) : -1
            onDone: model.bonusPercent = text;
        }

        DataEntry {
            visible: model.type === "Sales"
            labelText: "Realized Outcome"
            placeholderText: "150"
            text: visible ? model.realizedOutcome : -1
            onDone: model.realizedOutcome = text;
        }

        DataEntry {
            visible: model.type === "Sales"
            labelText: "Outcome Claim"
            placeholderText: "150"
            text: visible ? model.outcomeClaim : -1
            onDone: model.outcomeClaim = text;
        }

        DataEntry {
            Layout.columnSpan: gridLayout.columns
            labelText: "Salary"
            bold: true
            placeholderText: "3000"
            readOnly: true
            text: model.salary
        }
    }
}
