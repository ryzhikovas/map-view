#include "RenderImpl.hpp"

namespace sfml {
    RenderImpl::RenderImpl(std::shared_ptr<sf::RenderWindow> window)
        : window(std::move(window)) {}

    void RenderImpl::draw(const Point<double>& topLeft,
                          const Point<double>& bottomRight,
                          const TileData& tile) {
        const std::vector<char>& dataTile = tile.bytes();
        int j = 0;
        unsigned size = MAP_SIZE * MAP_SIZE * 4;
        std::vector<sf::Uint8> pixels(size);
        for (unsigned i = 0; i < size; i += 4, j += 3) {
            std::copy(&dataTile[j], &dataTile[j + 3], &pixels[i]);
            pixels[i + 3] = 255;
        }

        // TODO создать кеш текстур
        sf::Texture texture;
        texture.create(MAP_SIZE,MAP_SIZE);
        texture.update(pixels.data());

        sf::Sprite sprite;
        sprite.setTexture(texture, true);
        sprite.setPosition((float)topLeft.x, (float)topLeft.y);

        window->draw(sprite);
    }

    bool RenderImpl::getTile(const TileData& id) {
        // TODO Поиск заданного спрайта (возможно создать отдельный класс)
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
