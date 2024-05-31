#include "TileCache.hpp"

std::optional<Tile> TileCache::getTile(const TileId& tileId) {

    // TODO если в кеше могут хранится tile`ы разных источников надо проверять имя
    auto it = std::find_if(std::execution::seq,tiles.begin(), tiles.end(), [&](const Tile& tile) {
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

    tiles.emplace_back(tileId, tileData);

    return std::make_optional(tiles.back());
}

void TileCache::clean(CleanCallback&& callback){
    tiles.erase(std::remove_if(begin(tiles), end(tiles), [&] (const Tile& tile){
                    return callback(tile.id);
                }), end(tiles));
}