import QtQuick 2.0

Page {
    id: root
//    title: listView.currentItem.itemData.itemName
    title: HalalJapanAPI.categoryListModel.currentCategoryDetail.itemName
//    height: parent.height
//    width: parent.width

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
            formText: HalalJapanAPI.categoryListModel.currentCategoryDetail.itemName
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
            formText: HalalJapanAPI.categoryListModel.currentCategoryDetail.itemApproved ? "Ok" : "Not Approved"
            textColor: HalalJapanAPI.categoryListModel.currentCategoryDetail.itemApproved ? "green" : "red"
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
            formText: HalalJapanAPI.categoryListModel.currentCategoryDetail.itemLastUpdate
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
        text: "Open items on this category"

        onClicked: {
            pageStack.push(Qt.resolvedUrl("ItemByCategoryListView.qml"));
            pageStack.currentPage.categoryId = HalalJapanAPI.categoryListModel.currentCategoryDetail.itemId;
            pageStack.currentPage.categoryName = HalalJapanAPI.categoryListModel.currentCategoryDetail.itemName;

            HalalJapanAPI.getItemByCategory(HalalJapanAPI.categoryListModel.currentCategoryDetail.itemName, 1, Settings.itemPerPage);
        }
    }
}
