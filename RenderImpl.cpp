#include "RenderImpl.hpp"

namespace sfml {
    RenderImpl::RenderImpl(std::shared_ptr<sf::RenderWindow> window)
        : window(std::move(window)) {}

    void RenderImpl::draw(const Point<double>& topLeft,
                          const Point<double>& bottomRight,
                          const TileData& tile) {
        const std::vector<char>& dataTile = tile.bytes();
        int j = 0;
        // TODO заменить на vector
        std::vector<sf::Uint8> pixels(256 * 256 * 4);
        for (int i = 0; i < 256 * 256 * 4; i += 4, j += 3) {
            std::copy(&dataTile[j], &dataTile[j + 3], &pixels[i]);
            pixels[i + 3] = 255;
        }

        // TODO создать кеш текстур
        sf::Texture texture;
        texture.create(256,256);
        texture.update(pixels.data());

        sprite.setTexture(texture);
        sprite.setPosition((float)topLeft.x, (float)topLeft.y);

        window->draw(sprite);
    }

    unsigned RenderImpl::getWidthWindow(){
        return window->getSize().x;
    }

    unsigned RenderImpl::getHeightWindow(){
        return window->getSize().y;
    }

    void RenderImpl::clear() {
        window->clear();
    }

    void RenderImpl::display() {
        window->display();
    }
} // namespace sfml
