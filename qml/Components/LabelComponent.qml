import QtQuick 2.0

Rectangle {
    height: parent.height
    width: parent.width * 0.3
    property alias text: txt.text

    Text{
        id:txt
        height: parent.height * 0.6
        width: parent.width * 0.8
        wrapMode: Text.WrapAnywhere
        anchors.centerIn: parent
        horizontalAlignment: Text.AlignHCenter
    }
}
