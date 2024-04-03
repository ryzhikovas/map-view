#pragma once
#include "Point.hpp"
#include "TileData.hpp"

class Render {
  public:
    ~Render() = default;
    virtual unsigned getWidthWindow() = 0;
    virtual unsigned getHeightWindow() = 0;
    virtual void clear() = 0;
    virtual void display() = 0;
    virtual void draw(const Point<double>& topLeft,
                      const Point<double>& bottomRight,
                      const TileData& tile) = 0;
};
