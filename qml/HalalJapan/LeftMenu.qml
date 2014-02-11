import QtQuick 2.0

Item {
    id: root

    property alias listModel: menuList.model
//    property alias menuItems: menuLayout.children
//    property alias listDelegate: menuList.delegate

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
    width: appWindow.width - titleArea.height
//    closeMenuButton.width
//    height: menuLayout.height + 60
    anchors { top: parent.top; bottom: parent.bottom; right: parent.left; topMargin: -2; bottomMargin: -2}
//        rightMargin: closeMenuButton.width}

    Rectangle {
        id: backgroundRectangle
        anchors.fill: parent
        color: _BACKGROUND_COLOR
//        radius: 10
//        opacity: 0.8
        border.width: 2
        border.color: Settings.activeColor
    }

    /*ToolIcon {
        id: closeMenuButton

        width: 80
        height: titleArea.height
        anchors { top: parent.top; left: parent.right }
//        color: "black"
        iconSource: !theme.inverted ? "HalalJapan/images/minimize.png" : "HalalJapan/images/minimize-white.png"
//        onClicked: Utils.minimize()
        onClicked: close()

//        visible: false
    }*/

/*    Flickable {
        anchors { left: parent.left; top: parent.top; bottom: parent.bottom; right: closeMenuButton.left }
        flickableDirection: Flickable.VerticalFlick

        Flow {
            id: menuLayout
            anchors.fill: parent

    //        spacing: 10
        }
    }*/

    ListView {
        id: menuList

//        anchors { left: parent.left; top: parent.top; bottom: parent.bottom; right: parent.left }
//        closeMenuButton.left }
        anchors.fill: parent
        anchors.topMargin: 2

        /*delegate: Item {
            height: titleArea.height
//            width: menuList.width
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.margins: 2

            Rectangle {
//                color: (index % 2 == 1) ? "grey" : "lightgray"
                color: _BACKGROUND_COLOR
                anchors.fill: parent

                Label {
                    id: name
                    text: menuName
                    anchors.fill: parent
                    verticalAlignment: Text.AlignVCenter
//                    anchors.verticalCenter: parent.verticalCenter
                    anchors.leftMargin: 10
//                    anchors.left: parent.left
                }
            }
        }*/
    }

    MouseArea {
        z: -1
        anchors.fill: parent
    }

    MouseArea {
        parent: appWindow
        anchors.fill: parent
        enabled: root.state == "open"
        onClicked: {
            close()
        }
    }

    states: State {
        name: "open"
        AnchorChanges { target: root; anchors { right: undefined; left: parent.left } }
        PropertyChanges { target: root; anchors.leftMargin: -2 }
    }

    transitions: Transition {
        AnchorAnimation { easing.type: Easing.OutQuart; duration: 300 }
    }
}
