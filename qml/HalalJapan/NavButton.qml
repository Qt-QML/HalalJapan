import QtQuick 2.0

Item {
    id: root

    property string iconSource
    property alias label: label.text

    signal clicked
    signal pressed

    Rectangle {
        id: iconRectangle

        color: _BACKGROUND_COLOR

        height: parent.height*3/5
        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
            margins: 10
        }
        Image {
            id: icon

            anchors.centerIn: parent
            source: iconSource
            fillMode: Image.PreserveAspectFit
            height: parent.height - 10
//            scale: 0.9
            smooth: true
//            width: parent.width
//            Component.onCompleted: console.log(0.9 * wid)
        }
    }

    Label {
        id: label

        anchors { top: iconRectangle.bottom; horizontalCenter: parent.horizontalCenter; bottom: parent.bottom; margins: 10 }
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
//        color: mouseArea.pressed ? Settings.activeColor : _TEXT_COLOR
        width: parent.width
//        font.pixelSize: _STANDARD_FONT_SIZE
        height: parent.height*2/5

        wrapMode: Text.WordWrap
    }

    Rectangle {
        anchors {
//            top: parent.top
//            bottom: parent.bottom
//            horizontalCenter: parent.horizontalCenter
            fill: parent

            margins: 10
        }
        width: parent.height
        color: Settings.activeColor
        opacity: 0.5
        radius: 10
        visible: mouseArea.pressed
    }

    MouseArea {
        id: mouseArea

        anchors.fill: parent
        onClicked: parent.clicked()
        onPressAndHold: parent.pressed()
    }
}
