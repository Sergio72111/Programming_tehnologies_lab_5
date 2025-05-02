#ifndef DRILLFACTORY_H
#define DRILLFACTORY_H

#include "devicefactory.h"

class DrillFactory : public DeviceFactory {
public:
    std::unique_ptr<AbstractElectricDevice> Create() const override;
};

#endif // DRILLFACTORY_H
