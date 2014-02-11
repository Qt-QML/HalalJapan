import QtQuick 2.0
import "scripts/createobject.js" as ObjectCreator

Page {
    title: "All Place page " + HalalJapanAPI.placeListModel.currentPage

    function gotoPage(selectedPage) {
        HalalJapanAPI.abortBatchMode();
        toggleBusy(true);
        HalalJapanAPI.getPlaceFromDatabase(selectedPage, Settings.placePerPage);
    }

    function showGotoPageDialog() {
        var gotoPageDialog = ObjectCreator.createObject(Qt.resolvedUrl("GotoPageDialog.qml"), appWindow);
        gotoPageDialog.setCurrentPage(HalalJapanAPI.placeListModel.currentPage);
        gotoPageDialog.setTotalPage(HalalJapanAPI.placeListModel.totalPage);
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
        model: HalalJapanAPI.placeListModel

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

//               visible: itemName.length > 0 || approved.length > 0

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
/*
               Rectangle {
                   id: firstColumn
                   width: 150
                   anchors {
                       top: horizontalLineSeparator.bottom
                       bottom: parent.bottom
                       left: parent.left
                       margins: 5
                   }

                   color: _BACKGROUND_COLOR

                   Image {
                       id: thumbnailImage
                       height: 70
                       anchors {
                           centerIn: parent
                           margins: 5
                       }
                       source: thumb
                       fillMode: Image.PreserveAspectFit

                       Component.onCompleted: {
                           if(status !== 1) {
//                               width = 25;
//                               visible = false;
                               fillMode = Image.PreserveAspectFit
                               source = "images/not-found.png";
                           }
                       }
                   }
               }
*/
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

//                       color: statusTextElement.visible ? _TEXT_COLOR : status === "Halal" ? "green" : status === "Haram" ? "red" : "grey"
                   }

                   /*Label {
                       id: statusTextElement
                       text: status
                       color: status === "Halal" ? "green" : status == "Haram" ? "red" : "grey"

                       wrapMode: Text.WordWrap
                       horizontalAlignment: Text.AlignHCenter

                       verticalAlignment: Text.AlignVCenter

                       anchors {
//                           left: nameTextElement.right
                           top: parent.top
                           bottom: parent.bottom
                           right: parent.right
                       }

                       width: parent.height

                       visible: !inPortrait
                   }*/
               }

               Image {
                   id: nextItemImage
                   source: !theme.inverted ? "images/navigation-next-item.png" : "images/navigation-next-item-white.png"
                   fillMode: Image.PreserveAspectFit
                   anchors {
                       verticalCenter: parent.verticalCenter
                       right: parent.right
//                       top: parent.top
//                       bottom: parent.bottom
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
                       HalalJapanAPI.placeListModel.currentIndex = index
                       pageStack.push(Qt.resolvedUrl("PlaceDetail.qml"));
                   }
                   anchors.fill: parent
               }
           }
       }
   }

    PaginationListView {
        height: titleArea.height

        id: paginationView
        model: HalalJapanAPI.placeListModel.paginationModel
        currentPage: HalalJapanAPI.placeListModel.currentPage
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
