#include "Geography.hpp"

# define M_PI           3.14159265358979323846  /* pi */
# define RADIUS            6378137  /* earth radius(m) */
# define EQUATOR_LEN    40075696 /* length of the equator */
# define HALF_EQUATOR_LEN    20037848 /* length of the equator */

Location Geography::toLocationCoord(Point<double> rc) {
    // переводим координаты в проекцию Mercator
    rc = (rc * EQUATOR_LEN) - HALF_EQUATOR_LEN;
    rc.y *= -1;
    return Location{rad2deg(rc.x / RADIUS),
            rad2deg(2 * (atanl(exp(rc.y / RADIUS)) - (M_PI / 4)))};
}

Point<double> Geography::toRelativeCoord(const Location& location) {
    // переводим координаты в проекцию Mercator
    Point<double> coord{RADIUS * deg2rad(location.lon),
                        RADIUS * log(tan((M_PI / 4) + (deg2rad(location.lat) / 2)))};
    coord.y *= -1;
    coord = (coord + HALF_EQUATOR_LEN) / EQUATOR_LEN;
    return coord;
}

double Geography::deg2rad(double deg) {
    return deg * M_PI / 180;
}

double Geography::rad2deg(double rad) {
    return rad * 180 / M_PI;
}