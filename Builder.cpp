#include "Builder.hpp"
#include "EventsImpl.hpp"
#include "RenderImpl.hpp"
#include "constants.hpp"

namespace sfml {
    Builder::Builder() {
        window = std::make_shared<sf::RenderWindow>(sf::VideoMode{WINDOW_WIDTH, WINDOW_HEIGHT},
                                                    "map-view");
    }

    std::shared_ptr<Events> Builder::events() {
        return std::make_shared<EventsImpl>(window);
    }

    std::shared_ptr<Render> Builder::render() {
        return std::make_shared<RenderImpl>(window);
    }
} // namespace sfml
