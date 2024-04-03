#pragma once
#include "TileData.hpp"
#include "TileId.hpp"
#include <optional>
#include <string>

class TilesSource {
  public:
    virtual ~TilesSource() = default;
    /**
     * @brief Возвращает данные тайла
     * @throw std::logic_error в случае внутренних ошибок
     * @param id индекс тайла
     * @return данные тайла или std::nullopt, если тайл отсутствует
     */
    virtual std::optional<TileData> get(const TileId& id) const = 0;
    /**
     * @return имя источника данных. Должно быть уникальным для каждого источника данных
     */
    virtual std::string name() const = 0;
};
