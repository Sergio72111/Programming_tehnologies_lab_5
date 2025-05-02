#include "drill.h"

Drill::Drill(const std::string& name, int power, int voltage, int rpm)
    : AbstractElectricDevice(name, power), _voltage(voltage), _rpm(rpm) {}

std::string Drill::GetInfo() const {
    return "Дрель: " + std::to_string(_voltage) + "V" +
           ", Мощность: " + std::to_string(_power) + "W" +
           ", Обороты: " + std::to_string(_rpm) + "RPM" +
           (_isOn ? " (ВКЛ)" : " (ВЫКЛ)");
}

void Drill::UpdateParameters(int power, int voltage, int rpm) {
    _power = power;
    _voltage = voltage;
    _rpm = rpm;
}
