import QtQuick 2.0
import "scripts/createobject.js" as ObjectCreator

Page {
    title: "All Item page " + HalalJapanAPI.itemListModel.currentPage

    function gotoPage(selectedPage) {
        toggleBusy(true);
        HalalJapanAPI.getItemFromDatabase(selectedPage, Settings.itemPerPage);
    }

    ListView {

        /*Component.onCompleted: {
            if (count == 0) {
                messages.displayMessage("Empty");
            }
        }*/

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

    PaginationListView {
        height: titleArea.height
        width: parent.width

        anchors { right: parent.right; rightMargin: 8; left: parent.left; }

        id: paginationView
        model: HalalJapanAPI.itemListModel.paginationModel
        currentPage: HalalJapanAPI.itemListModel.currentPage
    }


/*
    Rectangle {
        id: paginationRectangle

        height: titleArea.height
        color: _BACKGROUND_COLOR

        anchors {
            bottom: parent.bottom
            left: parent.left
            right: parent.right
        }

        Label {
            text: HalalJapanAPI.itemListModel.currentPage === 1 ? "|" : "<<";
            anchors {
                left: parent.left
                top:parent.top
                bottom: parent.bottom
            }

            width: parent.width / 2

            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter

            Rectangle {
                anchors {
                    fill: parent;
                    margins: 5
                }
                color: Settings.activeColor
                opacity: 0.5
                radius: 10
                visible: leftMouseArea.pressed
            }

            MouseArea {
                id: leftMouseArea
                onClicked: {
                    if(HalalJapanAPI.itemListModel.currentPage > 1)
                    HalalJapanAPI.getItemFromDatabase(HalalJapanAPI.itemListModel.currentPage - 1, 20);
                }
                anchors.fill: parent
            }
        }

        Label {
            text: ">>"
            width: parent.width / 2

            anchors {
                right: parent.right
                top:parent.top
                bottom: parent.bottom
            }

            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter

            Rectangle {
                anchors {
                    fill: parent;
                    margins: 5
                }
                color: Settings.activeColor
                opacity: 0.5
                radius: 10
                visible: rightMouseArea.pressed
            }

            MouseArea {
                id: rightMouseArea
                onClicked: {
                    HalalJapanAPI.getItemFromDatabase(HalalJapanAPI.itemListModel.currentPage + 1, 20);
                }
                anchors.fill: parent
            }
        }
    }
*/
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
