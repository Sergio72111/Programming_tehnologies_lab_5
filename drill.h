#ifndef DRILL_H
#define DRILL_H

#include "electricdevice.h"

class Drill : public AbstractElectricDevice {
private:
    int _voltage;
    int _rpm;

public:
    Drill(const std::string& name, int power, int voltage, int rpm);
    std::string GetInfo() const override;

    // Методы для редактирования
    void UpdateParameters(int power, int voltage, int rpm);
    int GetVoltage() const { return _voltage; }
    int GetRPM() const { return _rpm; }
};

#endif // DRILL_H
