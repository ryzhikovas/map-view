#pragma once
#include "Render.hpp"
#include "constants.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <cstdlib>
#include <cstring>
#include <memory>

namespace sfml {
    class RenderImpl : public Render {
      public:
        RenderImpl(std::shared_ptr<sf::RenderWindow> window);
        void clear() override;
        void display() override;
        /**
         * @brief отрисовка tile на экране
         * @param topLeft левый верхний угол tile на экране
         * @param bottomRight правый нижний угол tile на экране
         * @param tile данные tile
         */
        void draw(const Point<double>& topLeft,
                  const Point<double>& bottomRight,
                  const Tile& tile) override;

      private:
        std::shared_ptr<sf::RenderWindow> window;
    };
} // namespace sfml
