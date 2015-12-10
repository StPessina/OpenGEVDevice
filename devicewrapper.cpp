#include "devicewrapper.h"

DeviceWrapper::DeviceWrapper()
{
    device = new GVDevice("MAN_NAME","MODEL_NAME","DEVICE_VERSION");

    device->createStreamChannel();
    device->createStreamChannel();
    device->createStreamChannel();

    connect(this,SIGNAL(initialization()),this,SLOT(setupTimer()));

    //value = (char*) malloc(2*sizeof(char));

    depthMap = new PixelMap(GVSP_PIX_MONO16, 320,240,0,0,0,0);
    RGBMap = new PixelMap(GVSP_PIX_RGB8, 320,240,0,0,0,0);
    DepthRGBMap = new PixelMap(GVSP_PIX_MONO16_RGB8, 320,240,0,0,0,0);

    openni::OpenNI::initialize ();
    //const char *cstr = file_name.c_str();
    device_.open(openni::ANY_DEVICE);
    ir_.create (device_, openni::SENSOR_DEPTH);
    ir_.start ();
    device_.setImageRegistrationMode (openni::IMAGE_REGISTRATION_DEPTH_TO_COLOR);
    color_.create (device_, openni::SENSOR_COLOR);
    color_.start();


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
    if(iteration<4294967296 &&
            sumTotal<4294967296 &&
            sumAcquireFrame<4294967296 &&
            sumSendData<4294967296)
        iteration++;
    else {
        iteration=1;
        sumTotal=0;
        sumAcquireFrame=0;
        sumSendData=0;
    }

    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();

    ir_.readFrame (&irf_);
    color_.readFrame (&colorf_);

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

    depthMap->data = (char*) irf_.getData();
    depthMap->sizex = irf_.getWidth();
    depthMap->sizey = irf_.getHeight();

    device->getStreamChannel(0)->writeIncomingData(*depthMap);
}

void DeviceWrapper::sendRgbDataStream()
{
    if(!device->getStreamChannel(1)->isChannelOpen())
        return;

    RGBMap->data = (char*) colorf_.getData();
    RGBMap->sizex = colorf_.getWidth();
    RGBMap->sizey = colorf_.getHeight();

    device->getStreamChannel(1)->writeIncomingData(*RGBMap);
}

void DeviceWrapper::sendDepthRgbDataStream()
{
    if(!device->getStreamChannel(2)->isChannelOpen())
        return;

    char* depthData = (char*) irf_.getData();
    char* rgbData = (char*) colorf_.getData();

    int depth_idx = 0;
    int rgb_idx = 0;
    int char_idx = 0;
    for (int v = 0; v < DepthRGBMap->sizey; ++v)
    {
        for (int u = 0; u < DepthRGBMap->sizex; ++u, depth_idx+=2, rgb_idx+=3, char_idx+=5)
        {
            DepthRGBMap->data[char_idx] = depthData[depth_idx];
            DepthRGBMap->data[char_idx+1] = depthData[depth_idx+1];

            DepthRGBMap->data[char_idx+2] = rgbData[rgb_idx];
            DepthRGBMap->data[char_idx+3] = rgbData[rgb_idx+1];
            DepthRGBMap->data[char_idx+4] = rgbData[rgb_idx+2];
        }
    }

    device->getStreamChannel(2)->writeIncomingData(*DepthRGBMap);
}

void DeviceWrapper::run()
{
    emit initialization();

    exec();
}
