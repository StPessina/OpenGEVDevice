#ifndef RECEIVER_H
#define RECEIVER_H

#include <QObject>

#include <QCoreApplication>

#include <QUdpSocket>
#include <QHostAddress>

#include <iostream>

class receiver : public QObject
{
    Q_OBJECT
public:
    //receiver();
    explicit receiver(QObject *parent = 0);
    receiver(char *abc, char *cdf);

    void initSocket();

    void doNothing();



    QHostAddress sourceAddr;

    quint16 sourcePort;

    QUdpSocket* socket;

public slots:
    void read();

    void run();

};

#endif // RECEIVER_H
