#pragma once

#include <healthbar/model/HealthModel.hpp>

namespace healthbar::viewmodel {

// Adapts the model for presentation. The view pulls from this every frame and
// pushes user intent back through the command methods.
class HealthBarViewModel {
public:
    explicit HealthBarViewModel(model::HealthModel& model);

    void increaseHp();
    void decreaseHp();

    float healthFraction() const;
    int currentHp() const;
    int maxHp() const;

private:
    model::HealthModel& m_model;
};

} // namespace healthbar::viewmodel
