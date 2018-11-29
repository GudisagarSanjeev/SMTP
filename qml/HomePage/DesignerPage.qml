import QtQuick 2.0
import QtQuick.Controls 2.2
import "../JavaScriptFile/JavaScriptFile.js" as Validator
import "../Components"
Item {
    id:top
    anchors.fill: parent
    Column{
        height: parent.height * 0.95
        width: parent.width * 0.9
        anchors.centerIn: parent
        spacing: parent.height * 0.03
        Row{
            width: parent.width
            height: parent.height * 0.07
            Rectangle{
                width: parent.width
                height: parent.height
                Text{text:"PthinkS Mailer";anchors.centerIn:parent;font.bold: true;font.pixelSize:parent.height * 0.8}
            }
        }
//        Row{
//            width: parent.width
//            height: parent.height * 0.07
//            spacing: parent.width * 0.1
//            LabelComponent{text:"Smtp Server"}
//            TextFieldComponent{id:smtpserver}
//        }
//        Row{
//            width: parent.width
//            height: parent.height * 0.07
//            spacing: parent.width * 0.1
//            LabelComponent{text:"Smtp port"}
//            TextFieldComponent{id:smtpport;text:"465"}
//        }
        Row{
            width: parent.width
            height: parent.height * 0.07
            spacing: parent.width * 0.1
            LabelComponent{text:"Username"}
            TextFieldComponent{id:username
                onEditingFinished: {
                    var email = Validator.validateEmail(username.text);

                    if(!email){
                        dialogbox.text = "Enter valid email"
                        dialogbox.open()
                    }
                }
            }
        }
        Row{
            width: parent.width
            height: parent.height * 0.07
            spacing: parent.width * 0.1
            LabelComponent{text:"Password"}
            TextFieldComponent{id:password;echoMode: TextInput.Password}
        }
        Row{
            width: parent.width
            height: parent.height * 0.07
            spacing: parent.width * 0.1
            LabelComponent{text:"Recipant"}
            TextFieldComponent{id:recipent
            onEditingFinished: {
                var email = Validator.validateEmail(recipent.text);

                if(!email){
                    dialogbox.text = "Enter valid recipent"
                    dialogbox.open()
                }
            }
            }
        }
        Row{
            width: parent.width
            height: parent.height * 0.07
            spacing: parent.width * 0.1
            LabelComponent{text:"Subject"}
            TextFieldComponent{id:subject}
        }
        Row{
            width: parent.width
            height: parent.height * 0.3
            spacing: parent.width * 0.1
            LabelComponent{text:"Messege"}
            TextFieldComponent{id:messege}
        }
        Row{
            width: parent.width
            height: parent.height * 0.07
            spacing: parent.width * 0.1
            LabelComponent{
                id:submit
                text:"Submit"
                width: parent.width * 0.4
                border.color:  "black"
                opacity: 0.5
                MouseArea{
                    anchors.fill: parent
                    hoverEnabled: true
                    onEntered: submit.opacity = 1
                    onExited: submit.opacity = 0.5
                    onClicked: {
                        handler.datareciever(username.text,password.text,recipent.text,subject.text,messege.text)
                        dialogbox.text = "Sending mail..."
                        dialogbox.open()
                    }
                }
            }
            LabelComponent{
                id:exit
                text:"Exit"
                width: parent.width * 0.4
                border.color: "black"
                 opacity: 0.5
                MouseArea{
                    anchors.fill: parent
                    hoverEnabled: true
                    onEntered: exit.opacity = 1
                    onExited: exit.opacity = 0.5
                    onClicked: {
                        Qt.quit()
                    }
                }
            }
        }
    }
    DialogBox{id:dialogbox}
    Connections{
        target: handler
        onPassmeg:{
           dialogbox.text = handler.meg
           console.log(handler.meg)
        }
    }
}


