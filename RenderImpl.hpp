#pragma once
#include "Render.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <cstring>
#include <cstdlib>
#include <memory>

namespace sfml {
    class RenderImpl : public Render {
      public:
        RenderImpl(std::shared_ptr<sf::RenderWindow> window);
        unsigned getWidthWindow() override;
        unsigned getHeightWindow() override;
        void clear() override;
        void display() override;
        void draw(const Point<double>& topLeft,
                  const Point<double>& bottomRight,
                  const TileData& tile) override;

      private:
        std::shared_ptr<sf::RenderWindow> window;
        sf::Sprite sprite;
    };
} // namespace sfml
