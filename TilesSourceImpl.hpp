#pragma once
#include "TilesSource.hpp"

class TilesSourceImpl : public TilesSource {
  public:
    TilesSourceImpl(std::string dataDirectory);
    std::optional<TileData> get(const TileId& id) const override;
    std::string name() const override;

  private:
    std::string dataDirectory;
};
