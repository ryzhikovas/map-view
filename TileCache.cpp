#include "TileCache.hpp"

std::optional<Tile> TileCache::getTile(const TileId& tileId) {

    // TODO если в кеше могут хранится tile`ы разных источников надо проверять имя
    auto it = std::find_if(tiles.begin(), tiles.end(), [&](const Tile& tile) {
        return tile.id == tileId;
    });
    if (it != std::end(tiles)) {
        return std::make_optional(*it);
    }
    return std::nullopt;
}

std::optional<Tile> TileCache::addTile(const TileId& tileId, const TileData& tileData){
    std::optional<Tile> tile = getTile(tileId);
    if (tile != std::nullopt)
        return tile;

    tiles.emplace_front(tileId, tileData);

    return std::make_optional(tiles.front());
}

void TileCache::clean(CleanCallback&& callback){
    tiles.remove_if([&] (Tile& tile){
        return callback(tile.id);
    });
}