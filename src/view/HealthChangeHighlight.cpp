#include <healthbar/view/HealthChangeHighlight.hpp>

#include <algorithm>

namespace healthbar::view {

namespace {
constexpr float kDurationSeconds = 0.35f;
} // namespace

void HealthChangeHighlight::trigger(const float fromFraction, const float toFraction) {
    const Kind incoming = toFraction < fromFraction ? Kind::Damage : Kind::Heal;

    // Same direction while still running: hold the outer edge where it was so the
    // whole burst collapses as one span. Otherwise start fresh.
    if (!isActive() || kind() != incoming) {
        m_fromFraction = fromFraction;
    }
    m_toFraction = toFraction;
    m_remainingSeconds = kDurationSeconds;
}

void HealthChangeHighlight::update(const float deltaSeconds) {
    m_remainingSeconds = std::max(0.f, m_remainingSeconds - deltaSeconds);
}

bool HealthChangeHighlight::isActive() const {
    return m_remainingSeconds > 0.f;
}

HealthChangeHighlight::Kind HealthChangeHighlight::kind() const {
    return m_toFraction < m_fromFraction ? Kind::Damage : Kind::Heal;
}

float HealthChangeHighlight::anchorFraction() const {
    return m_toFraction;
}

float HealthChangeHighlight::movingEdgeFraction() const {
    const float progress = 1.f - m_remainingSeconds / kDurationSeconds;
    return m_fromFraction + (m_toFraction - m_fromFraction) * progress;
}

} // namespace healthbar::view
