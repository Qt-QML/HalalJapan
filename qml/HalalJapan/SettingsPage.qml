import QtQuick 2.0

Page {
    id: root

    title: qsTr("Settings")

    Flickable {
        id: flicker

        anchors { fill: parent; topMargin: titleArea.height }
        contentWidth: parent.width
        contentHeight: col1.height + 20
        flickableDirection: Flickable.VerticalFlick
        clip: true

        Column {
            id: col1

            anchors { top: parent.top; left: parent.left; right: parent.right }
            spacing: 20

            SelectionItem {
                title: qsTr("Theme")
                model: ListModel {
                    ListElement { name: QT_TR_NOOP("Light"); value: "light" }
                    ListElement { name: QT_TR_NOOP("Dark"); value: "dark" }
                }
                initialValue: Settings.theme
                onValueChosen: Settings.theme = value
            }

            SelectionItem {
                title: qsTr("Item per page")
                model: ListModel {
                    ListElement { name: QT_TR_NOOP("5"); value: "5" }
                    ListElement { name: QT_TR_NOOP("10"); value: "10" }
                    ListElement { name: QT_TR_NOOP("15"); value: "15" }
                    ListElement { name: QT_TR_NOOP("20"); value: "20" }
                    ListElement { name: QT_TR_NOOP("30"); value: "30" }
                    ListElement { name: QT_TR_NOOP("40"); value: "40" }
                }
                initialValue: Settings.itemPerPage
                onValueChosen: Settings.itemPerPage = value
            }

            SelectionItem {
                title: qsTr("Category per page")
                model: ListModel {
                    ListElement { name: QT_TR_NOOP("5"); value: "5" }
                    ListElement { name: QT_TR_NOOP("10"); value: "10" }
                    ListElement { name: QT_TR_NOOP("15"); value: "15" }
                    ListElement { name: QT_TR_NOOP("20"); value: "20" }
                    ListElement { name: QT_TR_NOOP("30"); value: "30" }
                    ListElement { name: QT_TR_NOOP("40"); value: "40" }
                }
                initialValue: Settings.categoryPerPage
                onValueChosen: Settings.categoryPerPage = value
            }

            SelectionItem {
                title: qsTr("Producer per page")
                model: ListModel {
                    ListElement { name: QT_TR_NOOP("5"); value: "5" }
                    ListElement { name: QT_TR_NOOP("10"); value: "10" }
                    ListElement { name: QT_TR_NOOP("15"); value: "15" }
                    ListElement { name: QT_TR_NOOP("20"); value: "20" }
                    ListElement { name: QT_TR_NOOP("30"); value: "30" }
                    ListElement { name: QT_TR_NOOP("40"); value: "40" }
                }
                initialValue: Settings.producerPerPage
                onValueChosen: Settings.producerPerPage = value
            }

            SelectionItem {
                title: qsTr("Place per page")
                model: ListModel {
                    ListElement { name: QT_TR_NOOP("5"); value: "5" }
                    ListElement { name: QT_TR_NOOP("10"); value: "10" }
                    ListElement { name: QT_TR_NOOP("15"); value: "15" }
                    ListElement { name: QT_TR_NOOP("20"); value: "20" }
                    ListElement { name: QT_TR_NOOP("30"); value: "30" }
                    ListElement { name: QT_TR_NOOP("40"); value: "40" }
                }
                initialValue: Settings.placePerPage
                onValueChosen: Settings.placePerPage = value
            }

            Button {
                text: "Reset all settings"
                onClicked: {
                    Settings.resetAllSettings();
                    messages.displayMessage("Settings reset to default");
                    pageStack.pop();
                }
            }
        }
    }
}
