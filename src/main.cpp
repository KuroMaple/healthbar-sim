#include <SFML/Graphics.hpp>

#include <healthbar/model/HealthModel.hpp>
#include <healthbar/view/HealthBarView.hpp>
#include <healthbar/viewmodel/HealthBarViewModel.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode({600, 500}), "Health Bar Simulator");
    window.setFramerateLimit(60);

    // Composition root: main owns every layer, each one borrows the one below it.
    // Declaration order is what guarantees the references stay valid.
    healthbar::model::HealthModel model(100, 10);
    healthbar::viewmodel::HealthBarViewModel viewModel(model);
    healthbar::view::HealthBarView view(viewModel);

    while (window.isOpen()) {
        view.handleEvents(window);
        view.render(window);
    }

    return 0;
}
