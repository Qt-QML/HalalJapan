import QtQuick 2.0

Rectangle {
    id: appWindow
    width: 800
    height: 600

    property bool inPortrait: appWindow.height > appWindow.width

    property string _BACKGROUND_COLOR : theme.inverted ? "black" : "white"
    property string _TEXT_COLOR : theme.inverted ? "white" : "black"
    property int _SMALL_FONT_SIZE : 24
    property int _STANDARD_FONT_SIZE : 30
    property int _LARGE_FONT_SIZE : 44


    color: _BACKGROUND_COLOR

    function toggleBusy(isBusy) {
        titleArea.isBusy = isBusy;
    }

    Item {
        objectName: "backKeyNavigationItem"
        focus: true
        Keys.onReleased: {
            if (event.key === Qt.Key_Back) {
                if(pageStack.currentPage.tools !== null && pageStack.currentPage.tools.state === "open") {
                    pageStack.currentPage.tools.close();
                    event.accepted = true;
                }
                else if(pageStack.currentPage.leftTools !== null && pageStack.currentPage.leftTools.state === "open") {
                    pageStack.currentPage.leftTools.close();
                    event.accepted = true;
                }
                else {
                    var dialogExist = false;

                    for(var i=0; i<appWindow.children.length; i++) {
                        if(appWindow.children[i].objectName === "dialog") {
                            if(appWindow.children[i].state === "open") {
                                appWindow.children[i].close(true);
                                dialogExist = true;
                                event.accepted = true;
                                break;
                            }
                        }
                    }

                    if(!dialogExist) {
                        if (pageStack.depth > 1) {
        //                    if (!titleArea.isBusy)
                            if (!messageDialog.visible) {
                                titleArea.isBusy = false;
                                pageStack.pop();
                            }
                            event.accepted = true;
                        }
                        else {
                            Qt.quit();
                        }
                    }
                }
            }
        }
    }

    QtObject {
        id: theme

        property bool inverted: (Settings.theme === "dark")
    }

    Connections {
        /* Connect to signals from C++ object Database */
        target: HalalJapanAPI
        onFinished: toggleBusy(false);
        onAlert: messages.displayMessage(message);
    }

    PageStack {
        id: pageStack

        anchors.fill: parent
        initialPage: Qt.resolvedUrl("HomePage.qml")
    }

    TitleArea {
        id: titleArea
        parent: appWindow
//        parent: pageStack
        height: Utils.screenWidth>Utils.screenHeight ? Utils.screenHeight/7 : Utils.screenWidth/7
    }

    InfoBanner {
        id: messages
    }

    MessageDialog {
        id: messageDialog
    }
}
