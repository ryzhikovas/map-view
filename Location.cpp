#include "Location.hpp"

# define M_PI           3.14159265358979323846  /* pi */
# define RADIUS            6378137  /* RAD - earth radius(m) */
# define EQUATOR_LEN    40075696 /* length of the equator */
# define HALF_EQUATOR_LEN    20037848 /* length of the equator */

Location::Location(double lon, double lat) : lon(lon), lat(lat){};

Location::Location(Point<double> pt){
    pt = (pt * EQUATOR_LEN) - HALF_EQUATOR_LEN;
    pt.y *= -1;
    lon = rad2deg(pt.x / RADIUS);
    lat = rad2deg(2 * (atanl(exp(pt.y / RADIUS)) - (M_PI / 4)));
}

Point<double> Location::toRelativeCoord() const {
    Point<double> coord{RADIUS * deg2rad(this->lon),
                        RADIUS * log(tan((M_PI / 4) + (deg2rad(this->lat) / 2)))};
    coord.y *= -1;
    coord = (coord + HALF_EQUATOR_LEN) / EQUATOR_LEN;
    return coord;
}

double Location::deg2rad(double deg) {
    return deg * M_PI / 180;
}

double Location::rad2deg(double rad) {
    return rad * 180 / M_PI;
}