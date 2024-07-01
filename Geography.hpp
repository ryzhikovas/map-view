#pragma once
#include <cmath>
#include <algorithm>
#include "Point.hpp"
#include "constants.hpp"
#include "Location.hpp"

class Geography {
  public:
    /**
     * @brief перевод входных координат
     * в географические координаты
     * @param pt относительные координаты
     * @return географические координаты
     */
    static Location toLocationCoord(Point<double> rc);
    /**
     * @brief перевод географических координат
     * в относительные
     * @param location географические координаты
     * @return относительные координаты
     */
    static Point<double> toRelativeCoord(const Location& location);

  private:
    /**
     * @brief перевод градусов в радианы
     * @param deg значение в градусах
     * @return значение в радианах
     */
    static double deg2rad(double deg);
    /**
     * @brief перевод радиан в градусы
     * @param rad значение в радианах
     * @return значение в градусах
     */
    static double rad2deg(double rad);
};