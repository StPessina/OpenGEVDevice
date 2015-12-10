#include "app.h"

App::App()
{
}

void App::run()
{
    app = new GVApplication();

    app->discoverDevice();

    foreach (PartnerDevice aDevice, app->getDiscoveredDevice()) {
        std::cout<<aDevice.manufactureName.toStdString()<<std::endl;
        std::cout<<aDevice.modelName.toStdString()<<std::endl;
        std::cout<<aDevice.deviceVersion.toStdString()<<std::endl;
        std::cout<<aDevice.macAddress.toStdString()<<std::endl;
        std::cout<<aDevice.ipAddress.toString().toStdString()<<std::endl;
        std::cout<<aDevice.subnetMask.toString().toStdString()<<std::endl;
        std::cout<<aDevice.defaultGateway.toString().toStdString()<<std::endl;
    }

    PartnerDevice pdevice = app->getDiscoveredDevice().at(0);

    pdevice.openControlChannel(5001);

    while(pdevice.openStreamChannel(0)!=GEV_STATUS_SUCCESS) {};

    Observer* obs = new Observer(pdevice.getStreamChannel(0));

    while(true){};

    pdevice.closeControlChannel();

    delete obs;
    delete app;
}
