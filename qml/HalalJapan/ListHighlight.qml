import QtQuick 2.0

Rectangle {
    id: highlight

    anchors { fill: parent; topMargin: 1; bottomMargin: 1 }
    color: parent.checked ? Settings.activeColor : "#4d4d4d"
    opacity: 0.5
    smooth: true
}
