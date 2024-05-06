#include "Scene.hpp"

Scene::Scene() : zoom(ZoomLevel(0)), topLeftPoint(Point<double>{0,0}),
      isMoving{false} {}

void Scene::onMoving(Point<double> focusPos, bool moving) {
    this->isMoving = moving;
    if (moving) {
        lastPoint = focusPos;
    }
}

void Scene::onZoom(Point<double> focusPos, double delta) {
    if ((zoom <= 0) and delta < 0)
        return;

    zoom = zoom + (int)delta;

    auto scalingCoordinates = [delta] (Point<double> pos) {
        pos.x = std::ldexp(pos.x, (int)delta);
        pos.y = std::ldexp(pos.y, (int)delta);
        return pos;
    };

    Point<double> newFocusPos = scalingCoordinates(focusPos);
    Point<double> offset = {(newFocusPos.x - focusPos.x),
                            (newFocusPos.y - focusPos.y)};
    topLeftPoint = scalingCoordinates(topLeftPoint);
    topLeftPoint.x += offset.x;
    topLeftPoint.y += offset.y;
}

void Scene::onOffset(Point<double> newPoint) {
    if (isMoving) {
        double offset_x = lastPoint.x - newPoint.x;
        double offset_y = lastPoint.y - newPoint.y;
        lastPoint.x = newPoint.x;
        lastPoint.y = newPoint.y;
        topLeftPoint.x += offset_x;
        topLeftPoint.y += offset_y;
    }
}

void Scene::addTilesSource(std::shared_ptr<TilesSource> source) {
    tilesSource.push_back(std::move(source));
}

void Scene::show(Render& render) {
    render.clear();

    auto drawTile = [this, &render] (Point<double> ptr) {
        Point<size_t> posTile = (floor(ptr / (double)MAP_SIZE)).toSize_t();

        Point<double> topLeft{((double)posTile.x * MAP_SIZE) - topLeftPoint.x,
                              ((double)posTile.y * MAP_SIZE) - topLeftPoint.y};
        Point<double> bottomRight{topLeft.x + MAP_SIZE, topLeft.y + MAP_SIZE};

        TileId tileId(zoom, posTile);
        // TODO Проверка что id есть в кеше
        std::optional<Tile> cacheTile = cache.getTile(tileId);
        if (!cacheTile.has_value())
            try {
                std::optional<TileData> tileData = tilesSource[0]->get(tileId);
                if (tileData.has_value()) {
                    cacheTile =
                        std::make_optional(Tile(tileId, tileData.value()));
                    cache.addTile(tileId, tileData.value());
                }
            } catch (...) {}
        if (cacheTile.has_value()) {
            render.draw(topLeft, bottomRight, cacheTile.value());
        }
    };

    Point<int> lowerRightPoint{(int)(render.getWidthWindow() + topLeftPoint.x + MAP_SIZE),
                               (int)(render.getHeightWindow() + topLeftPoint.y + MAP_SIZE)};

    cache.clean([this, &lowerRightPoint] (const TileId& tileId) {
        Point<double> posTile{(double)tileId.pos.x * MAP_SIZE,
                              (double)tileId.pos.y * MAP_SIZE};

        if (topLeftPoint - MAP_SIZE * 3 <= posTile and
            lowerRightPoint.toDouble() + MAP_SIZE * 3 >= posTile)
            return false;
        return true;
    });

    for (auto i = topLeftPoint.x; i < lowerRightPoint.x; i += MAP_SIZE) {
        for (auto j = topLeftPoint.y; j < lowerRightPoint.y; j += MAP_SIZE) {
            drawTile(Point<double>{i,j});
        }
    }

    render.display();
}