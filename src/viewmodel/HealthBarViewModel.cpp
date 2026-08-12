#include <healthbar/viewmodel/HealthBarViewModel.hpp>

namespace healthbar::viewmodel {

namespace {
// Above healthy is Healthy, above low is Low, everything else is Critical.
constexpr float kHealthyThreshold = 0.55f;
constexpr float kLowThreshold = 0.20f;
} // namespace

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

HealthLevel HealthBarViewModel::healthLevel() const {
    const float fraction = m_model.fraction();
    if (fraction > kHealthyThreshold) {
        return HealthLevel::Healthy;
    }
    if (fraction > kLowThreshold) {
        return HealthLevel::Low;
    }
    return HealthLevel::Critical;
}

int HealthBarViewModel::currentHp() const {
    return m_model.current();
}

int HealthBarViewModel::maxHp() const {
    return m_model.max();
}

} // namespace healthbar::viewmodel
