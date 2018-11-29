#ifndef HANDLER_H
#define HANDLER_H
#include <QString>
#include <QDebug>
#include <QObject>
#include "SmtpClass.h"
class Handler:public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString meg READ getMeg WRITE setMeg NOTIFY passmeg)
public:
    Handler();

    Q_INVOKABLE void datareciever(QString username,QString password,QString recipent,QString subject,QString meg);
    QString getMeg() const;
    void setMeg(const QString &value);

private slots:
    void mailSent(QString);
signals:
    void passmeg(QString);
private:
    SmtpClass *smtp;
    int timeout = 30000;
    QString server;
    QString meg;
    int port;
};

#endif // HANDLER_H
