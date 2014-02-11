import QtQuick 2.0

Item {
    id: root

    property alias isBusy: busyIndicator.isBusy

//    parent: pageStack
    height: 60
    anchors { left: parent.left; right: parent.right; top: parent.top }

    Rectangle {
        id: background

        anchors.fill: parent
        color: _BACKGROUND_COLOR
    }

    Rectangle {
        height: 1
        anchors { left: parent.left; right: parent.right; bottom: parent.bottom }
        color: Settings.activeColor
        opacity: 0.5
    }

    ToolIcon {
        id: minimizeButton

        width: parent.height
        height: parent.height
        anchors { verticalCenter: parent.verticalCenter; left: parent.left }
        iconSource: pageStack.currentPage.leftTools === null ? "HalalJapan/images/minimize-grey.png" : !theme.inverted ? "HalalJapan/images/minimize.png" : "HalalJapan/images/minimize-white.png"
//        onClicked: Utils.minimize()
        onClicked: {
            if (pageStack.currentPage !== null && pageStack.currentPage.leftTools !== null)
                pageStack.currentPage.leftTools.open()
        }
    }

    Rectangle {
        id: leftSeparator

        width: 1
        height: parent.height/2
        anchors {
            left: minimizeButton.right
            verticalCenter: parent.verticalCenter
        }
        color: Settings.activeColor
        opacity: 0.5
    }

    SystemInfoArea {
        id: systemInfo

        anchors { left: leftSeparator.right; verticalCenter: parent.verticalCenter }
    }

    Item {
        anchors { left: systemInfo.right; leftMargin: 10; right: busyIndicator.visible ? busyIndicator.left : rightSeparator.left; rightMargin: 10; top: parent.top; bottom: parent.bottom }

        Label {
            id: title

            property int maximumWidth: parent.width - menuIndicator.width - 10

            width: paintedWidth < maximumWidth ? paintedWidth : maximumWidth
            anchors { left: parent.left; verticalCenter: parent.verticalCenter }

            clip: true

            verticalAlignment: Text.AlignVCenter
            text: !pageStack.currentPage ? "Halal Japan" : pageStack.currentPage.title
        }

        MenuIndicator {
            id: menuIndicator

            anchors { left: title.right; leftMargin: 10; verticalCenter: parent.verticalCenter; verticalCenterOffset: -3 }
            visible: pageStack.currentPage !== null && pageStack.currentPage.tools !== null
//            visible: false
        }
    }

    MouseArea {
        anchors { left: systemInfo.right; right: rightSeparator.left; top: parent.top; bottom: parent.bottom }
        enabled: pageStack.currentPage !== null && pageStack.currentPage.tools !== null
        onClicked: pageStack.currentPage.tools.open()
    }

    Image {
        id: busyIndicator

        property bool isBusy: false

        width: 30
        height: 30
        anchors { right: rightSeparator.left; rightMargin: 10; verticalCenter: parent.verticalCenter }
        source: "images/busy.png"
        sourceSize.width: busyIndicator.width
        sourceSize.height: busyIndicator.height
        smooth: true
        visible: isBusy
        opacity: 0

        NumberAnimation on rotation {
            running: busyIndicator.opacity > 0; from: 0; to: 360; loops: Animation.Infinite; duration: 1500
        }

        states: State {
            name: "busy"
            when: busyIndicator.isBusy
            PropertyChanges { target: busyIndicator; opacity: 1 }
        }

        transitions: Transition {
            PropertyAnimation { properties: "opacity"; duration: 300 }
        }
    }

    Rectangle {
        id: rightSeparator

        width: 1
        height: parent.height/2
        anchors { right: backButton.left; verticalCenter: parent.verticalCenter }
        color: Settings.activeColor
        opacity: 0.5
    }

    ToolIcon {
        id: backButton

        width: parent.height
        height: parent.height
        anchors { verticalCenter: parent.verticalCenter; right: parent.right }
        iconSource: pageStack.index > 0 ?  !theme.inverted ? "HalalJapan/images/back.png" : "HalalJapan/images/back-white.png" : !theme.inverted ? "HalalJapan/images/close.png" : "HalalJapan/images/close-white.png"
        onClicked: {
//            busyIndicator.isBusy = false;
            if(pageStack.index > 0) {
                pageStack.pop();
            }
            else {
                Qt.quit()
            }
        }
        onPressAndHold: {
            if (pageStack.index > 0) {
                pageStack.clear()
                pageStack.push(pageStack.initialItem);
                busyIndicator.isBusy = false;
            }
        }
    }

    /*MouseArea {
        anchors.fill: parent
        z: -1
    }*/
}




