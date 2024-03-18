#pragma once
#include "Render.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>

namespace sfml {
    class RenderImpl : public Render {
      public:
        RenderImpl(std::shared_ptr<sf::RenderWindow> window);
        void clear() override;
        void display() override;
        void draw(const Point<double>& topLeft,
                  const Point<double>& bottomRight,
                  const TileData& tile) override;

      private:
        std::shared_ptr<sf::RenderWindow> window;
    };
} // namespace sfml
