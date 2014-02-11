import QtQuick 2.0

Item {
    id: button

    property bool useTheme: true
    property bool enabled: true
    property string iconSource
    property alias iconWidth: icon.width
    property alias iconHeight: icon.height
    property alias text: label.text
    property alias textColor: label.color
    property alias textSize: label.textSize
    property int textWidth: label.width
    property bool checked: false
    property bool checkable: false
    property bool pressed: mouseArea.pressed

    signal clicked
    signal pressAndHold

    width: textWidth > 150 ? textWidth + 20 : 150
    height: 90
    opacity: enabled ? 1 : 0.3

    Rectangle {
        id: background

        anchors.fill: button
        radius: 10
        gradient: Gradient {
            GradientStop { id: gradient1; position: 0.0; color: button.useTheme ? Settings.gradientColorHigh : "#524e4e" }
            GradientStop { id: gradient2; position: 0.7; color: button.useTheme ? Settings.gradientColor : "black"}
        }
        border.width: 2
        border.color: Settings.activeColor
        opacity: 0.7
        smooth: true
        state: (mouseArea.pressed) || (checked) ? "highlight" : ""

        states: State {
            name: "highlight"
            PropertyChanges { target: gradient1; color: Qt.lighter(Settings.activeColor, 1.2) }
            PropertyChanges { target: gradient2; color: Settings.activeColor }
        }
    }

    Image {
        id: icon

        anchors.centerIn: button
        width: 50
        height: 50
        smooth: true
        source: iconSource == "" ? "" : "../" + iconSource
        sourceSize.width: icon.width
        sourceSize.height: icon.height
        visible: source != ""
    }

    Label {
        id: label

        property int textSize : 24

        anchors.centerIn: button
        font.pixelSize: textSize
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        
        visible: text != ""
    }

    MouseArea {
        id: mouseArea

        anchors.fill: parent
        enabled: button.enabled
        onClicked: parent.clicked()
        onPressAndHold: parent.pressAndHold()
    }
}



