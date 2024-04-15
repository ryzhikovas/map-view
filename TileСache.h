#pragma once

#include <cstddef>
#include <optional>
#include <iterator>
#include <list>
#include "TileData.hpp"
#include "TileId.hpp"

class TileCache {
public:
    explicit TileCache(size_t size) : size(size) {}

    std::optional<TileData> getTile(const TileId& tileId) {
        auto equal = [tileId] (const TileId& id) {
            if (id.level == tileId.level and
                id.pos.x == tileId.pos.x and
                id.pos.y == tileId.pos.y)
                return true;
            return false;
        };

        for (Tile tile : tiles) {
            // TODO если в кеше могут хранится тайлы разных источников надо проверять имя
            if (equal(tile.id)) {
//                tiles.remove(tile);
                return std::make_optional(tile.data);
            }
        }
        return std::nullopt;
    }

private:
    struct Tile{
        const TileData& data;
        TileId id;

        Tile(const TileData& tileData, TileId tileId) : data(tileData), id(tileId) {}
    };

    size_t size;
    std::list<Tile> tiles;
};