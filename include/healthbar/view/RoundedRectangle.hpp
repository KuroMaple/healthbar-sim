#pragma once

#include <SFML/Graphics/Shape.hpp>
#include <SFML/System/Vector2.hpp>

#include <cstddef>

namespace healthbar::view {

// A rectangle with rounded corners, built by handing sf::Shape a polygon that
// approximates each corner with an arc of points.
//
// The radius is clamped against the current size on every query, so shrinking
// the shape below twice the radius degrades to a pill and then to a sliver
// rather than turning the geometry inside out.
class RoundedRectangle : public sf::Shape {
public:
    explicit RoundedRectangle(sf::Vector2f size = {0.f, 0.f},
                              float radius = 0.f,
                              std::size_t cornerPointCount = 8);

    void setSize(sf::Vector2f size);
    sf::Vector2f getSize() const;

    void setRadius(float radius);
    float getRadius() const;

    // Points used per corner. Higher is smoother and costs more vertices.
    void setCornerPointCount(std::size_t count);
    std::size_t getCornerPointCount() const;

    std::size_t getPointCount() const override;
    sf::Vector2f getPoint(std::size_t index) const override;

private:
    // The radius actually drawable at the current size.
    float effectiveRadius() const;

    sf::Vector2f m_size;
    float m_radius;
    std::size_t m_cornerPointCount;
};

} // namespace healthbar::view
