#pragma once

#include <SFML/Graphics.hpp>

#include <healthbar/view/RoundedRectangle.hpp>
#include <healthbar/viewmodel/HealthBarViewModel.hpp>

namespace healthbar::view {

// Owns every SFML drawable, polls window events, and hit-tests clicks against
// the buttons it owns. Reads state from the view model fresh each frame.
class HealthBarView {
public:
    explicit HealthBarView(viewmodel::HealthBarViewModel& viewModel);

    void handleEvents(sf::RenderWindow& window);
    void render(sf::RenderWindow& window);

private:
    void onLeftClick(sf::Vector2f position);

    viewmodel::HealthBarViewModel& m_viewModel;

    // Declared before m_hpText: sf::Text holds a reference to its font, so the
    // font has to be constructed first and outlive it.
    sf::Font m_font;
    sf::Text m_hpText;

    RoundedRectangle m_barTrack;
    RoundedRectangle m_barFill;
    sf::CircleShape m_increaseButton;
    sf::CircleShape m_decreaseButton;

    // The + and - glyphs, drawn as plain bars so they need no font.
    sf::RectangleShape m_minusBar;
    sf::RectangleShape m_plusBarHorizontal;
    sf::RectangleShape m_plusBarVertical;
};

} // namespace healthbar::view
