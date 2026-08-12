#pragma once

namespace healthbar::model {

// Owns the health state and the rules that keep it valid. Knows nothing about
// SFML or how the bar is drawn.
class HealthModel {
public:
    HealthModel(int maxHp, int step);

    void increase();
    void decrease();

    int current() const;
    int max() const;

    // Current health as 0.0 .. 1.0, for sizing the bar.
    float fraction() const;

private:
    int m_maxHp;
    int m_step;
    int m_currentHp;
};

} // namespace healthbar::model
