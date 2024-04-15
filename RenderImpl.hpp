#pragma once
#include "Render.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "constants.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <cstdlib>
#include <cstring>
#include <memory>

namespace sfml {
    class RenderImpl : public Render {
      public:
        RenderImpl(std::shared_ptr<sf::RenderWindow> window);
        /**
         * @return возвращает ширину экрана
         */
        unsigned getWidthWindow() override;
        /**
         * @return возвращает длину экрана
         */
        unsigned getHeightWindow() override;
        void clear() override;
        void display() override;
        /**
         * @brief проверяет наличие текстуры tile в буфере
         * @param id информация о tile
         * @return возвращает true если текстура найдена
         */
        bool getTile(const TileData& id);
        /**
         * @brief отрисовка tile на экране
         * @param topLeft левый верхний угол tile на экране
         * @param bottomRight правый нижний угол tile на экране
         * @param tile данные tile
         */
        void draw(const Point<double>& topLeft,
                  const Point<double>& bottomRight,
                  const TileData& tile) override;

      private:
        std::shared_ptr<sf::RenderWindow> window;
        std::vector<sf::Texture> spriteBuffer;
    };
} // namespace sfml
