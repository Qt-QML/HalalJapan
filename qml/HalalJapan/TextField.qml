import QtQuick 2.0

Rectangle {
    id: root

    property alias enabled: input.enabled
    property alias placeholderText: placeholderText.text
    property alias text : input.text
    property alias echoMode : input.echoMode
    property alias inputFocus: input.focus
    property alias validator: input.validator

//    signal textChanged

    height: 50
    color:  "white"
    border.width: 2
    border.color: input.activeFocus ? Settings.activeColor : "grey"
    radius: 5

    TextInput {
        id: input

        anchors { fill: parent; margins: 5 }
        font.pixelSize: _STANDARD_FONT_SIZE
        selectByMouse: true
        selectionColor: Settings.activeColor
        onTextChanged: root.textChanged()
    }

    Label {
        id: placeholderText

        anchors.fill: input
        
        color: "#4d4d4d"
        clip: true
        visible: (!input.activeFocus) && (input.text == "")
    }
}
