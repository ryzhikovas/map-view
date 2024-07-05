#include "RenderImpl.hpp"

namespace sfml {
    RenderImpl::RenderImpl(std::shared_ptr<sf::RenderWindow> window)
        : window(std::move(window)) {}

    void RenderImpl::draw(const Point<double>& topLeft,
                          const Point<double>& bottomRight,
                          const Tile& tile) {
        sf::Sprite sprite;
        tile.getSprite(sprite);
        sprite.setPosition((float)topLeft.x, (float)topLeft.y);
        window->draw(sprite);
    }

    void RenderImpl::clear() {
        window->clear();
    }

    void RenderImpl::display() {
        window->display();
    }
} // namespace sfml
