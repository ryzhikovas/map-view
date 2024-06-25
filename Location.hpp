#pragma once
#include <cmath>
#include <algorithm>
#include "Point.hpp"
#include "constants.hpp"

#include <iostream>

class Location{
  public:
    /**
     * @brief создания объекта Location
     * @param lon широта в градусах
     * @param lat долгота в градусах
     */
    Location(double lon, double lat);
    /**
     * @brief перевод входных координат
     * в географические координаты,
     * создания объекта Location
     * @param pt относительные координаты
     */
    explicit Location(Point<double> pt);
    /**
     * @brief перевод географических координат
     * в относительные
     * @return относительные координаты
     */
    Point<double> toRelativeCoord() const;

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

  private:
    double lon;
    double lat;
};