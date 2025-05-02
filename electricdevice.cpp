#include "electricdevice.h"

AbstractElectricDevice::AbstractElectricDevice(const std::string& name, int power)
    : _name(name), _power(power) {} // _isOn инициализируется в классе как false
