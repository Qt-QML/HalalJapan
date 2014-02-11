import QtQuick 2.0
import "scripts/createobject.js" as ObjectCreator

Page {
    title: "All Item page " + HalalJapanAPI.itemListModel.currentPage

    function gotoPage(selectedPage) {
        HalalJapanAPI.abortBatchMode();
        toggleBusy(true);
        HalalJapanAPI.getItemFromDatabase(selectedPage, Settings.itemPerPage);
    }

    function showGotoPageDialog() {
        var gotoPageDialog = ObjectCreator.createObject(Qt.resolvedUrl("GotoPageDialog.qml"), appWindow);
        gotoPageDialog.setCurrentPage(HalalJapanAPI.itemListModel.currentPage);
        gotoPageDialog.setTotalPage(HalalJapanAPI.itemListModel.totalPage);
        gotoPageDialog.open();
    }

    onClosed: {
        HalalJapanAPI.abortBatchMode();
    }

    leftTools: LeftMenu {
        id: leftMenuTools

        listModel:  VisualItemModel {
            LeftMenuItem {
                height: titleArea.height

                id: retrieveAllItemsButton
                text: HalalJapanAPI.batchMode ? qsTr("Stop retrieve items") : qsTr("Retrieve all items")
                onClicked: {
                    if(retrieveAllItemsButton.text === "Retrieve all items") {
                        toggleBusy(true);
                        HalalJapanAPI.retrieveAllItem();
                    }
                    else {
                        HalalJapanAPI.abortBatchMode();
                        toggleBusy(false);
                        HalalJapanAPI.busyMessage = "";
                    }
                }
            }

            LeftMenuItem {
                height: titleArea.height
                id: gotoButton
                text: qsTr("Go To Page...")
                onClicked: showGotoPageDialog();
            }
        }
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

    PaginationListView {
        height: titleArea.height

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
