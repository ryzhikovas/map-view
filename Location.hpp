#pragma once

struct Location {
    Location(double lon, double lat) : lon(lon), lat(lat) {};

    double lon;
    double lat;
};
