#pragma once
#include "Point.hpp"
#include <cstddef>

/**
 * @brief Уровень детализации
 */
class ZoomLevel {
  public:
    ZoomLevel(unsigned zoom) : zoom{zoom} {}
    operator unsigned() const {
        return zoom;
    }

  private:
    unsigned zoom;
};

/**
 * https://developers.google.com/maps/documentation/javascript/coordinates?hl=ru
 */
struct TileId {
    ZoomLevel level;
    Point<size_t> pos;

    TileId(ZoomLevel level, Point<size_t> pos) : level{level}, pos{pos} {}

    bool operator== (const TileId& tileId) const{
        if (level == tileId.level and
            pos.x == tileId.pos.x and pos.y == tileId.pos.y)
            return true;
        return false;
    }
};
