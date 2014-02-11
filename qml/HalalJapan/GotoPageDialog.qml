import QtQuick 2.0

Dialog {
    id: root
    height: 200
    function setTotalPage(totalPage)
    {
        root.totalPage = totalPage;
    }
    function setCurrentPage(currentPage)
    {
        root.currentPage = currentPage;
    }

    onAccepted: gotoPage(pageInput.text);

    property int totalPage: 1
    property int currentPage: 1

    Label {
        id: titleTextElement
        text: "go to page... (1-" + totalPage + ")"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.margins: 10
        horizontalAlignment: Text.AlignHCenter
    }

    TextField {
        id: pageInput

        anchors { top: titleTextElement.bottom; left: parent.left; right: parent.right; margins: 15}
//        placeholderText: qsTr("Page")
        text: currentPage
        validator: IntValidator { bottom:1; top: totalPage; }
        Keys.onEnterPressed: accept()
        Keys.onReturnPressed: accept()
    }

    Button {
        id: okButton
        height: pageInput.height
        anchors { top: pageInput.bottom; left: parent.left; right: parent.right; bottom: parent.bottom; margins: 15;}
        text: qsTr("OK")

        onClicked: accept();
    }
}
