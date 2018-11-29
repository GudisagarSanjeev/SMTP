import QtQuick 2.0
import QtQuick.Controls 2.2

Popup{
  id:messegeDialog

  width: parent.width * 0.5
  height: parent.height * 0.5

  y:parent.height/4 - height/6
  x:parent.width/2 - width/2

  modal: true
  closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside

  property alias text: txt.text
  Rectangle{
      anchors.fill: parent
      Text{
          id:txt
          font.pixelSize: parent.height/8
          anchors.centerIn: parent
      }
  }
}
