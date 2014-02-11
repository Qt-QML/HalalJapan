import QtQuick 2.0
import QtQuick.Controls 1.0

StackView {
    id: pageView
    anchors.fill: parent

    property alias initialPage: pageView.initialItem
    property Item currentPage: pageView.currentItem
    property int index: pageView.depth - 1

    function replace(item, immediate) {
        pageView.pop()
        pageView.push(item)
    }

    function dim() {
        pageView.state = "dim";
    }

    function undim() {
        pageView.state = "";
    }

    states: State {
        name: "dim"
        PropertyChanges { target: pageView; opacity: 0.1 }
    }

    transitions: Transition {
        PropertyAnimation { target: pageView; properties: "opacity"; duration: 300 }
    }
}
