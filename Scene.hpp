#pragma once
#include "constants.hpp"
#include "Render.hpp"
#include "TilesSourceImpl.hpp"
#include <memory>
#include <cmath>

class Scene {
  public:
    explicit Scene();
    /**
     * @brief разрешает/запрещает передвижение
     * @param focusPos координаты мыши
     * @param moving флаг разрешающий передвижение
     */
    void onMoving(Point<double> focusPos, bool moving);
    /**
     * @brief изменение масштаба
     * @param focusPos координаты мыши
     * @param delta смещение
     */
    void onZoom(Point<double> focusPos, double delta);
    /**
     * @brief Изменение положения на экрана
     * @param newPoint изменение координат
     */
    void onOffset(Point<double> newPoint);
    /**
     * @brief Добавляет источник данных тайтлов
     * @param source источник данных
     */
    void addTilesSource(std::shared_ptr<TilesSource> source);
    /**
     * @brief Управление отрисовкой
     * @param render средство реализации отображения tile
     */
    void show(Render& render);

  private:
    std::vector<std::shared_ptr<TilesSource>> tilesSource;
    ZoomLevel zoom;
    Point<double> topLeftPoint;
    Point<double> lastPoint;
    bool isMoving;
};
