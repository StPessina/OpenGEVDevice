#ifndef DEVICEWRAPPER_H
#define DEVICEWRAPPER_H

#include <QThread>

#include <string>

#include <opengev.h>

#include <Application/gvapplication.h>

#include <Device/gvdevice.h>
#include <DeviceCommandHandler/devicecommandhandlerfactory.h>

#include "CommonStream/streamrawdataleader.h"
#include "CommonStream/streamrawdatapayload.h"
#include "CommonStream/streamrawdatatrailer.h"

#include "iostream"

#include "observer.h"

#include <stdio.h>

#include <chrono>

#include <OpenNI.h>

#define SIZE_X 640
#define SIZE_Y 480

class DeviceWrapper : public QThread
{
    Q_OBJECT
public:
    DeviceWrapper();

    std::string a = "MAN_NAME";
    std::string b = "MODEL_NAME";
    std::string c = "DEVICE_VERSION";


    GVDevice* device;

    log4cpp::Category &logger = log4cpp::Category::getInstance("ComponentLog");

    //long* historyValue = new long[10];
    long sumTotal = 0;
    long sumAcquireFrame = 0;
    long sumSendData = 0;

    long iteration = 0;


    bool singleShoot = false;

    PixelMap::Ptr depthMap;

    PixelMap::Ptr RGBMap;

    PixelMap::Ptr DepthRGBMap;


    openni::Device device_;
    openni::VideoStream ir_;
    openni::VideoStream color_;
    openni::Status rc_;
    openni::VideoFrameRef irf_;
    openni::VideoFrameRef colorf_;

protected:
    void run();

signals:
    void initialization();

public slots:
    void setupTimer();

    void readDataFromCam();

    void sendDepthDataStream();

    void sendRgbDataStream();

    void sendDepthRgbDataStream();

};

#endif // DEVICEWRAPPER_H
