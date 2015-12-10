#ifndef OBSERVER_H
#define OBSERVER_H

#include <QObject>

#include <log4cpp/Category.hh>

#include "Application/streamdatareceiver.h"

class Observer : public QObject
{
    Q_OBJECT
public:
    explicit Observer(QObject* parent = 0);

    Observer(const StreamDataReceiver* channel);

public slots:
    void update();

private:
    log4cpp::Category &logger = log4cpp::Category::getInstance("ComponentLog");
};

#endif // OBSERVER_H
