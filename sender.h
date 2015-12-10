#ifndef SENDER_H
#define SENDER_H

#include <QObject>

#include <QUdpSocket>
#include <QHostAddress>


class sender : public QObject
{
    Q_OBJECT
public:
    explicit sender(QObject *parent = 0);
    sender(int a);

    void initSocket();


    QUdpSocket* socket;

};

#endif // SENDER_H
