#ifndef REFRIGERATORFACTORY_H
#define REFRIGERATORFACTORY_H

#include "devicefactory.h"

class RefrigeratorFactory : public DeviceFactory {
public:
    std::unique_ptr<AbstractElectricDevice> Create() const override;
};

#endif // REFRIGERATORFACTORY_H
