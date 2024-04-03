#include "RenderImpl.hpp"

namespace sfml {
    RenderImpl::RenderImpl(std::shared_ptr<sf::RenderWindow> window)
        : window(std::move(window)) {}

    void RenderImpl::draw(const Point<double>& topLeft,
                          const Point<double>& bottomRight,
                          const TileData& tile) {
        // TODO: реализовать отрисовку. Здесь придется подумать о системах
        //  координат (мировой/экранной)
        const std::vector<char>& dataTile = tile.bytes();
        sf::Uint8* pixels = new sf::Uint8[256 * 256 * 4];
        for (int i = 0; i < 256 * 256; i++) {
            // std::copy(<tile it>, <tile it + 3>, <pixels it>)
            memcpy(&pixels[i * 4], &dataTile[i * 3], sizeof(sf::Uint8) * 3);
            pixels[i * 4 + 3] = 255;
        }

        sf::Texture texture;//создаем объект Texture (текстура)
        texture.create(256,256);
        texture.update(pixels);
        delete[] pixels;

        sprite.setTexture(texture);//передаём в него объект Texture (текстуры)
        sprite.setPosition(topLeft.x, topLeft.y);//задаем начальные координаты появления спрайта

        window->draw(sprite);//выводим спрайт на экран
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
