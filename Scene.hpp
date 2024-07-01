#pragma once
#include "EventsImpl.hpp"
#include "Geography.hpp"
#include "Point.hpp"
#include "EventsImpl.hpp"
#include "Render.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "TileCache.hpp"
#include "TilesSourceImpl.hpp"
#include "constants.hpp"
#include <memory>

class Scene {
  public:
    explicit Scene(std::shared_ptr<Events> e);
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
     * @brief фокусировка сцены по входным координатам и
     * перерисовка сцены в соответствии с новым положением
     * @param render средство реализации отображения tile
     * @param latlon географические координаты
     */
    void focusOnCoord(Render& render, Location latlon);

    /**
     * @brief пересчёт входных координат в географические координаты
     * и отправление сообщения в Events об изменении координат
     * @param coord координаты положения мыши
     * в экранной системе координат
     */
    void getCoord(Point<double> coord);

    /**
     * @brief Изменение положения на экрана
     * @param newPoint изменение координат
     */
    void onOffset(Point<double> newPoint);

    /**
     * @brief Возвращает размер карты
     * @return размер карты в пикселях с учётом текущего приближения
     */
    [[maybe_unused]] double getSizeMap();

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
    std::shared_ptr<Events> events;
    std::vector<std::shared_ptr<TilesSource>> tilesSource;
    ZoomLevel zoom;
    Point<double> topLeftPoint;
    Point<double> lastPoint;
    bool isMoving;
    TileCache cache;
};
