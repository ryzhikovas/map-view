#include "Builder.hpp"
#include "EventsImpl.hpp"
#include "RenderImpl.hpp"

namespace sfml {
    Builder::Builder() {
        window = std::make_shared<sf::RenderWindow>(sf::VideoMode{1280u, 960u},
                                                    "map-view");
    }

    std::shared_ptr<Events> Builder::events() {
        return std::make_shared<EventsImpl>(window);
    }

    std::shared_ptr<Render> Builder::render() {
        return std::make_shared<RenderImpl>(window);
    }
} // namespace sfml
