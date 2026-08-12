#include <healthbar/view/HealthBarView.hpp>

namespace healthbar::view {

namespace {
constexpr float kBarWidth = 400.f;
constexpr float kBarHeight = 40.f;
constexpr float kBarLeft = 100.f;
constexpr float kBarCenterY = 250.f;

constexpr float kButtonRadius = 30.f;
constexpr float kButtonCenterY = 380.f;
constexpr float kDecreaseCenterX = 200.f;
constexpr float kIncreaseCenterX = 400.f;

const sf::Color kButtonColor(50, 110, 220);

// The view owns the palette; the view model only says how healthy things are.
sf::Color fillColorFor(const viewmodel::HealthLevel level) {
    switch (level) {
        case viewmodel::HealthLevel::Healthy:
            return sf::Color(60, 190, 70);
        case viewmodel::HealthLevel::Low:
            return sf::Color(225, 195, 50);
        case viewmodel::HealthLevel::Critical:
            return sf::Color(200, 40, 40);
    }
    return sf::Color::White;
}

// getGlobalBounds() on a circle is its bounding square, which would swallow
// clicks in the corners. Compare squared distance to the radius instead — same
// answer, no square root.
bool circleContains(const sf::CircleShape& circle, const sf::Vector2f point) {
    const sf::Vector2f offset = point - circle.getPosition();
    const float radius = circle.getRadius();
    return offset.x * offset.x + offset.y * offset.y <= radius * radius;
}
} // namespace

HealthBarView::HealthBarView(viewmodel::HealthBarViewModel& viewModel)
    : m_viewModel(viewModel) {
    // Anchor the bar on its left edge, so as HP drops the filled edge recedes
    // leftward and the empty space opens up on the right.
    m_barTrack.setSize({kBarWidth, kBarHeight});
    m_barTrack.setOrigin({0.f, kBarHeight / 2.f});
    m_barTrack.setPosition({kBarLeft, kBarCenterY});
    m_barTrack.setFillColor(sf::Color(60, 60, 60));

    m_barFill.setSize({kBarWidth, kBarHeight});
    m_barFill.setOrigin({0.f, kBarHeight / 2.f});
    m_barFill.setPosition({kBarLeft, kBarCenterY});
    m_barFill.setFillColor(fillColorFor(m_viewModel.healthLevel()));

    // Origin at the circle's centre, so setPosition places the centre directly
    // and the hit test can measure distance from that same point.
    m_decreaseButton.setRadius(kButtonRadius);
    m_decreaseButton.setOrigin({kButtonRadius, kButtonRadius});
    m_decreaseButton.setPosition({kDecreaseCenterX, kButtonCenterY});
    m_decreaseButton.setFillColor(kButtonColor);

    m_increaseButton.setRadius(kButtonRadius);
    m_increaseButton.setOrigin({kButtonRadius, kButtonRadius});
    m_increaseButton.setPosition({kIncreaseCenterX, kButtonCenterY});
    m_increaseButton.setFillColor(kButtonColor);
}

void HealthBarView::handleEvents(sf::RenderWindow& window) {
    while (const std::optional event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window.close();
        } else if (const auto* pressed = event->getIf<sf::Event::MouseButtonPressed>()) {
            if (pressed->button == sf::Mouse::Button::Left) {
                onLeftClick(window.mapPixelToCoords(pressed->position));
            }
        }
    }
}

void HealthBarView::onLeftClick(const sf::Vector2f position) {
    if (circleContains(m_increaseButton, position)) {
        m_viewModel.increaseHp();
    } else if (circleContains(m_decreaseButton, position)) {
        m_viewModel.decreaseHp();
    }
}

void HealthBarView::render(sf::RenderWindow& window) {
    // Both are derived state: recomputed from current HP every frame, so no
    // mutation path can leave them stale.
    m_barFill.setSize({kBarWidth * m_viewModel.healthFraction(), kBarHeight});
    m_barFill.setFillColor(fillColorFor(m_viewModel.healthLevel()));

    window.clear(sf::Color::Black);
    window.draw(m_barTrack);
    window.draw(m_barFill);
    window.draw(m_decreaseButton);
    window.draw(m_increaseButton);
    window.display();
}

} // namespace healthbar::view
