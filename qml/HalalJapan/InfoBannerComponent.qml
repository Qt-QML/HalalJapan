import QtQuick 2.0

Item {
    id: banner

    property alias message : messageText.text

    height: 70

    Rectangle {
        id: background

        anchors.fill: banner
        color: Settings.activeColor
        smooth: true
        opacity: 0.8
    }

    Label {
        id: messageText


        anchors.fill: banner
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        wrapMode: Text.WordWrap

        color: "white"
    }

    states: State {
        name: "portrait"
        PropertyChanges { target: banner; height: 105 }
    }

    MouseArea {
        anchors.fill: parent
        onClicked: messages.state = ""
    }
}
