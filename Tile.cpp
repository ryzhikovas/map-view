#include "Tile.hpp"

Tile::Tile(const TileId& tileId, const TileData& tileData) : id(tileId) {
    const std::vector<char>& dataTile = tileData.bytes();
    const unsigned size = TILE_SIZE * TILE_SIZE * 4;
    std::vector<sf::Uint8> pixels(size);
    auto pixel{pixels.begin()};
    for (auto data{dataTile.begin()}; data != dataTile.end(); data += 3) {
        std::copy(data, data + 3, pixel);
        pixel += 3;
        *pixel = 255;
        ++pixel;
    }

    texture.create(TILE_SIZE, TILE_SIZE);
    texture.update(pixels.data());
}

void Tile::getSprite(sf::Sprite& sprite) const{
    sprite.setTexture(texture, true);
}