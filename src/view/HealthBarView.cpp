#include <healthbar/view/HealthBarView.hpp>

#include <stdexcept>
#include <string>

namespace healthbar::view {

namespace {
constexpr float kBarWidth = 400.f;
constexpr float kBarHeight = 40.f;
constexpr float kBarLeft = 100.f;
constexpr float kBarCenterY = 250.f;
constexpr float kBarCornerRadius = 12.f;

constexpr float kButtonRadius = 30.f;
constexpr float kButtonCenterY = 380.f;
constexpr float kDecreaseCenterX = 200.f;
constexpr float kIncreaseCenterX = 400.f;

constexpr float kGlyphLength = 26.f;
constexpr float kGlyphThickness = 6.f;

constexpr unsigned int kHpTextSize = 56;
constexpr float kHpTextCenterX = 300.f;
constexpr float kHpTextCenterY = 170.f;

const sf::Color kButtonColor(50, 110, 220);
const sf::Color kButtonPressedColor(30, 70, 150);
const sf::Color kGlyphColor = sf::Color::White;

sf::Font loadFont() {
    sf::Font font;
    const std::string path = std::string(HEALTHBAR_ASSET_DIR) + "/PixelifySans-Regular.ttf";
    if (!font.openFromFile(path)) {
        throw std::runtime_error("failed to open font: " + path);
    }
    return font;
}

// Re-centre after the string changes, since the bounds move with the glyphs.
void centreText(sf::Text& text, const sf::Vector2f position) {
    const sf::FloatRect bounds = text.getLocalBounds();
    text.setOrigin(bounds.position + bounds.size / 2.f);
    text.setPosition(position);
}

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
    : m_viewModel(viewModel),
      m_font(loadFont()),
      m_hpText(m_font, "", kHpTextSize) {
    m_hpText.setFillColor(sf::Color::White);

    // Anchor the bar on its left edge, so as HP drops the filled edge recedes
    // leftward and the empty space opens up on the right.
    m_barTrack.setSize({kBarWidth, kBarHeight});
    m_barTrack.setRadius(kBarCornerRadius);
    m_barTrack.setOrigin({0.f, kBarHeight / 2.f});
    m_barTrack.setPosition({kBarLeft, kBarCenterY});
    m_barTrack.setFillColor(sf::Color(60, 60, 60));

    m_barFill.setSize({kBarWidth, kBarHeight});
    m_barFill.setRadius(kBarCornerRadius);
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

    m_minusBar.setSize({kGlyphLength, kGlyphThickness});
    m_minusBar.setOrigin({kGlyphLength / 2.f, kGlyphThickness / 2.f});
    m_minusBar.setPosition({kDecreaseCenterX, kButtonCenterY});
    m_minusBar.setFillColor(kGlyphColor);

    m_plusBarHorizontal.setSize({kGlyphLength, kGlyphThickness});
    m_plusBarHorizontal.setOrigin({kGlyphLength / 2.f, kGlyphThickness / 2.f});
    m_plusBarHorizontal.setPosition({kIncreaseCenterX, kButtonCenterY});
    m_plusBarHorizontal.setFillColor(kGlyphColor);

    m_plusBarVertical.setSize({kGlyphThickness, kGlyphLength});
    m_plusBarVertical.setOrigin({kGlyphThickness / 2.f, kGlyphLength / 2.f});
    m_plusBarVertical.setPosition({kIncreaseCenterX, kButtonCenterY});
    m_plusBarVertical.setFillColor(kGlyphColor);
}

void HealthBarView::handleEvents(sf::RenderWindow& window) {
    while (const std::optional event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window.close();
        } else if (const auto* pressed = event->getIf<sf::Event::MouseButtonPressed>()) {
            if (pressed->button == sf::Mouse::Button::Left) {
                onLeftClick(window.mapPixelToCoords(pressed->position));
            }
        } else if (const auto* released = event->getIf<sf::Event::MouseButtonReleased>()) {
            // Clear regardless of where the cursor ended up, so dragging off a
            // button can't leave it stuck in the pressed colour.
            if (released->button == sf::Mouse::Button::Left) {
                m_pressedButton = nullptr;
            }
        }
    }
}

void HealthBarView::onLeftClick(const sf::Vector2f position) {
    // The commands report false when the model clamped the change away, which is
    // exactly the "that did nothing" case worth shaking over.
    if (circleContains(m_increaseButton, position)) {
        m_pressedButton = &m_increaseButton;
        if (!m_viewModel.increaseHp()) {
            m_shake.trigger();
        }
    } else if (circleContains(m_decreaseButton, position)) {
        m_pressedButton = &m_decreaseButton;
        if (!m_viewModel.decreaseHp()) {
            m_shake.trigger();
        }
    }
}

void HealthBarView::update(const float deltaSeconds) {
    m_shake.update(deltaSeconds);
}

void HealthBarView::render(sf::RenderWindow& window) {
    // Both are derived state: recomputed from current HP every frame, so no
    // mutation path can leave them stale.
    m_barFill.setSize({kBarWidth * m_viewModel.healthFraction(), kBarHeight});
    m_barFill.setFillColor(fillColorFor(m_viewModel.healthLevel()));

    m_hpText.setString(std::to_string(m_viewModel.currentHp()));
    centreText(m_hpText, {kHpTextCenterX, kHpTextCenterY});

    m_increaseButton.setFillColor(m_pressedButton == &m_increaseButton ? kButtonPressedColor
                                                                      : kButtonColor);
    m_decreaseButton.setFillColor(m_pressedButton == &m_decreaseButton ? kButtonPressedColor
                                                                      : kButtonColor);

    window.clear(sf::Color::Black);

    sf::View shaken = window.getDefaultView();
    shaken.move(m_shake.offset());
    window.setView(shaken);

    window.draw(m_barTrack);
    window.draw(m_barFill);
    window.draw(m_hpText);
    window.draw(m_decreaseButton);
    window.draw(m_increaseButton);
    window.draw(m_minusBar);
    window.draw(m_plusBarHorizontal);
    window.draw(m_plusBarVertical);

    // Restore before the next event poll: mapPixelToCoords uses whatever view is
    // currently set, so leaving the shaken one active would offset hit-testing.
    window.setView(window.getDefaultView());
    window.display();
}

} // namespace healthbar::view
