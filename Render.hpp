#pragma once
#include "Point.hpp"
#include "Tile.hpp"
#include "TileData.hpp"
#include "SFML/Graphics/Sprite.hpp"

class Render {
  public:
    ~Render() = default;
    virtual void clear() = 0;
    virtual void display() = 0;
    virtual void draw(const Point<double>& topLeft,
                      const Point<double>& bottomRight,
                      const Tile& tile) = 0;
};
