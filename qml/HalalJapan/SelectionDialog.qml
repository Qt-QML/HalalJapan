import QtQuick 2.0

Dialog {
    id: root

    property alias model: listView.model
    property alias selectedIndex: listView.currentIndex
    property bool emitValueChosenSignal: true

    signal valueChosen(variant value)

    height: (listView.count > 5) || (!appWindow.inPortrait) ? appWindow.height - titleArea.height : (listView.count * 80) + 80
    destroyOnClosing: false
    content: ListView {
        id: listView

        anchors.fill: parent
        clip: true
        currentIndex: -1
        highlightRangeMode: ListView.NoHighlightRange
//        maximumFlickVelocity: Settings.maximumFlickVelocity
        delegate: SettingsDelegate {
            id: selectionDelegate

            onClicked: {
                listView.currentIndex = index;
                if (emitValueChosenSignal) {
                    valueChosen(value);
                }
                accept();
            }
        }

        ScrollBar {}
    }
}
