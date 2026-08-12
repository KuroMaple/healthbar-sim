#pragma once

#include <SFML/Graphics.hpp>

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

    sf::RectangleShape m_barTrack;
    sf::RectangleShape m_barFill;
    sf::CircleShape m_increaseButton;
    sf::CircleShape m_decreaseButton;
};

} // namespace healthbar::view
