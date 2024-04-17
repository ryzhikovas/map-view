#include "TileCache.hpp"

std::optional<Tile> TileCache::getTile(const TileId& tileId) {
    auto equal = [tileId](const TileId& id) {
        if (id.level == tileId.level and id.pos.x == tileId.pos.x and
            id.pos.y == tileId.pos.y)
            return true;
        return false;
    };

    for(auto tile{tiles.begin()}; tile !=tiles.end(); tile++ ) {
        // TODO если в кеше могут хранится tile`ы разных источников надо проверять имя
        if (equal((*tile).id)) {
            tiles.splice(tiles.begin(), tiles, tile);
            return std::make_optional((*tile));
        }
    }
    return std::nullopt;
}

std::optional<Tile> TileCache::addTile(const TileId& tileId, const TileData& tileData){
    std::optional<Tile> tile = getTile(tileId);
    if (tile != std::nullopt)
        return tile;

    tiles.emplace_front(tileId, tileData);

    while (tiles.size() > size)
        tiles.pop_back();

    return std::make_optional(tiles.front());
}