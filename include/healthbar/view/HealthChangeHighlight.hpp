#pragma once

namespace healthbar::view {

// A fading highlight over the segment of the bar that just changed.
//
// Damage and heal are the same animation with the colour and draw order swapped:
// one edge sits fixed at the new health fraction while the other interpolates
// linearly from the old fraction to the new one, closing the gap to nothing.
class HealthChangeHighlight {
public:
    enum class Kind {
        Damage,
        Heal
    };

    // Repeated steps in the same direction accumulate: the moving edge keeps the
    // start it already had, so a burst of clicks reads as one larger change
    // rather than a flicker of small ones.
    void trigger(float fromFraction, float toFraction);

    void update(float deltaSeconds);
    bool isActive() const;

    Kind kind() const;

    // The edge pinned at the new health fraction.
    float anchorFraction() const;

    // The edge travelling from the old fraction towards the anchor.
    float movingEdgeFraction() const;

private:
    float m_fromFraction = 0.f;
    float m_toFraction = 0.f;
    float m_remainingSeconds = 0.f;
};

} // namespace healthbar::view
