import QtQuick 2.8
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.8

ApplicationWindow {
    title: "Personnel Manager"
    width: 1024
    height: 600
    visible: true
    //flags: Qt.FramelessWindowHint | Qt.WA_TranslucentBackground

    property int activeIndex: 0

    function openDialog(index) {
        addbtn.visible = true
        savebtn.visible = true
        typecbox.visible = false
        popuptmr.running = false
        editdialog.visible = true
        activeIndex = index // TODO
    }

    function cancelDialog() {
        if(!typecbox.popup.visible) {
            addbtn.visible = true
            savebtn.visible = true
            typecbox.visible = false
            popuptmr.running = false
            typecbox.currentIndex = 0
        }
    }

    ListView {
        id: root
        anchors.fill: parent

        header: Row {
            spacing: 1
            Repeater {
                model: ["Employee", "Name", "SSN", "Salary"]
                Label {
                    text: modelData
                    font.pixelSize: 22
                    padding: 10
                    background: Rectangle { color: "#6699CC" }
                    width: (root.width - 2*32) / 4 - 2
                }
            }
            Repeater {
                model: ["-", "x"]
                Label {
                    text: modelData
                    font.pixelSize: 22
                    padding: 10
                    background: Rectangle { color: "#6699CC" }
                    width: 32
                }
            }
        }

        model: listModel
        delegate: Column {
            Row {
                spacing: 1
                ItemDelegate {
                    text: model.type + " Employee"
                    width: (root.width - 2*32) / 4 - 2
                }
                ItemDelegate {
                    text: model.name
                    width: (root.width - 2*32) / 4 - 2
                    highlighted: true
                }
                ItemDelegate {
                    text: model.ssn
                    width: (root.width - 2*32) / 4 - 2
                }
                ItemDelegate {
                    text: model.salary
                    width: (root.width - 2*32) / 4 - 2
                }
                Button {
                    width: 32
                    height: 48
                    background: Rectangle { color: "transparent" }
                    Image {
                        id: im3
                        states: [ "mouseIn", "mouseOut" ]
                        state: "mouseOut"

                        transitions: [
                            Transition {
                                from: "*"
                                to: "mouseIn"
                                NumberAnimation {
                                    target: im3
                                    properties: "scale"
                                    from: 0.85
                                    to: 1
                                    duration: 400
                                    easing.type: Easing.OutBounce
                                }
                            }
                        ]
                        MouseArea{
                            hoverEnabled: true
                            anchors.fill: parent

                            onContainsMouseChanged: {
                                im3.state = containsMouse ? "mouseIn" : "mouseOut"
                            }
                            onClicked: {
                                console.log("edit " + index);
                                openDialog(index);
                            }
                        }

                        anchors.centerIn: parent
                        source: "qrc:///edit.png"
                        width: 32
                        height: 32
                    }
                }
                Button {
                    width: 32
                    height: 48
                    background: Rectangle { color: "transparent" }
                    Image {
                        id: im4
                        states: [ "mouseIn", "mouseOut" ]
                        state: "mouseOut"

                        transitions: [
                            Transition {
                                from: "*"
                                to: "mouseIn"
                                NumberAnimation {
                                    target: im4
                                    properties: "scale"
                                    from: 0.85
                                    to: 1
                                    duration: 400
                                    easing.type: Easing.OutBounce
                                }
                            }
                        ]
                        MouseArea{
                            hoverEnabled: true
                            anchors.fill: parent

                            onContainsMouseChanged: {
                                im4.state = containsMouse ? "mouseIn" : "mouseOut"
                            }
                            onClicked: listModel.removeperson(index)
                        }

                        anchors.centerIn: parent
                        source: "qrc:///del.png"
                        width: 32
                        height: 32
                    }
                }
            }

            Rectangle {
                color: index % 2 == 0 ? "#6699CC" : "#AA1020"
                width: parent.width
                height: 1
            }
        }
    }

    Row {
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.leftMargin: 15
        anchors.bottomMargin: 15
        spacing: 15

        Timer {
            id: popuptmr
            interval: 500
            running: false
            repeat: true
            onTriggered: {
                cancelDialog();
            }
        }

        ComboBox {
            id: typecbox
            implicitWidth: 130
            model: listModel.personTypes
            visible: false
            currentIndex: 0
            onCurrentTextChanged: {
                if(visible) {
                    console.log("Added " + currentText)
                    listModel.addperson(currentText);
                    openDialog(listModel.size() - 1);
                }
            }
        }

        Button {
            id: addbtn
            width: 64
            height: 64
            background: Rectangle { color: "transparent" }
            Image {
                id: im2
                states: [ "mouseIn", "mouseOut" ]
                state: "mouseOut"

                transitions: [
                    Transition {
                        from: "*"
                        to: "mouseIn"
                        NumberAnimation {
                            target: im2
                            properties: "scale"
                            from: 0.85
                            to: 1
                            duration: 400
                            easing.type: Easing.OutBounce
                        }
                    }
                ]
                MouseArea{
                    hoverEnabled: true
                    anchors.fill: parent

                    onContainsMouseChanged: {
                        im2.state = containsMouse ? "mouseIn" : "mouseOut"
                    }
                    onClicked: {
                        addbtn.visible = false
                        savebtn.visible = false
                        typecbox.visible = true
                        typecbox.popup.visible = true
                        popuptmr.running = true
                    }
                }

                anchors.centerIn: parent
                anchors.fill: parent
                source: "qrc:///add.png"
            }
        }

        Button {
            id: savebtn
            width: 64
            height: 64
            background: Rectangle { color: "transparent" }
            Image {
                id: im1
                states: [ "mouseIn", "mouseOut" ]
                state: "mouseOut"

                transitions: [
                    Transition {
                        from: "*"
                        to: "mouseIn"
                        NumberAnimation {
                            target: im1
                            properties: "scale"
                            from: 0.85
                            to: 1
                            duration: 400
                            easing.type: Easing.OutBounce
                        }
                    }
                ]
                MouseArea{
                    hoverEnabled: true
                    anchors.fill: parent

                    onContainsMouseChanged: {
                        im1.state = containsMouse ? "mouseIn" : "mouseOut"
                    }
                    onClicked: listModel.save();
                }

                anchors.centerIn: parent
                anchors.fill: parent
                source: "qrc:///save.png"
            }
        }
    }

    // Dialog
    Rectangle {
        id: editdialogshadow
        visible: false
        color: "#d2d2d2"
        opacity: 0.8
        anchors.fill: parent
    }
    Rectangle {
        id: editdialog
        visible: false
        anchors {
            top: parent.top
            topMargin: root.height / 10
            horizontalCenter: root.horizontalCenter
        }
        width: root.width / 2
        color: "white"
        onVisibleChanged: editdialogshadow.visible = visible
        Repeater {
            anchors.fill: parent
            clip: true
            model: listModel
            delegate: DDialog {
                width: parent.width
                value: activeIndex
                onHide: {
                    editdialog.visible = false
                    typecbox.currentIndex = 0
                }
            }
        }
    }
}
