#include <QCoreApplication>

#include <stdio.h>
#include <iostream>

#include <QThread>

#include <opengv.h>

#include "devicewrapper.h"

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    OpenGV::configure();

    DeviceWrapper* myDevice = new DeviceWrapper();
    myDevice->start();

    return a.exec();
}
