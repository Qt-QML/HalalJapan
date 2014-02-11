import QtQuick 2.0

Item {
    id: root

    signal closed;

    Component.onDestruction: root.close()

    function close() {
        root.closed();
    }

    property string title
    property Item tools: null
    property Item leftTools: null
}
