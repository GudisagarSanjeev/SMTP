#ifndef EMAILHANDLER_H
#define EMAILHANDLER_H
#include <QDebug>
//#include "SmtpClass.h"
class EmailHandler
{
    Q_OBJECT
public:
    EmailHandler();
     ~EmailHandler();

    Q_INVOKABLE void sendMail(QString,QString,QString,QString,QString,QString,QString);
    void mainSent(QString);
private:
    //SmtpClass *smtp;

};

#endif // EMAILHANDLER_H
