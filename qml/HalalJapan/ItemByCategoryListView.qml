import QtQuick 2.0
import "scripts/createobject.js" as ObjectCreator

Page {
    title: "All item on category " + categoryName + " page " + HalalJapanAPI.itemListModel.currentPage
    property int categoryId: 0
    property string categoryName: "category"

    function gotoPage(selectedPage) {
        toggleBusy(true);
        HalalJapanAPI.getItemByCategory(categoryName, selectedPage, Settings.itemPerPage);
    }

    ListView {
        currentIndex: -1
        highlightFollowsCurrentItem: false
        highlightRangeMode: ListView.NoHighlightRange

        id: itemListView
        anchors {
            fill: parent
            topMargin: titleArea.height
            bottomMargin: paginationView.height
        }

        clip: true
//        focus: false

        delegate: ItemDelegate{}
        model: HalalJapanAPI.itemListModel
    }

    Rectangle {
        height: titleArea.height
        width: parent.width

        anchors { right: parent.right; left: parent.left; bottom: parent.bottom}

        id: paginationView
        color: _BACKGROUND_COLOR
//        model: HalalJapanAPI.itemListModel.paginationModel
//        currentPage: HalalJapanAPI.itemListModel.currentPage

        Item {
            id: leftWrapper
            height: parent.height

            anchors {
                left: parent.left
                right: rightWrapper.visible ? parent.horizontalCenter : parent.right
            }

            visible: HalalJapanAPI.itemListModel.currentPage > 1

            Rectangle {
                anchors { fill: parent; margins: 5 }
                color: Settings.activeColor
                opacity: 0.5
                radius: 10
                visible: leftMouseArea.pressed
            }

            Label {
//                    anchors.fill: parent
                anchors.centerIn: parent
                id: leftTextElement
                text: "<<"
//                color: (pageNumber == currentPage) ? Settings.activeColor : _TEXT_COLOR
//                font.bold: (pageNumber == currentPage) ? true : false
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter

//                    anchors.left: (paginationListView.currentIndex == 0) ? parent.left : paginationListView.indexAt(paginationListView.currentIndex - 1).left
//                    anchors.right: (currentIndex == paginationListView.model.count - 1) ? parent.right
            }

            MouseArea {
                id: leftMouseArea

                anchors.fill: parent
                onClicked: gotoPage(HalalJapanAPI.itemListModel.currentPage-1)
            }
        }

        Item {
            id: rightWrapper
            height: parent.height

            anchors {
                left: leftWrapper.visible ? parent.horizontalCenter : parent.left
                right: parent.right
            }

            Rectangle {
                anchors { fill: parent; margins: 5 }
                color: Settings.activeColor
                opacity: 0.5
                radius: 10
                visible: rightMouseArea.pressed
            }

            Label {
//                    anchors.fill: parent
                anchors.centerIn: parent
                id: rightTextElement
                text: ">>"
//                color: (pageNumber == currentPage) ? Settings.activeColor : _TEXT_COLOR
//                font.bold: (pageNumber == currentPage) ? true : false
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter

//                    anchors.left: (paginationListView.currentIndex == 0) ? parent.left : paginationListView.indexAt(paginationListView.currentIndex - 1).left
//                    anchors.right: (currentIndex == paginationListView.model.count - 1) ? parent.right
            }

            MouseArea {
                id: rightMouseArea

                anchors.fill: parent
                onClicked: gotoPage(HalalJapanAPI.itemListModel.currentPage+1)
            }
        }
    }

    Rectangle {
        id: bottomLineSeparator
        height: 1
        anchors {
            top: paginationView.top
            left: parent.left
            right: parent.right
        }

        color: "#d0d0d0"
    }
}
