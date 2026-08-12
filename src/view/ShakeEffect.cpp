#include <healthbar/view/ShakeEffect.hpp>

#include <algorithm>
#include <cmath>
#include <numbers>

namespace healthbar::view {

namespace {
constexpr float kDurationSeconds = 0.25f;
constexpr float kAmplitudePixels = 8.f;
constexpr float kFrequencyHz = 18.f;
} // namespace

void ShakeEffect::trigger() {
    m_remainingSeconds = kDurationSeconds;
}

void ShakeEffect::update(const float deltaSeconds) {
    m_remainingSeconds = std::max(0.f, m_remainingSeconds - deltaSeconds);
}

bool ShakeEffect::isActive() const {
    return m_remainingSeconds > 0.f;
}

sf::Vector2f ShakeEffect::offset() const {
    if (!isActive()) {
        return {0.f, 0.f};
    }

    // Drive the wave off elapsed rather than remaining time, so the shake always
    // starts at zero displacement instead of snapping away from centre.
    const float elapsed = kDurationSeconds - m_remainingSeconds;
    const float decay = m_remainingSeconds / kDurationSeconds;
    const float phase = 2.f * std::numbers::pi_v<float> * kFrequencyHz * elapsed;

    return {kAmplitudePixels * decay * std::sin(phase), 0.f};
}

} // namespace healthbar::view
