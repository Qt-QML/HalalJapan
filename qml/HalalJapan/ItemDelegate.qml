import QtQuick 2.0

Component {
    id: itemListDelegate

    Item {
        id: wrapper
        height: !inPortrait ? 150 : 180
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

        Rectangle {
            id: firstSeparator
            height: parent.height * 3/4
            width: 1
            anchors {
                left: firstColumn.right
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
                elide: Text.ElideMiddle
                maximumLineCount: 2
                smooth: false

                verticalAlignment: Text.AlignVCenter

                anchors {
                    left: parent.left
                    top: parent.top
                    bottom: parent.bottom
                    right: statusTextElement.visible ? statusTextElement.left : parent.right
                    leftMargin: 10
                }

                color: statusTextElement.visible ? _TEXT_COLOR : status === "Halal" ? "green" : status === "Haram" ? "red" : "grey"
            }

            Label {
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
            }
        }

        Image {
            id: nextItemImage
            source: !theme.inverted ? "images/navigation-next-item.png" : "images/navigation-next-item-white.png"
            fillMode: Image.PreserveAspectFit
            anchors {
                right: parent.right
                top: parent.top
                bottom: parent.bottom
            }
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
//                       console.log("clicked " + id + " " + itemName + " " + status)
//                       itemListView.currentIndex = index;
                HalalJapanAPI.itemListModel.currentIndex = index
//                       console.log(HalalJapanAPI.itemListModel.currentItemMap.name);
                pageStack.push(Qt.resolvedUrl("ItemDetail.qml"));
            }
            anchors.fill: parent
        }
    }
}
