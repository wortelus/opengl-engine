// Creator: Daniel Slavík
// E-Mail: sla0331@vsb.cz
// Date of Creation:  3/11/2023

#include <stdexcept>
#include "light.h"

LIGHT_ID Light::getManagedId() const {
    if (this->managed_id == -1)
        throw std::runtime_error("Light has not been assigned a managed id");
    return this->managed_id;
}
