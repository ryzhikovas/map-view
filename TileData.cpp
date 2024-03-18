#include "TileData.hpp"

TileData::TileData(std::vector<char> bytes) : bytes_{std::move(bytes)} {}

const std::vector<char>& TileData::bytes() const {
    return bytes_;
}
