#include <healthbar/view/HealthBarView.hpp>

namespace healthbar::view {

namespace {
constexpr float kBarWidth = 400.f;
constexpr float kBarHeight = 40.f;
constexpr float kBarLeft = 100.f;
constexpr float kBarCenterY = 250.f;

constexpr float kButtonSize = 60.f;
constexpr float kButtonCenterY = 380.f;
constexpr float kDecreaseCenterX = 200.f;
constexpr float kIncreaseCenterX = 400.f;
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
    m_barFill.setFillColor(sf::Color(200, 40, 40));

    m_decreaseButton.setSize({kButtonSize, kButtonSize});
    m_decreaseButton.setOrigin({kButtonSize / 2.f, kButtonSize / 2.f});
    m_decreaseButton.setPosition({kDecreaseCenterX, kButtonCenterY});
    m_decreaseButton.setFillColor(sf::Color(120, 30, 30));

    m_increaseButton.setSize({kButtonSize, kButtonSize});
    m_increaseButton.setOrigin({kButtonSize / 2.f, kButtonSize / 2.f});
    m_increaseButton.setPosition({kIncreaseCenterX, kButtonCenterY});
    m_increaseButton.setFillColor(sf::Color(30, 120, 30));
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
    if (m_increaseButton.getGlobalBounds().contains(position)) {
        m_viewModel.increaseHp();
    } else if (m_decreaseButton.getGlobalBounds().contains(position)) {
        m_viewModel.decreaseHp();
    }
}

void HealthBarView::render(sf::RenderWindow& window) {
    m_barFill.setSize({kBarWidth * m_viewModel.healthFraction(), kBarHeight});

    window.clear(sf::Color::Black);
    window.draw(m_barTrack);
    window.draw(m_barFill);
    window.draw(m_decreaseButton);
    window.draw(m_increaseButton);
    window.display();
}

} // namespace healthbar::view
