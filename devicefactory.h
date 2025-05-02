#ifndef DEVICEFACTORY_H
#define DEVICEFACTORY_H

#include <memory>
#include "electricdevice.h"

class DeviceFactory {
public:
    virtual std::unique_ptr<AbstractElectricDevice> Create() const = 0;
    virtual ~DeviceFactory() = default;
};

#endif
