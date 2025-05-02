#ifndef REFRIGERATOR_H
#define REFRIGERATOR_H

#include "electricdevice.h"
#include <string>

class Refrigerator : public AbstractElectricDevice {
private:
    std::string _brand;
    int _capacity;

public:
    Refrigerator(const std::string& name, int power, const std::string& brand, int capacity);
    std::string GetInfo() const override;

    // Методы для редактирования
    void UpdateParameters(int power, const std::string& brand, int capacity);
    std::string GetBrand() const { return _brand; }
    int GetCapacity() const { return _capacity; }
};

#endif // REFRIGERATOR_H
