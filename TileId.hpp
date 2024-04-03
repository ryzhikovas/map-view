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
};
