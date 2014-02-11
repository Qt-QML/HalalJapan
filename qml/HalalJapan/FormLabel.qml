import QtQuick 2.0


Item {
    property alias formTitle: titleElement.text
    property alias formText: textElement.text
    property alias textColor: textElement.color

    height: titleElement.height + textElement.height

    Text {
        id: titleElement
        color: _TEXT_COLOR
        font.pixelSize: _STANDARD_FONT_SIZE
    }

    Text {
        id: textElement

        anchors {
            top: titleElement.bottom
            leftMargin: 35
            right: parent.right
            left: parent.left
        }
        color: _TEXT_COLOR
        font.pixelSize: _STANDARD_FONT_SIZE
        wrapMode: Text.WordWrap
    }
}
