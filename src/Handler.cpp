#include "Handler.h"

Handler::Handler()
{
    qDebug()<<Q_FUNC_INFO<<endl;
}

void Handler::datareciever(QString username, QString password, QString recipent, QString subject, QString meg)
{
    qDebug()<<Q_FUNC_INFO<<endl;

    if(username.endsWith("gmail.com")){
        server = "smtp.gmail.com";
        port = 465;
    }else if(username.endsWith("yahoo.com")){
        server = "smtp.mail.yahoo.com";
        port = 465;
    }
    smtp=new SmtpClass(username,password,server,port,timeout);

    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));
    smtp->sendMail(username,recipent,subject,meg);
}
void Handler::mailSent(QString status)
{
     qDebug()<<Q_FUNC_INFO<<endl;
     meg = status;
     if(meg == "Message sent"){
         emit passmeg("Message sent");
     }else{
         emit passmeg("Sending failed");
     }

}

QString Handler::getMeg() const
{
    return meg;
}

void Handler::setMeg(const QString &value)
{
    meg = value;
}
