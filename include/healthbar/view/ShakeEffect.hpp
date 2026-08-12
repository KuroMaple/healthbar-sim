#pragma once

#include <SFML/System/Vector2.hpp>

namespace healthbar::view {

// A decaying horizontal camera shake. Deterministic — the offset is a sine wave
// whose amplitude falls linearly to zero, so no random source is involved and the
// whole thing can be stepped with a fake delta in a test.
class ShakeEffect {
public:
    // Restart at full amplitude, whether or not a shake is already running.
    void trigger();

    void update(float deltaSeconds);

    // Zero once the shake has decayed, so it can be applied unconditionally.
    sf::Vector2f offset() const;

    bool isActive() const;

private:
    float m_remainingSeconds = 0.f;
};

} // namespace healthbar::view
