#include "observer.h"

Observer::Observer(const StreamDataReceiver *channel)
{
    QObject::connect(channel,SIGNAL(newDataAvailable()),
                                               this,SLOT(update()));
}

void Observer::update()
{
    logger.infoStream()<<"UPDATE!!!!!!!!!!!!!!";
}
