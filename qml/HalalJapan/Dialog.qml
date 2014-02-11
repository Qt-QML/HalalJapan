import QtQuick 2.0

FocusScope {
    id: root

    objectName: "dialog"

//    Component.onCompleted: console.log(titleArea.z + " " + root.z)

    property alias icon: icon.source
    property alias titleText: title.text
    property alias content: content.children
    property alias buttons: buttonColumn.children
    property bool destroyOnClosing: true
    property bool isChild: false

    signal accepted
    signal rejected
    signal opened
    signal closed

    z: titleArea.z + 1

    function accept() {
        root.accepted();
        root.close(false);
    }

    function reject() {
        root.rejected();
        root.close(false);
    }

    function open() {
        pageStack.dim();
        root.state = "open";
        root.opened();
    }

    function close(emitClosedSignal) {
        root.state = "";
        if (emitClosedSignal) {
            closed();
        }
        if (!isChild) {
            pageStack.undim();
        }
        if (destroyOnClosing) {
            root.destroy();
        }
    }

    function lowerOpacity() {
        root.opacity = 0;
    }

    function raiseOpacity() {
        root.opacity = 1;
    }

    parent: appWindow
    height: appWindow.height - 100
    anchors { left: parent.left; right: parent.right; top: parent.bottom }

    Rectangle {
        id: background

        anchors.fill: root
        color: _BACKGROUND_COLOR
        opacity: 0.8
    }

    Rectangle {
        height: 2
        anchors { left: root.left; right: root.right; top: root.top }
        color: Settings.activeColor
        opacity: 0.5
    }

    Image {
        id: icon

        width: 64
        height: 64
        anchors { top: root.top; topMargin: 10; horizontalCenter: content.horizontalCenter }
        visible: source != ""
        smooth: true
    }

    Label {
        id: title

        anchors { top: icon.visible ? icon.bottom : root.top; topMargin: 10; horizontalCenter: icon.visible ? content.horizontalCenter : root.horizontalCenter }
        
        
        font.bold: true
        visible: text != ""
    }

    Item {
        id: content

        anchors {
            left: root.left; leftMargin: 10;
            right: root.right; rightMargin: (!appWindow.inPortrait) && (buttonColumn.visible) ? buttonColumn.width + 20 : 10;
            top: title.bottom; topMargin: 10;
            bottom: root.bottom; bottomMargin: (appWindow.inPortrait) && (buttonColumn.visible) ? buttonColumn.height + 20 : 10
        }
    }

    Column {
        id: buttonColumn

        anchors { right: root.right; bottom: root.bottom; margins: 10 }
        visible: children.length > 0
        spacing: 10
    }

    /*MouseArea {
        z: -1
        anchors.fill: root
    }*/

    MouseArea {
        parent: appWindow
        anchors.fill: parent
        enabled: root.state != ""
        onClicked: close(true)
    }

    states: State {
        name: "open"
        AnchorChanges { target: root; anchors { top: undefined; bottom: parent.bottom } }
    }

    transitions: Transition {
        AnchorAnimation { easing.type: Easing.OutQuart; duration: 300 }
    }
}
