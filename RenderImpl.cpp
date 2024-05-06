#include "RenderImpl.hpp"

namespace sfml {
    RenderImpl::RenderImpl(std::shared_ptr<sf::RenderWindow> window)
        : window(std::move(window)) {}

    void RenderImpl::draw(const Point<double>& topLeft,
                          const Point<double>& bottomRight,
                          const Tile& tile) {
        sf::Sprite sprite = tile.getSprite();
        sprite.setPosition((float)topLeft.x, (float)topLeft.y);
        window->draw(sprite);
    }

    unsigned RenderImpl::getWidthWindow() {
        return window->getSize().x;
    }

    unsigned RenderImpl::getHeightWindow() {
        return window->getSize().y;
    }

    void RenderImpl::clear() {
        window->clear();
    }

    void RenderImpl::display() {
        window->display();
    }
} // namespace sfml
