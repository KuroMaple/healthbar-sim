#include <healthbar/viewmodel/HealthBarViewModel.hpp>

namespace healthbar::viewmodel {

HealthBarViewModel::HealthBarViewModel(model::HealthModel& model)
    : m_model(model) {}

void HealthBarViewModel::increaseHp() {
    m_model.increase();
}

void HealthBarViewModel::decreaseHp() {
    m_model.decrease();
}

float HealthBarViewModel::healthFraction() const {
    return m_model.fraction();
}

int HealthBarViewModel::currentHp() const {
    return m_model.current();
}

int HealthBarViewModel::maxHp() const {
    return m_model.max();
}

} // namespace healthbar::viewmodel
