#ifndef SMTPCLASS_H
#define SMTPCLASS_H
#include <QDebug>
#include <QObject>
#include <QAbstractSocket>
#include <QSslSocket>
#include <QTextStream>
#include <QByteArray>
class SmtpClass: public QObject
{
    Q_OBJECT
public:
    SmtpClass( const QString &user, const QString &pass,
               const QString &host, int port, int timeout);
    ~SmtpClass();
    void sendMail(const QString &from, const QString &to,
                  const QString &subject, const QString &body);

private slots:
    void stateChanged(QAbstractSocket::SocketState socketState);
    void errorReceived(QAbstractSocket::SocketError socketError);
    void disconnected();
    void connected();
    void readyRead();
signals:
    void status(const QString);
private:
    QString message;

    QTextStream *t;
    QSslSocket *socket;

    QString from;
    QString rcpt;
    QString response;
    QString user;
    QString pass;
    QString host;

    int port;
    int state;
    int timeout;

    QString meg;

    enum states{Tls, HandShake ,Auth,User,Pass,Rcpt,Mail,Data,Init,Body,Quit,Close};

};

#endif // SMTPCLASS_H
