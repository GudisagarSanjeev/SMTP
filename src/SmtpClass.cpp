#include "SmtpClass.h"

SmtpClass::SmtpClass(const QString &user, const QString &pass, const QString &host, int port, int timeout)
{
    qDebug()<<Q_FUNC_INFO<<endl;

    socket = new QSslSocket(this);

    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(socket, SIGNAL(connected()), this, SLOT(connected() ) );
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this,SLOT(errorReceived(QAbstractSocket::SocketError)));
    connect(socket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(stateChanged(QAbstractSocket::SocketState)));
    connect(socket, SIGNAL(disconnected()), this,SLOT(disconnected()));

    this->user = user;
    this->pass = pass;

    this->host = host;
    this->port = port;
    this->timeout = timeout;
}

SmtpClass::~SmtpClass()
{
    qDebug()<<Q_FUNC_INFO<<endl;
    delete t;
    delete socket;
}
void SmtpClass::sendMail(const QString &from, const QString &to, const QString &subject, const QString &body)
{
    qDebug()<<Q_FUNC_INFO<<endl;
    message = "To: " + to + "\n";
    message.append("From: " + from + "\n");
    message.append("Subject: " + subject + "\n");
    message.append(body);
    message.replace( QString::fromLatin1( "\n" ), QString::fromLatin1( "\r\n" ) );
    message.replace( QString::fromLatin1( "\r\n.\r\n" ),
                     QString::fromLatin1( "\r\n..\r\n" ) );
    this->from = from;
    rcpt = to;
    state = Init;
    socket->connectToHostEncrypted(host, port);
    if (!socket->waitForConnected(timeout)) {
        qDebug() << socket->errorString();
    }

    t = new QTextStream( socket );
}
void SmtpClass::stateChanged(QAbstractSocket::SocketState socketState)
{
    qDebug()<<Q_FUNC_INFO<<endl;
    qDebug() <<"stateChanged " << socketState;
}
void SmtpClass::errorReceived(QAbstractSocket::SocketError socketError)
{
    qDebug()<<Q_FUNC_INFO<<endl;
    qDebug() << "error " <<socketError;
}
void SmtpClass::disconnected()
{
    qDebug()<<Q_FUNC_INFO<<endl;

    qDebug() <<"disconneted";
    qDebug() << "error "  << socket->errorString();
}

void SmtpClass::connected()
{
    qDebug()<<Q_FUNC_INFO<<endl;
    qDebug() << "Connected ";
}

void SmtpClass::readyRead()
{
    qDebug()<<Q_FUNC_INFO<<endl;
    QString responseLine;
    do
    {
        responseLine = socket->readLine();
        response += responseLine;
    }
    while ( socket->canReadLine() && responseLine[3] != ' ' );

    responseLine.truncate( 3 );

    qDebug() << "Server response code:" <<  responseLine;
    qDebug() << "Server response: " << response;

    if ( state == Init && responseLine == "220" )
    {
        *t << "EHLO localhost" <<"\r\n";
        t->flush();

        state = HandShake;
    }
    else if (state == HandShake && responseLine == "250")
    {
        socket->startClientEncryption();
        if(!socket->waitForEncrypted(timeout))
        {
            qDebug() << socket->errorString();
            state = Close;
        }

        *t << "EHLO localhost" << "\r\n";
        t->flush();
        state = Auth;
    }
    else if (state == Auth && responseLine == "250")
    {
        qDebug() << "Authentication";
        *t << "AUTH LOGIN" << "\r\n";
        t->flush();
        state = User;
    }
    else if (state == User && responseLine == "334")
    {
        qDebug() << "Username";
        *t << QByteArray().append(user).toBase64()  << "\r\n";
        t->flush();

        state = Pass;
    }
    else if (state == Pass && responseLine == "334")
    {
        qDebug() << "Password";
        *t << QByteArray().append(pass).toBase64() << "\r\n";
        t->flush();

        state = Mail;
    }
    else if ( state == Mail && responseLine == "235" )
    {
        qDebug() << "Sender:<" << from << ">";
        *t << "MAIL FROM:<" << from << ">\r\n";
        t->flush();
        state = Rcpt;
    }
    else if ( state == Rcpt && responseLine == "250" )
    {
        *t << "RCPT TO:<" << rcpt << ">\r\n"; //r
        t->flush();
        state = Data;
    }
    else if ( state == Data && responseLine == "250" )
    {

        *t << "DATA\r\n";
        t->flush();
        state = Body;
    }
    else if ( state == Body && responseLine == "354" )
    {

        *t << message << "\r\n.\r\n";
        t->flush();
        state = Quit;
    }
    else if ( state == Quit && responseLine == "250" )
    {

        *t << "QUIT\r\n";
        t->flush();
        state = Close;
        emit status( tr( "Message sent" ) );
    }
    else if ( state == Close )
    {
        deleteLater();
        return;
    }
    else
    {
        state = Close;
        emit status( tr( "Sending failed" ) );
    }
    response = "";
}

