#pragma once

#include <cstddef>
#include <optional>
#include <iterator>
#include <list>
#include <memory>
#include "TileData.hpp"
#include "TileId.hpp"
#include "Tile.hpp"
#include "constants.hpp"

class TileCache {
public:
    explicit TileCache(size_t size) : size(size) {}

    std::optional<Tile> getTile(const TileId& tileId);

    std::optional<Tile> addTile(const TileId& tileId, const TileData& tileData);

private:
    size_t size;
    std::list<Tile> tiles;
};