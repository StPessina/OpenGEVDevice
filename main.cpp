//#define ENABLE_KINECT 0

#include <QCoreApplication>

#include <stdio.h>
#include <iostream>
#include <signal.h>

#include <QThread>

#include <opengev.h>

#include "devicewrapper.h"
#include "OpenNICamera/opennicamera.h"

#include "Kinect/kinectv2camera.h"

KinectV2Camera *kinect;

/*
 * Check signal interrupt because stop starded kinect
 * device can freeze operative system
 *
*/
void sigint_handler(int s)
{
  std::cout<<"quit signal called"<<std::endl;
  kinect->quit();
}

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    OpenGEV::configure();

    if(argc>1) {
        char* p;
        int device = strtol(argv[1], &p, 10);

        if(device==1) {
            OpenNICamera asus;
            asus.start();
            return a.exec();
        }
        if(device==2) {
            kinect = new KinectV2Camera;
            kinect->start();
            //Correctly shutdown device on signal interrupt on console
            signal(SIGINT,sigint_handler);
            return a.exec();
        }
        if(device==3) {
            DeviceWrapper w;
            w.start();
            return a.exec();
        }

        if(device<=0 || device >3)
            std::cout<<"No valid device selected"<<std::endl;
    } else {
        std::cout<<"No valid device selected"<<std::endl;
    }
    return -1;
}
