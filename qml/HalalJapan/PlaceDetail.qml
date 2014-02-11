import QtQuick 2.0

Page {
    id: root
//    title: listView.currentItem.itemData.itemName
    title: HalalJapanAPI.placeListModel.currentPlaceDetail.itemName
//    height: parent.height
//    width: parent.width

    /*tools: Menu {
            menuItems: [
                MenuItem {
                    id: openLocationButton
                    text: qsTr("Open Location")
                    onClicked: {
                        Qt.openUrlExternally("geo:"+HalalJapanAPI.placeListModel.currentPlaceDetail.itemCoordinate)
                    }

                    visible: HalalJapanAPI.placeListModel.currentPlaceDetail.itemCoordinate !== ""
                },

                MenuItem {
                    id: openWebsiteButton
                    text: qsTr("Open Website")
                    onClicked: {
                        Qt.openUrlExternally(HalalJapanAPI.placeListModel.currentPlaceDetail.itemWebsite)
                    }

                    visible: HalalJapanAPI.placeListModel.currentPlaceDetail.itemWebsite !== "-" && HalalJapanAPI.placeListModel.currentPlaceDetail.itemWebsite !== ""
                },

                MenuItem {
                    id: sendEmailButton
                    text: qsTr("Send Email")
                    onClicked: {
                        Qt.openUrlExternally("mailto:"+HalalJapanAPI.placeListModel.currentPlaceDetail.itemEmail)
                    }

                    visible: HalalJapanAPI.placeListModel.currentPlaceDetail.itemEmail !== "-" && HalalJapanAPI.placeListModel.currentPlaceDetail.itemEmail !== ""
                }
            ]
        }*/

    Flickable {
        anchors.fill: parent
        anchors.topMargin: titleArea.height
        contentWidth: parent.width
        contentHeight: Math.max(placeRectangle.height+titleArea.height, parent.height)
//                    contentHeight: parent.height
        flickableDirection: Flickable.VerticalFlick

        Rectangle {
            id: placeRectangle
            anchors {
                top: parent.top
                left: parent.left
                right: parent.right
    //            bottom: placeButton.top
//                bottom: parent.bottom
//                topMargin: titleArea.height
                margins: 10
            }

            height: nameLabel.height + approvedLabel.height + lastUpdateLabel.height + typeLabel.height + addressLabel.height + phoneLabel.height + emailLabel.height + websiteLabel.height + titleArea.height

            border.width: 2
            border.color: Settings.activeColor
            radius: 10

            color: _BACKGROUND_COLOR

            FormLabel {
                id: nameLabel

                anchors {
                    top: parent.top
                    left: parent.left
                    right: parent.right
                    margins: 10
                }

                formTitle: "Name:"
                formText: HalalJapanAPI.placeListModel.currentPlaceDetail.itemName
            }

            FormLabel {
                id: approvedLabel

                anchors {
                    top: nameLabel.bottom
                    left: parent.left
                    right: parent.right
                    margins: 10
                }
                formTitle: "Approved:"
                formText: HalalJapanAPI.placeListModel.currentPlaceDetail.itemApproved ? "Ok" : "Not Approved"
                textColor: HalalJapanAPI.placeListModel.currentPlaceDetail.itemApproved ? "green" : "red"
            }

            FormLabel {
                id: lastUpdateLabel

                anchors {
                    top: approvedLabel.bottom
                    left: parent.left
                    right: parent.right
                    margins: 10
                }
                formTitle: "Last Update:"
                formText: HalalJapanAPI.placeListModel.currentPlaceDetail.itemLastUpdate
            }

            FormLabel {
                id: typeLabel

                anchors {
                    top: lastUpdateLabel.bottom
                    left: parent.left
                    right: parent.right
                    margins: 10
                }
                formTitle: "Type:"
                formText: HalalJapanAPI.placeListModel.currentPlaceDetail.itemType
            }

            FormLabel {
                id: addressLabel

                anchors {
                    top: typeLabel.bottom
                    left: parent.left
                    right: addressButton.visible ? addressButton.left : parent.right
                    margins: 10
                }
                formTitle: "Address:"
                formText: HalalJapanAPI.placeListModel.currentPlaceDetail.itemAddress
            }

            Button {
                id: addressButton
                text: "Open Location"

                anchors {
                    top: addressLabel.top
                    bottom: addressLabel.bottom
                    right: parent.right
                    margins: 5
                }

                onClicked: {
                    Qt.openUrlExternally("geo:"+HalalJapanAPI.placeListModel.currentPlaceDetail.itemCoordinate)
                }

                visible: HalalJapanAPI.placeListModel.currentPlaceDetail.itemCoordinate !== ""
            }

            FormLabel {
                id: phoneLabel

                anchors {
                    top: addressLabel.bottom
                    left: parent.left
                    right: parent.right
                    margins: 10
                }
                formTitle: "Phone:"
                formText: HalalJapanAPI.placeListModel.currentPlaceDetail.itemPhone === "" ? "-" : HalalJapanAPI.placeListModel.currentPlaceDetail.itemPhone
            }

            FormLabel {
                id: emailLabel

                anchors {
                    top: phoneLabel.bottom
                    left: parent.left
                    right: emailButton.visible ? emailButton.left : parent.right
                    margins: 10
                }
                formTitle: "Email:"
                formText: HalalJapanAPI.placeListModel.currentPlaceDetail.itemEmail === "" ? "-" : HalalJapanAPI.placeListModel.currentPlaceDetail.itemEmail
            }

            Button {
                id: emailButton
                text: "Send Email"

                anchors {
                    top: emailLabel.top
                    bottom: emailLabel.bottom
                    right: parent.right
                    margins: 5
                }

                onClicked: {
                    Qt.openUrlExternally("mailto:"+HalalJapanAPI.placeListModel.currentPlaceDetail.itemEmail)
                }

                visible: HalalJapanAPI.placeListModel.currentPlaceDetail.itemEmail !== "-" && HalalJapanAPI.placeListModel.currentPlaceDetail.itemEmail !== ""
            }

            FormLabel {
                id: websiteLabel

                anchors {
                    top: emailLabel.bottom
                    left: parent.left
                    right: websiteButton.visible ? websiteButton.left : parent.right
                    margins: 10
                }
                formTitle: "Website:"
                formText: HalalJapanAPI.placeListModel.currentPlaceDetail.itemWebsite === "" ? "-" : HalalJapanAPI.placeListModel.currentPlaceDetail.itemWebsite
            }

            Button {
                id: websiteButton
                text: "Open Website"

                anchors {
                    top: websiteLabel.top
                    bottom: websiteLabel.bottom
                    right: parent.right
                    margins: 5
                }

                onClicked: {
                    Qt.openUrlExternally(HalalJapanAPI.placeListModel.currentPlaceDetail.itemWebsite)
                }

                visible: HalalJapanAPI.placeListModel.currentPlaceDetail.itemWebsite !== "-" && HalalJapanAPI.placeListModel.currentPlaceDetail.itemWebsite !== ""
            }
        }
    }
}
