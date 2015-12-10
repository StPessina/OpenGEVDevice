#ifndef APP_H
#define APP_H

#include <QObject>

#include <string>

#include <opengv.h>

#include <Application/gvapplication.h>

#include <Device/gvdevice.h>
#include <DeviceCommandHandler/devicecommandhandlerfactory.h>
#include <CommonUdpChannel/udpchannelreceiver.h>

#include "CommonStream/streamrawdataleader.h"
#include "CommonStream/streamrawdatapayload.h"
#include "CommonStream/streamrawdatatrailer.h"

#include "CommonStreamImageFormat/mono16.h"

#include "iostream"

#include "observer.h"

class App : public QObject
{
    Q_OBJECT
public:
    App();

    std::string a = "MAN_NAME";
    std::string b = "MODEL_NAME";
    std::string c = "DEVICE_VERSION";


    GVApplication* app;

public slots:
    void run();
};

#endif // APP_H
