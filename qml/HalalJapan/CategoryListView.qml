import QtQuick 2.0
import "scripts/createobject.js" as ObjectCreator

Page {
    title: "All Category page " + HalalJapanAPI.categoryListModel.currentPage

    function gotoPage(selectedPage) {
        HalalJapanAPI.abortBatchMode();
        toggleBusy(true);
        HalalJapanAPI.getCategoryFromDatabase(selectedPage, Settings.categoryPerPage);
    }

    function showGotoPageDialog() {
        var gotoPageDialog = ObjectCreator.createObject(Qt.resolvedUrl("GotoPageDialog.qml"), appWindow);
        gotoPageDialog.setCurrentPage(HalalJapanAPI.categoryListModel.currentPage);
        gotoPageDialog.setTotalPage(HalalJapanAPI.categoryListModel.totalPage);
        gotoPageDialog.open();
    }

    onClosed: {
        HalalJapanAPI.abortBatchMode();
    }

    /*tools: Menu {

        menuItems: [
            MenuItem {
                id: gotoButton
                text: qsTr("Go To Page...")
                onClicked: showGotoPageDialog();
            }
        ]
    }*/

    leftTools: LeftMenu {
        id: leftMenuTools

        listModel:  VisualItemModel {
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

        delegate: itemListDelegate
        model: HalalJapanAPI.categoryListModel

       Component {
           id: itemListDelegate

           Item {
               id: wrapper
               height: !inPortrait ? 120 : 150
               width: parent.width
               anchors {
                   topMargin: 5
                   bottomMargin: 5
               }

               Rectangle {
                   id: horizontalLineSeparator
                   height: 1
                   anchors {
                       top: parent.top
                       left: parent.left
                       right: parent.right
                   }
                   color: "#d0d0d0"
               }

               Rectangle {
                   id: firstSeparator
                   height: parent.height * 3/4
                   width: 1
                   anchors {
                       left: parent.left
                       verticalCenter: parent.verticalCenter
                   }
                   color: "#d0d0d0"
               }

               Rectangle {
                   id: secondColumn
                   width: 150
                   anchors {
                       top: horizontalLineSeparator.bottom
                       bottom: parent.bottom
                       left: firstSeparator.right
                       right: nextItemImage.left
                   }

                   color: _BACKGROUND_COLOR
//                   anchors.margins: 5

                   Label {
                       id: itemNameTextElement
                       text: itemName

                       wrapMode: Text.WordWrap
//                       elide: Text.ElideMiddle
                       maximumLineCount: 2
                       smooth: false

                       verticalAlignment: Text.AlignVCenter

                       anchors {
                           fill: parent
                           leftMargin: 10
                       }
                   }
               }

               Image {
                   id: nextItemImage
                   source: !theme.inverted ? "images/navigation-next-item.png" : "images/navigation-next-item-white.png"
                   fillMode: Image.PreserveAspectFit
                   anchors {
                       verticalCenter: parent.verticalCenter
                       right: parent.right
                   }

                   width: parent.height
               }

               Rectangle {
                   anchors {
                       fill: parent;
                       margins: 5
                   }
                   color: Settings.activeColor
                   opacity: 0.5
                   radius: 10
                   visible: mouseArea.pressed
               }

               MouseArea {
                   id: mouseArea
                   onClicked: {
                       HalalJapanAPI.categoryListModel.currentIndex = index
                       pageStack.push(Qt.resolvedUrl("CategoryDetail.qml"));
                   }
                   anchors.fill: parent
               }
           }
       }
   }

    PaginationListView {
        height: titleArea.height

        id: paginationView
        model: HalalJapanAPI.categoryListModel.paginationModel
        currentPage: HalalJapanAPI.categoryListModel.currentPage
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
