#include "devicemanager.h"
#include "ilogger.h"
#include "electricdevice.h"
#include <numeric> // Для std::accumulate

DeviceManager::DeviceManager(std::shared_ptr<ILogger> logger)
    : _logger(logger) {}

void DeviceManager::AddDevice(std::unique_ptr<AbstractElectricDevice> device) {
    if (device) {
        _logger->Log("[+] Добавлено устройство: " + device->GetInfo());
        _devices.push_back(std::move(device));
    }
}

void DeviceManager::RemoveDevice(int index) {
    if (index >= 0 && index < static_cast<int>(_devices.size())) {
        _logger->Log("[-] Удалено устройство: " + _devices[index]->GetInfo());
        _devices.erase(_devices.begin() + index);
    }
}

void DeviceManager::TurnOnAll() {
    for (auto& device : _devices) {
        device->TurnOn();
        _logger->Log("[⚡] Включено: " + device->GetInfo());
    }
}

int DeviceManager::GetTotalPower() const {
    return std::accumulate(
        _devices.begin(),
        _devices.end(),
        0,
        [](int total, const auto& device) {
            return total + device->GetPower();
        }
        );
}

const std::vector<std::unique_ptr<AbstractElectricDevice>>&
DeviceManager::GetDevices() const {
    return _devices;
}
