#pragma once

#include <cstddef>
#include <optional>
#include <iterator>
#include <list>
#include <memory>
#include "TileData.hpp"
#include "TileId.hpp"

class TileCache {
public:
    explicit TileCache(size_t size) : size(size) {}

    std::optional<std::shared_ptr<TileData>> getTile(const TileId& tileId);

    void addTile(const TileId& tileId, const TileData& data);

private:
    struct Tile{
        std::shared_ptr<TileData> data;
        TileId id;

        Tile(const TileData& tileData, TileId tileId) :
              data(std::make_shared<TileData>(tileData)), id(tileId) {}
    };

    size_t size;
    std::list<Tile> tiles;
};