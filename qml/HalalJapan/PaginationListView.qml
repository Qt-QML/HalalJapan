import QtQuick 2.0

Item {
    id: root

    signal clicked
    signal pressed
    property alias model: paginationListView.model
    property int currentPage


    anchors { left: parent.left; right: parent.right; bottom: parent.bottom }

    Rectangle {
        id: pageBackground

        anchors.fill: parent
        color: _BACKGROUND_COLOR
    }

    Rectangle {
            id: line
            height: 1
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
    //        anchors.bottom: paginationView.top
            color: "#d0d0d0"
    }

    ListView {
        id: paginationListView
        anchors.fill: parent
        interactive: false
        clip: true

        delegate: paginationListDelegate
        model: paginationListModel
        orientation: ListView.Horizontal

        Component {
            id: paginationListDelegate

            Item {
                id: wrapper
                height: parent.height
                width: ((appWindow.width > 0) ? appWindow.width : parent.width) / paginationListView.count

                Rectangle {
                    anchors { fill: parent; margins: 5 }
                    color: Settings.activeColor
                    opacity: 0.5
                    radius: 10
                    visible: mouseArea.pressed
                }

                Label {
//                    anchors.fill: parent
                    anchors.centerIn: parent
                    id: nameTextElement
                    text: textLabel
                    color: (pageNumber == currentPage) ? Settings.activeColor : _TEXT_COLOR
                    font.bold: (pageNumber == currentPage) ? true : false
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter

//                    anchors.left: (paginationListView.currentIndex == 0) ? parent.left : paginationListView.indexAt(paginationListView.currentIndex - 1).left
//                    anchors.right: (currentIndex == paginationListView.model.count - 1) ? parent.right
                }

                MouseArea {
                    id: mouseArea

                    anchors.fill: parent
                    onClicked: {
                        gotoPage(pageNumber);
//                            root.currentPage = pageNumber;
//                            root.clicked();
                    }
                }
            }
        }
    }
}
