#pragma once

#include <cstddef>
#include <optional>
#include <iterator>
#include <list>
#include <algorithm>
#include <execution>
#include <functional>
#include <memory>
#include "TileData.hpp"
#include "TileId.hpp"
#include "Tile.hpp"
#include "constants.hpp"

class TileCache {
private:
    using CleanCallback = std::function<bool(const TileId& tileId)>;

public:
    explicit TileCache() {}

    std::optional<Tile> getTile(const TileId& tileId);

    std::optional<Tile> addTile(const TileId& tileId, const TileData& tileData);

    void clean(CleanCallback&& callback);

private:
    std::list<Tile> tiles;
};