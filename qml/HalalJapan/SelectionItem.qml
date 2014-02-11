import QtQuick 2.0
import "scripts/createobject.js" as ObjectCreator

Item {
    id: root

    property alias title: title.text
    property string initialValue
    property string currentValue
    property alias model: selectionDialog.model
    property alias isChild: selectionDialog.isChild
    property bool enabled: true

    signal valueChosen(string value)
    signal opened
    signal rejected
    signal accepted
    signal closed

    width: parent.width
    height: 80
    opacity: enabled ? 1 : 0.3

    function setInitialValue(value) {
        var found = false;
        var i = 0;
        while ((!found) && (i < model.count)) {
            if (model.get(i).value == value) {
                selectionDialog.selectedIndex = i;
                found = true;
            }
            i++;
        }
        currentValue = value;
    }

    Component.onCompleted: if (initialValue != "") setInitialValue(initialValue);

    ListHighlight {
        visible: mouseArea.pressed
    }

    Column {

        anchors { left: parent.left; leftMargin: 10; right: icon.left; rightMargin: 10; verticalCenter: parent.verticalCenter }

        Label {
            id: title

            font.bold: true
            
            
            verticalAlignment: Text.AlignVCenter
        }

        Label {
            id: subTitle

            width: parent.width
            color: "#4d4d4d"
            verticalAlignment: Text.AlignVCenter
            elide: Text.ElideRight
            text: selectionDialog.selectedIndex < 0 ? "" : model.get(selectionDialog.selectedIndex).name
        }
    }

    Image {
        id: icon

        anchors { right: parent.right; rightMargin: 20; verticalCenter: parent.verticalCenter }
        source: !theme.inverted ? "images/icon-m-common-combobox-arrow.png" : "images/icon-m-textinput-combobox-arrow.png"
    }

    MouseArea {
        id: mouseArea

        anchors.fill: parent
        enabled: root.enabled
        onClicked: selectionDialog.open()
    }

    SelectionDialog {
        id: selectionDialog

        titleText: title.text
        onValueChosen: {
            currentValue = value;
            root.valueChosen(value);
        }
        onOpened: root.opened()
        onAccepted: root.accepted()
        onRejected: root.rejected()
        onClosed: root.closed()
    }
}
