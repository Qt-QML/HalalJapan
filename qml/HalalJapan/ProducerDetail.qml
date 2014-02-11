import QtQuick 2.0

Page {
    id: root
    title: HalalJapanAPI.producerListModel.currentCategoryDetail.itemName

    Rectangle {
        id: categoryRectangle
        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
            bottom: categoryButton.top
            topMargin: titleArea.height
            margins: 10
        }

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
            formText: HalalJapanAPI.producerListModel.currentCategoryDetail.itemName
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
            formText: HalalJapanAPI.producerListModel.currentCategoryDetail.itemApproved ? "Ok" : "Not Approved"
            textColor: HalalJapanAPI.producerListModel.currentCategoryDetail.itemApproved ? "green" : "red"
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
            formText: HalalJapanAPI.producerListModel.currentCategoryDetail.itemLastUpdate
        }
    }

    Button {
        id: categoryButton

        anchors {
            bottom: parent.bottom
            left: parent.left
            right: parent.right
            margins: 10
        }
        text: "Open items produced by this producer"

        onClicked: {
            pageStack.push(Qt.resolvedUrl("ItemByProducerListView.qml"));
            pageStack.currentPage.producerId = HalalJapanAPI.producerListModel.currentCategoryDetail.itemId;
            pageStack.currentPage.producerName = HalalJapanAPI.producerListModel.currentCategoryDetail.itemName;

            HalalJapanAPI.getItemByProducer(HalalJapanAPI.producerListModel.currentCategoryDetail.itemName, 1, Settings.itemPerPage);
        }
    }
}
