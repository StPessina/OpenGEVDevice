#include "receiver.h"

receiver::receiver(QObject *parent) :
    QObject(parent)
{
}

receiver::receiver(char *abc, char *cdf)
{
}

void receiver::initSocket()
{
    socket = new QUdpSocket(this);
    socket->bind(QHostAddress::Any, 3956);

    std::cout<<socket->BoundState<<std::endl;

    connect(socket, SIGNAL(readyRead()),
            this, SLOT(read()));

    std::cout<<"connected"<<std::endl;
    read();
    std::cout<<"readed"<<std::endl;

    socket->dumpObjectInfo();
    //this-dumpObjectTree();
}

void receiver::doNothing()
{

}

void receiver::run()
{
    initSocket();
}

void receiver::read()
{
    while(socket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(socket->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;

        socket->readDatagram(datagram.data(), datagram.size(),
                            &sender, &senderPort);

        std::cout<<"Pending datagram: "<<datagram.data()<<std::endl;
    }
}
