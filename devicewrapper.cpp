#include "devicewrapper.h"

DeviceWrapper::DeviceWrapper(int sizex, int sizey)
{
    device = new GVDevice("WRAPPER_DEVICE","WRAPPER_DEVICE","DEVICE_VERSION");

    device->createStreamChannel();
    device->createStreamChannel();
    device->createStreamChannel();

    connect(this,SIGNAL(initialization()),this,SLOT(setupTimer()));

    depthMap = new PixelMap(GVSP_PIX_MONO16, sizex,sizey,0,0,0,0);
    RGBMap = new PixelMap(GVSP_PIX_RGB8, sizex,sizey,0,0,0,0);
    DepthRGBMap = new PixelMap(GVSP_PIX_MONO16_RGB8, sizex,sizey,0,0,0,0);

    for (int var = 0; var < sizex*sizey*2; var+=2) {
        depthMap->data[var] = 0x0;
        depthMap->data[var] = 0xF;
    }


    for (int var = 0; var < sizex*sizey*3; var+=2) {
        RGBMap->data[var] = 0x0;
        RGBMap->data[var] = 0xF;
    }


    for (int var = 0; var < sizex*sizey*5; var+=2) {
        DepthRGBMap->data[var] = 0x0;
        DepthRGBMap->data[var] = 0xF;
    }
}

void DeviceWrapper::setupTimer()
{
    QTimer* readFromCamTimer = new QTimer(this);
    connect(readFromCamTimer,SIGNAL(timeout()),this,SLOT(readDataFromCam()));
    readFromCamTimer->start(30);

    /*
    QTimer* sendDepthDataTimer = new QTimer(this);
    connect(sendDepthDataTimer,SIGNAL(timeout()),this,SLOT(sendDepthDataStream()));
    sendDepthDataTimer->start(30);

    QTimer* sendRgbDataTimer = new QTimer(this);
    connect(sendRgbDataTimer,SIGNAL(timeout()),this,SLOT(sendRgbDataStream()));
    sendRgbDataTimer->start(30);

    QTimer* sendDepthRgbDataTimer = new QTimer(this);
    connect(sendDepthRgbDataTimer,SIGNAL(timeout()),this,SLOT(sendDepthRgbDataStream()));
    sendDepthRgbDataTimer->start(30);
    */
}

void DeviceWrapper::readDataFromCam()
{
    if(iteration<100)
        iteration++;
    else {
        sumTotal/=iteration;
        sumAcquireFrame/=iteration;
        sumSendData/=iteration;
        iteration=1;
    }

    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    long acquireFrame = std::chrono::duration_cast<std::chrono::microseconds>(end- start).count();

    start = std::chrono::steady_clock::now();

    sendDepthDataStream();
    sendRgbDataStream();
    sendDepthRgbDataStream();

    end = std::chrono::steady_clock::now();
    long sendData = std::chrono::duration_cast<std::chrono::microseconds>(end- start).count();

    long value = acquireFrame+sendData;

    sumTotal+=value;
    sumAcquireFrame+=acquireFrame;
    sumSendData+=sendData;

    std::cout << "Send value time "
              << value
              << "us. (average: "<<sumTotal/iteration<<" us"
              <<" - Acquire frame: "<<sumAcquireFrame/iteration<<" us"
             <<" - Send data: "<<sumSendData/iteration<<" us"
            <<" )\n";
}

void DeviceWrapper::sendDepthDataStream()
{
    if(!device->getStreamChannel(0)->isChannelOpen())
        return;

    device->getStreamChannel(0)->writeIncomingData(*depthMap);
}

void DeviceWrapper::sendRgbDataStream()
{
    if(!device->getStreamChannel(1)->isChannelOpen())
        return;

    device->getStreamChannel(1)->writeIncomingData(*RGBMap);
}

void DeviceWrapper::sendDepthRgbDataStream()
{
    if(!device->getStreamChannel(2)->isChannelOpen())
        return;

    device->getStreamChannel(2)->writeIncomingData(*DepthRGBMap);
}

void DeviceWrapper::run()
{
    emit initialization();

    exec();
}
