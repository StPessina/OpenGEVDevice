#include "sender.h"

sender::sender(QObject *parent) :
    QObject(parent)
{
}

sender::sender(int a)
{
}

void sender::initSocket()
{
    socket = new QUdpSocket(this);
}
