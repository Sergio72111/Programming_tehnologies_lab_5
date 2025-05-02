#ifndef ELECTRICDEVICE_H
#define ELECTRICDEVICE_H

#include <string>

class AbstractElectricDevice {
protected:
    std::string _name;
    int _power;
    bool _isOn = false;

public:
    AbstractElectricDevice(const std::string& name, int power);
    virtual ~AbstractElectricDevice() = default;

    virtual void TurnOn() { _isOn = true; }
    virtual void TurnOff() { _isOn = false; }
    virtual int GetPower() const { return _isOn ? _power : 0; }
    virtual std::string GetInfo() const = 0;
    bool IsOn() const { return _isOn; } // Добавлен метод IsOn()

    virtual void UpdatePower(int power) { _power = std::max(0, power); }
    int GetBasePower() const { return _power; }
};

#endif // ELECTRICDEVICE_H
