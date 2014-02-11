import QtQuick 2.0


Page {
    id: root

    title: "Halal Japan"

    /*tools: Menu {
        menuItems: [
            MenuItem {
                id: firstSyncButton
                text: HalalJapanAPI.batchMode ? qsTr("Stop Synchronize"):  qsTr("First Synchronize")
                onClicked: {
                    HalalJapanAPI.batchMode = !HalalJapanAPI.batchMode;
                    if(HalalJapanAPI.batchMode)
                    {
                        toggleBusy(true);
                        HalalJapanAPI.busyMessage = "Synchronizing..."
                        HalalJapanAPI.firstSync();
                    }
                }

//                useTheme: false
            },

            MenuItem {
                id: settingsButton
                text: qsTr("Settings")
                onClicked: pageStack.push(Qt.resolvedUrl("SettingsPage.qml"));
            },

            MenuItem {
                id: aboutButton
                text: qsTr("About")
                onClicked: console.log("about")

//                useTheme: false
            }
        ]
    }*/

    leftTools: LeftMenu {
        id: leftMenuTools
        /*menuItems: [
            ListItem {
                text: HalalJapanAPI.batchMode ? qsTr("Stop Synchronize"):  qsTr("First Synchronize")
                onClicked: {
                    HalalJapanAPI.batchMode = !HalalJapanAPI.batchMode;
                    if(HalalJapanAPI.batchMode)
                    {
                        toggleBusy(true);
                        HalalJapanAPI.busyMessage = "Synchronizing..."
                        HalalJapanAPI.firstSync();
                    }
                }

//                useTheme: false
            },

            ListItem {
                text: qsTr("Settings")
                onClicked: pageStack.push(Qt.resolvedUrl("SettingsPage.qml"));
            },

            ListItem {
                id: aboutListItem
                text: qsTr("About")
                onClicked: {
                    console.log("about")
                }

//                useTheme: false
            }
        ]*/

        listModel:  VisualItemModel {
            LeftMenuItem {
                height: titleArea.height

                text: "Synchronize"

                onClicked: {
                    HalalJapanAPI.batchMode = !HalalJapanAPI.batchMode;
                    if(HalalJapanAPI.batchMode)
                    {
                        toggleBusy(true);
                        HalalJapanAPI.busyMessage = "Synchronizing..."
                        HalalJapanAPI.firstSync();
                    }
                }
            }

            LeftMenuItem {
                height: titleArea.height
                text: "Settings"

                onClicked: {
                    pageStack.push(Qt.resolvedUrl("SettingsPage.qml"));
                }
            }

            LeftMenuItem {
                height: titleArea.height
                text: "About"

                onClicked: {
//                    pageStack.push(Qt.resolvedUrl("SettingsPage.qml"));
                }
            }
        }
    }

    Grid {
        id: iconGrid

        anchors { fill: parent; topMargin: titleArea.height }
        columns: !appWindow.inPortrait ? 2 : 1
        rows: !appWindow.inPortrait ? 2 : 4

        /*Button {
            text: "testing"
            onClicked: {
                HalalJapanAPI.getItemFromDatabase(7, 20);
                pageStack.push(Qt.resolvedUrl("ItemList.qml"));
            }
        }*/
        NavButton {
            iconSource: "images/item-icon.png"
            label: "All Item"

            height: parent.height / iconGrid.rows
            width: parent.width / iconGrid.columns

            onClicked: {
                toggleBusy(true);
                HalalJapanAPI.getItemFromDatabase(1, Settings.itemPerPage);
                pageStack.push(Qt.resolvedUrl("ItemListView.qml"));
            }
        }

        NavButton {
            iconSource: "images/category-icon.png"
            label: "All Category"

            height: parent.height / iconGrid.rows
            width: parent.width / iconGrid.columns

            onClicked: {
                toggleBusy(true);
                HalalJapanAPI.getCategoryFromDatabase(1, Settings.categoryPerPage);
                pageStack.push(Qt.resolvedUrl("CategoryListView.qml"));
            }
        }

        NavButton {
            iconSource: "images/producer-icon.png"
            label: "All Producer"

            height: parent.height / iconGrid.rows
            width: parent.width / iconGrid.columns

            onClicked: {
                toggleBusy(true);
                HalalJapanAPI.getProducerFromDatabase(1, Settings.producerPerPage);
                pageStack.push(Qt.resolvedUrl("ProducerListView.qml"));
            }
        }

        NavButton {
            iconSource: "images/place-icon.png"
            label: "All Place"

            height: parent.height / iconGrid.rows
            width: parent.width / iconGrid.columns

            onClicked: {
                toggleBusy(true);
                HalalJapanAPI.getPlaceFromDatabase(1, Settings.placePerPage);
                pageStack.push(Qt.resolvedUrl("PlaceListView.qml"));
            }
        }
    }

    /*Connections {

            target: HalalJapanAPI
            onNewItemWindow: {
                pageStack.push(Qt.resolvedUrl("ItemList.qml"));
            }
        }*/
}
