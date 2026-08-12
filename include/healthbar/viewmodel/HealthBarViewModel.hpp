#pragma once

#include <healthbar/model/HealthModel.hpp>

namespace healthbar::viewmodel {

// How healthy the bar currently reads. Deliberately semantic rather than a
// colour, so the threshold rule stays free of SFML and the view owns the palette.
enum class HealthLevel {
    Critical,
    Low,
    Healthy
};

// Adapts the model for presentation. The view pulls from this every frame and
// pushes user intent back through the command methods.
class HealthBarViewModel {
public:
    explicit HealthBarViewModel(model::HealthModel& model);

    void increaseHp();
    void decreaseHp();

    float healthFraction() const;
    HealthLevel healthLevel() const;
    int currentHp() const;
    int maxHp() const;

private:
    model::HealthModel& m_model;
};

} // namespace healthbar::viewmodel
