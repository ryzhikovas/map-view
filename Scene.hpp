#pragma once
#include "Render.hpp"
#include "TilesSource.hpp"
#include <memory>

class Scene {
  public:
    void onZoom(double delta, Point<double> focusPos);
    void onOffset(Point<double> offset);
    void addTilesSource(std::shared_ptr<TilesSource> source);
    void show(Render& render);
};
