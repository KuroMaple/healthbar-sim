#include <healthbar/model/HealthModel.hpp>

#include <algorithm>

namespace healthbar::model {

HealthModel::HealthModel(const int maxHp, const int step)
    : m_maxHp(maxHp), m_step(step), m_currentHp(maxHp) {}

void HealthModel::increase() {
    m_currentHp = std::min(m_currentHp + m_step, m_maxHp);
}

void HealthModel::decrease() {
    m_currentHp = std::max(m_currentHp - m_step, 0);
}

int HealthModel::current() const {
    return m_currentHp;
}

int HealthModel::max() const {
    return m_maxHp;
}

float HealthModel::fraction() const {
    return static_cast<float>(m_currentHp) / static_cast<float>(m_maxHp);
}

} // namespace healthbar::model
