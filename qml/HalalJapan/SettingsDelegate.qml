import QtQuick 2.0

Item {
    id: root

    signal clicked

    width: root.ListView.view.width
    height: 80

    ListHighlight {
        visible: (mouseArea.pressed) || (root.ListView.view.currentIndex == index)
    }

    Label {
        id: titleText

        anchors { left: root.left; leftMargin: 10; right: root.right; rightMargin: 10; verticalCenter: root.verticalCenter }
        elide: Text.ElideRight
        text: name
        
        
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }

    MouseArea {
        id: mouseArea

        anchors.fill: root
        onClicked: root.clicked()
    }
}
