#include <healthbar/view/RoundedRectangle.hpp>

#include <algorithm>
#include <cmath>
#include <numbers>

namespace healthbar::view {

namespace {
constexpr float kDegreesPerCorner = 90.f;

float toRadians(const float degrees) {
    return degrees * std::numbers::pi_v<float> / 180.f;
}
} // namespace

RoundedRectangle::RoundedRectangle(const sf::Vector2f size,
                                   const float radius,
                                   const std::size_t cornerPointCount)
    : m_size(size),
      m_radius(radius),
      m_cornerPointCount(std::max<std::size_t>(cornerPointCount, 1)) {
    update();
}

void RoundedRectangle::setSize(const sf::Vector2f size) {
    m_size = size;
    update();
}

sf::Vector2f RoundedRectangle::getSize() const {
    return m_size;
}

void RoundedRectangle::setRadius(const float radius) {
    m_radius = radius;
    update();
}

float RoundedRectangle::getRadius() const {
    return m_radius;
}

void RoundedRectangle::setCornerPointCount(const std::size_t count) {
    m_cornerPointCount = std::max<std::size_t>(count, 1);
    update();
}

std::size_t RoundedRectangle::getCornerPointCount() const {
    return m_cornerPointCount;
}

std::size_t RoundedRectangle::getPointCount() const {
    return m_cornerPointCount * 4;
}

float RoundedRectangle::effectiveRadius() const {
    // A corner can never eat more than half of either dimension.
    return std::max(0.f, std::min({m_radius, m_size.x / 2.f, m_size.y / 2.f}));
}

sf::Vector2f RoundedRectangle::getPoint(const std::size_t index) const {
    const float radius = effectiveRadius();
    const std::size_t corner = index / m_cornerPointCount;
    const std::size_t pointInCorner = index % m_cornerPointCount;

    // Sweep evenly from 0 to 90 degrees across the corner, inclusive at both
    // ends. With a single point per corner this collapses to a sharp corner.
    const float progress =
            m_cornerPointCount == 1
                    ? 0.f
                    : static_cast<float>(pointInCorner) / static_cast<float>(m_cornerPointCount - 1);

    // Corners run clockwise on screen (y grows downward) starting top-left.
    float angle = progress * kDegreesPerCorner;
    sf::Vector2f centre;
    switch (corner) {
        case 0: // top-left: left edge round to top edge
            centre = {radius, radius};
            angle += 180.f;
            break;
        case 1: // top-right
            centre = {m_size.x - radius, radius};
            angle += 270.f;
            break;
        case 2: // bottom-right
            centre = {m_size.x - radius, m_size.y - radius};
            break;
        default: // bottom-left
            centre = {radius, m_size.y - radius};
            angle += 90.f;
            break;
    }

    const float radians = toRadians(angle);
    return centre + sf::Vector2f{std::cos(radians) * radius, std::sin(radians) * radius};
}

} // namespace healthbar::view
