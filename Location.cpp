#include "Location.hpp"

// функция перевода в стереографическую проекцию

# define M_PI           3.14159265358979323846  /* pi */
# define RAD            6378137  /* RAD - earth radius(m) */
# define EQUATOR_LEN    40075696 /* length of the equator */
# define HALF_EQUATOR_LEN    20037848 /* length of the equator */


double coord::deg2rad(double deg) {
    return deg * M_PI / 180;
}

double coord::rad2deg(double rad) {
    return rad / M_PI / 180;
}

Location coord::to_LatLon(Point<double> pt) {
    pt = (pt * EQUATOR_LEN) - HALF_EQUATOR_LEN;
    pt.y *= -1;
    return Location{rad2deg(pt.x / RAD),
                    rad2deg(2 * (atanl(exp(pt.y / RAD)) - (M_PI / 4)) * 2)};
}

Point<double> coord::to_pixel(Location latlon) {
    Point<double> coord{deg2rad(latlon.lon),
                        RAD * log(tan((M_PI / 4) + (deg2rad(latlon.lat) / 2)))};
    coord.y *= -1;
    coord = (coord + HALF_EQUATOR_LEN) / EQUATOR_LEN;
    return coord;
}