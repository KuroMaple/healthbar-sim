#include <healthbar/view/HealthChangeHighlight.hpp>

#include <algorithm>

namespace healthbar::view {

namespace {
constexpr float kDurationSeconds = 0.35f;
} // namespace

void HealthChangeHighlight::trigger(const float fromFraction, const float toFraction) {
    const Kind incoming = toFraction < fromFraction ? Kind::Damage : Kind::Heal;

    // Same direction while still running: pick up from where the edge actually is
    // rather than where the span began, so the travel already done isn't thrown
    // away. Resetting the timer sends progress back to 0, and progress 0 means
    // "at m_fromFraction" — so m_fromFraction has to move to match or the edge
    // snaps back outward on every click.
    //
    // Read the old state before overwriting any of it: both helpers below depend
    // on all three members.
    const bool continuing = isActive() && kind() == incoming;
    const float newFrom = continuing ? movingEdgeFraction() : fromFraction;

    m_fromFraction = newFrom;
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
