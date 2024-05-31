#pragma once
#include <cmath>
#include <algorithm>
#include "Point.hpp"
#include "constants.hpp"

# define M_PI           3.14159265358979323846  /* pi */

struct Location {
    double lon;
    double lat;
};

namespace coord {
    // градусы в радианы
    double deg2rad(double deg);

    // радианы в градусы
    double rad2deg(double rad);

    //
    Location to_LatLon(Point<double> pt);

    Point<double> to_pixel(Location latlon);
}