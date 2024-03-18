#pragma once
#include <vector>

/**
 * @brief Содержит данные тайла
 * Размер тайла в пикселях 256x256 пикселей
 * В текущей реализации тайл всегда трехканальный (RGB), 24 бита на пиксель
 */
class TileData {
  public:
    TileData(std::vector<char> bytes);
    /**
     * @return данные тайла в формате R0 G0 B0 R1 G1 B1 ... Rn Gn Bn,
     * где Qi - код яркости канала Q пикселя с номером i. Данные соседних
     * строк тайла записаны друг за другом без пропусков.
     */
    const std::vector<char>& bytes() const;

  private:
    std::vector<char> bytes_;
};
