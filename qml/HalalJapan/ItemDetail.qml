import QtQuick 2.0

Page {
    id: root
//    title: listView.currentItem.itemData.itemName
    title: HalalJapanAPI.itemListModel.currentItemDetail.itemName
//    height: parent.height
//    width: parent.width

    Flickable {
        anchors.fill: parent
        anchors.topMargin: titleArea.height
        contentWidth: parent.width
        contentHeight: Math.max((firstCell.height + secondCell.height + (inPortrait ? titleArea.height : 0)), parent.height)
//                    contentHeight: parent.height
        flickableDirection: Flickable.VerticalFlick

        Rectangle {
            id: firstCell
            width: inPortrait ? parent.width : parent.width/3
            height: itemImage.height + statusLabel.height

            radius: 5

            border {
                width: 2
                color: HalalJapanAPI.itemListModel.currentItemDetail.itemStatus === "Halal" ? "green" : HalalJapanAPI.itemListModel.currentItemDetail.itemStatus == "Haram" ? "red" : "grey"
            }


//                        Component.onCompleted: console.log(itemImage.height + " " + statusLabel.height)

            anchors {
                top: parent.top
//                horizontalCenter: inPortrait ? parent.horizontalCenter : undefined
                left: parent.left
                right: inPortrait ? parent.right : undefined
                margins: 5
            }

            Image {
                id: itemImage
                source: HalalJapanAPI.itemListModel.currentItemDetail.itemPic
                fillMode: Image.PreserveAspectFit
//                        smooth: true
                width: parent.width*3/4
//                            height: undefined
//                        width: sourceSize.width
//                        height: sourceSize.height

                anchors {
                    margins: 20
//                                left: parent.left
                    top: parent.top
                    right: parent.right
                    horizontalCenter: parent.horizontalCenter
                }

                /*MouseArea {
                    anchors.fill: parent

                    onClicked: {
                        Qt.openUrlExternally("file://"+HalalJapanAPI.itemListModel.currentItemDetail.itemPic)
                    }
                }*/
            }

            Label {
                id: statusLabel
                text: HalalJapanAPI.itemListModel.currentItemDetail.itemStatus
                color: HalalJapanAPI.itemListModel.currentItemDetail.itemStatus === "Halal" ? "green" : HalalJapanAPI.itemListModel.currentItemDetail.itemStatus == "Haram" ? "red" : "grey"
                font.pixelSize: _LARGE_FONT_SIZE

                anchors {
                    top: itemImage.bottom
                    topMargin: 10
                    horizontalCenter: itemImage.horizontalCenter
                }

                height: titleArea.height * 3/4
            }
        }

        Rectangle {
            id: secondCell
            width: inPortrait ? parent.width : parent.width/3 * 2
            height: nameLabel.height + producerLabel.height + categoryLabel.height + descriptionLabel.height + 60

            radius: 5

            border {
                color: "black"
                width: 2
            }

            anchors {
                top: inPortrait ? firstCell.bottom : parent.top
//                            horizontalCenter: inPortrait ? parent.horizontalCenter : undefined
                left: inPortrait ? parent.left : firstCell.right
                right: parent.right
                margins: 5
            }

            FormLabel {
                id: nameLabel
                formTitle: "Name:"
                formText: HalalJapanAPI.itemListModel.currentItemDetail.itemName

                anchors {
                    left: parent.left
                    margins: 10
                    top: parent.top
                    right: parent.right
                }
            }

            FormLabel {
                id: producerLabel
                formTitle: "Producer:"
                formText: HalalJapanAPI.itemListModel.currentItemDetail.itemProducer

                anchors {
                    left: nameLabel.left
                    margins: 10
                    top: nameLabel.bottom
                    right: nameLabel.right
                }
            }

            FormLabel {
                id: categoryLabel
                formTitle: "Category:"
                formText: HalalJapanAPI.itemListModel.currentItemDetail.itemCategory

                anchors {
                    left: nameLabel.left
                    margins: 10
                    top: producerLabel.bottom
                    right: nameLabel.right
                }
            }

            FormLabel {
                id: descriptionLabel
                formTitle: "Description:"
                formText: HalalJapanAPI.itemListModel.currentItemDetail.itemDesc

                anchors {
                    left: nameLabel.left
                    margins: 10
                    top: categoryLabel.bottom
                    right: nameLabel.right
                }
            }
        }

        /*FormLabel {
            id: ingredientLabel
            formTitle: "Ingredient:"
            formText: HalalJapanAPI.itemListModel.currentItemDetail.itemReason

            anchors {
                left: parent.left
                margins: 10
                top: secondCell.bottom
                right: parent.right
            }
        }*/
    }

    /*ListView {

        Component.onCompleted: {
            contentX = HalalJapanAPI.itemListModel.currentIndex*width
            currentIndex = HalalJapanAPI.itemListModel.currentIndex
        }

        onMovementEnded: {
            currentIndex = contentX/width
        }

        id: listView
        anchors.fill: parent
        anchors.topMargin: titleArea.height
        anchors.bottomMargin: titleArea.height

        highlightFollowsCurrentItem: false
        keyNavigationWraps: true

        orientation: ListView.Horizontal
        snapMode: ListView.SnapOneItem

        model: HalalJapanAPI.itemListModel

        delegate: itemListDelegate
        Component {
            id: itemListDelegate
            Item {
                property variant itemData: model
                id: wrapper
                height: listView.height
                width: listView.width
                clip: true

                Flickable {
//                    height: root.height
//                    width: root.width
                    anchors.fill: parent
                    contentWidth: parent.width
                    contentHeight: Math.max((firstCell.height + secondCell.height + (inPortrait ? titleArea.height : 0)), parent.height)
//                    contentHeight: parent.height
                    flickableDirection: Flickable.VerticalFlick

                    Item {
                        id: firstCell
                        width: inPortrait ? parent.width : parent.width/3
                        height: itemImage.height + statusLabel.height

//                        Component.onCompleted: console.log(itemImage.height + " " + statusLabel.height)

                        anchors {
                            top: parent.top
//                            horizontalCenter: inPortrait ? parent.horizontalCenter : undefined
                            left: parent.left
                            right: inPortrait ? parent.right : undefined
                        }

                        Image {
                            id: itemImage
                            source: pic
                            fillMode: Image.PreserveAspectFit
    //                        smooth: true
                            width: parent.width*3/4
//                            height: undefined
    //                        width: sourceSize.width
    //                        height: sourceSize.height

                            anchors {
                                margins: 20
//                                left: parent.left
                                top: parent.top
                                right: parent.right
                                horizontalCenter: parent.horizontalCenter
                            }
                        }

                        Label {
                            id: statusLabel
                            text: status
                            color: status === "Halal" ? "green" : status == "Haram" ? "red" : "grey"

                            anchors {
                                top: itemImage.bottom
                                topMargin: 10
                                horizontalCenter: itemImage.horizontalCenter
                            }

                            height: titleArea.height * 3/4
                        }
                    }

                    Item {
                        id: secondCell
                        width: inPortrait ? parent.width : parent.width/3 * 2
                        height: nameLabel.height + producerLabel.height

                        anchors {
                            top: inPortrait ? firstCell.bottom : parent.top
//                            horizontalCenter: inPortrait ? parent.horizontalCenter : undefined
                            left: inPortrait ? parent.left : firstCell.right
                            right: parent.right
                        }

                        FormLabel {
                            id: nameLabel
                            formTitle: "Name:"
                            formText: itemName

                            anchors {
                                left: parent.left
                                margins: 10
                                top: parent.top
                                right: parent.right
                            }
                        }

                        FormLabel {
                            id: producerLabel
                            formTitle: "Producer:"
                            formText: producer

                            anchors {
                                left: nameLabel.left
                                margins: 10
                                top: nameLabel.bottom
                                right: nameLabel.right
                            }
                        }
                    }
                }
            }
        }
    }*/
}
