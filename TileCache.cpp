#include "TileCache.hpp"

std::optional<std::shared_ptr<TileData>> TileCache::getTile(const TileId& tileId) {
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
            return std::make_optional((*tile).data);
        }
    }
    return std::nullopt;
}

void TileCache::addTile(const TileId& tileId, const TileData& data){
    if (getTile(tileId) != std::nullopt)
        return;

    tiles.emplace_front(data, tileId);

    while (tiles.size() > size)
        tiles.pop_back();
}