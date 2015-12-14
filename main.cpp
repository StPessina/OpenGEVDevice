#include <QCoreApplication>

#include <stdio.h>
#include <iostream>

#include <QThread>

#include <opengev.h>

#include "OpenNICamera/opennicamera.h"


using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    OpenGEV::configure();

    OpenNICamera myDevice;
    myDevice.start();

    return a.exec();
}
