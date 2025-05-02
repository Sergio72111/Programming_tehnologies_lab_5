#include "refrigerator.h"

Refrigerator::Refrigerator(const std::string& name, int power,
                           const std::string& brand, int capacity)
    : AbstractElectricDevice(name, std::max(0, power)),
    _brand(brand),
    _capacity(std::max(0, capacity)) {}

std::string Refrigerator::GetInfo() const {
    return "Холодильник: " + _brand +
           ", Мощность: " + std::to_string(_power) + "W" +
           ", Объем: " + std::to_string(_capacity) + "л" +
           (_isOn ? " (ВКЛ)" : " (ВЫКЛ)");
}

void Refrigerator::UpdateParameters(int power, const std::string& brand, int capacity) {
    _power = std::max(0, power);
    _brand = brand;
    _capacity = std::max(0, capacity);
}
