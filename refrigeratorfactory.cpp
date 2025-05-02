#include "refrigeratorfactory.h"
#include "refrigerator.h"
#include <memory>

std::unique_ptr<AbstractElectricDevice> RefrigeratorFactory::Create() const {
    return std::make_unique<Refrigerator>(
        "Samsung Fridge",
        150,
        "Samsung",
        300
        );
}
