import QtQuick 2.0

Loader {
    id: messages

    function displayMessage(message) {
        /* Display a notification using the message banner */

            messages.source = "";
            messages.source = Qt.resolvedUrl("InfoBannerComponent.qml");
            messages.item.message = message;

        toggleBusy(false);
    }

    width: appWindow.width
    anchors.bottom: appWindow.top
    z: 1
    onLoaded: {
        messages.item.state = appWindow.state;
        timer.running = true;
        messages.state = "show"
    }

    Timer {
        id: timer

        interval: 2500
        onTriggered: messages.state = ""
    }

    states: State {
        name: "show"
        AnchorChanges { target: messages; anchors { bottom: undefined; top: appWindow.top } }
        PropertyChanges { target: messages; anchors.topMargin: titleArea.height }
    }

    transitions: Transition {
        AnchorAnimation { easing.type: Easing.OutQuart; duration: 300 }
    }

}
