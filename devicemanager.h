#ifndef DEVICEMANAGER_H
#define DEVICEMANAGER_H

#include <vector>
#include <memory>
#include "electricdevice.h"
#include "ilogger.h"

class DeviceManager {
private:
    std::vector<std::unique_ptr<AbstractElectricDevice>> _devices;
    std::shared_ptr<ILogger> _logger;

public:
    explicit DeviceManager(std::shared_ptr<ILogger> logger);
    void AddDevice(std::unique_ptr<AbstractElectricDevice> device);
    void RemoveDevice(int index);
    void TurnOnAll();
    int GetTotalPower() const;
    const std::vector<std::unique_ptr<AbstractElectricDevice>>& GetDevices() const; // Объявление метода
};

#endif // DEVICEMANAGER_H
