import QtQuick 2.0

Item {
    id: root

    property alias menuItems: menuLayout.children

    signal opened
    signal closed

    function open() {
        pageStack.dim();
        root.state = "open";
        root.opened();
    }

    function close() {
        pageStack.undim();
        root.state = "";
        root.closed();
    }

    parent: appWindow
    height: menuLayout.height + 60
    anchors { bottom: parent.top; bottomMargin: 20; left: parent.left; leftMargin: 40; right: parent.right; rightMargin: 40 }

    Rectangle {
        anchors.fill: parent
        color: _BACKGROUND_COLOR
        radius: 10
//        opacity: 0.8
        border.width: 2
        border.color: Settings.activeColor
    }

    Flow {
        id: menuLayout

        anchors { left: parent.left; leftMargin: 10; right: parent.right; rightMargin: 10; top: parent.top; topMargin: 50 }
        spacing: 10
    }

    MouseArea {
        z: -1
        anchors.fill: parent
    }

    MouseArea {
        parent: appWindow
        anchors.fill: parent
        enabled: root.state == "open"
        onClicked: close()
    }

    states: State {
        name: "open"
        AnchorChanges { target: root; anchors { bottom: undefined; top: parent.top } }
        PropertyChanges { target: root; anchors.topMargin: -40 }
    }

    transitions: Transition {
        AnchorAnimation { easing.type: Easing.OutQuart; duration: 300 }
    }
}
