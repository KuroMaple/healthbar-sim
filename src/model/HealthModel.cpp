#include <healthbar/model/HealthModel.hpp>

#include <algorithm>

namespace healthbar::model {

HealthModel::HealthModel(const int maxHp, const int step)
    : m_maxHp(maxHp), m_step(step), m_currentHp(maxHp) {}

bool HealthModel::increase() {
    const int previous = m_currentHp;
    m_currentHp = std::min(m_currentHp + m_step, m_maxHp);
    return m_currentHp != previous;
}

bool HealthModel::decrease() {
    const int previous = m_currentHp;
    m_currentHp = std::max(m_currentHp - m_step, 0);
    return m_currentHp != previous;
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
