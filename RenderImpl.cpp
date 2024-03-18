#include "RenderImpl.hpp"
namespace sfml {
    RenderImpl::RenderImpl(std::shared_ptr<sf::RenderWindow> window)
        : window(std::move(window)) {}

    void RenderImpl::draw(const Point<double>& topLeft,
                          const Point<double>& bottomRight,
                          const TileData& tile) {
        // TODO: реализовать отрисовку. Здесь придется подумать о системах
        //  координат (мировой/экранной)
    }

    void RenderImpl::clear() {
        window->clear();
    }

    void RenderImpl::display() {
        window->display();
    }
} // namespace sfml
