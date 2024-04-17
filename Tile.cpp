#include "Tile.hpp"

Tile::Tile(const TileId& tileId, const TileData& tileData) : id(tileId) {
    const std::vector<char>& dataTile = tileData.bytes();
    int j = 0;
    unsigned size = MAP_SIZE * MAP_SIZE * 4;
    std::vector<sf::Uint8> pixels(size);
    for (unsigned i = 0; i < size; i += 4, j += 3) {
        std::copy(&dataTile[j], &dataTile[j + 3], &pixels[i]);
        pixels[i + 3] = 255;
    }

    texture.create(MAP_SIZE, MAP_SIZE);
    texture.update(pixels.data());
    sprite.setTexture(texture, true);
}

const sf::Sprite& Tile::getSprite() const{
    return sprite;
}