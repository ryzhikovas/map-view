#pragma once
#include "TileId.hpp"
#include "TileData.hpp"
#include "constants.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Sprite.hpp"

class Tile{
public:
  TileId id;
  Tile(const TileId& tileId, const TileData& tileData);

  const sf::Sprite& getSprite() const;

private:
    sf::Texture texture;
    sf::Sprite sprite;
};