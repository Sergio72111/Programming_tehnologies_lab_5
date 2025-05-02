#include "drillfactory.h"
#include "drill.h"
#include <memory>

std::unique_ptr<AbstractElectricDevice> DrillFactory::Create() const {
    return std::make_unique<Drill>(
        "Bosch Drill",
        800,
        220,
        3000
        );
}
