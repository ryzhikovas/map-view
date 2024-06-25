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

void Scene::focusOnCoord(Render& render, Location latlon){
    topLeftPoint = latlon.toRelativeCoord() * this->getSizeMap();

    // перемещение в точку
    topLeftPoint.x -= (double)render.getWidthWindow() / 2;
    topLeftPoint.y -= (double)render.getHeightWindow() / 2;
    show(render);
}

Location Scene::getCoord(Point<double> coord){
    coord += topLeftPoint;
    coord /= this->getSizeMap();
    return coord::to_LatLon(coord);
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

[[maybe_unused]] double Scene::getSizeMap(){
    return sqrt(pow(4, zoom)) * TILE_SIZE;
}

void Scene::addTilesSource(std::shared_ptr<TilesSource> source) {
    tilesSource.push_back(std::move(source));
}

void Scene::show(Render& render) {
    render.clear();

    auto drawTile = [this, &render] (Point<double> ptr) {
        Point<size_t> posTile = (floor(ptr / (double)TILE_SIZE)).convert<size_t>();

        Point<double> topLeft{((double)posTile.x * TILE_SIZE) - topLeftPoint.x,
                              ((double)posTile.y * TILE_SIZE) - topLeftPoint.y};
        Point<double> bottomRight{topLeft.x + TILE_SIZE, topLeft.y + TILE_SIZE};

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

    Point<double> lowerRightPoint{(render.getWidthWindow() + topLeftPoint.x + TILE_SIZE),
                               (render.getHeightWindow() + topLeftPoint.y + TILE_SIZE)};

    cache.clean([this, &lowerRightPoint] (const TileId& tileId) {
        Point<double> posTile{(double)tileId.pos.x * TILE_SIZE,
                              (double)tileId.pos.y * TILE_SIZE};

        if (!(topLeftPoint - TILE_SIZE <= posTile and
            lowerRightPoint + TILE_SIZE >= posTile) or tileId.level != zoom)
            return true;
        return false;
    });

    for (auto i = topLeftPoint.x; i < lowerRightPoint.x; i += TILE_SIZE) {
        for (auto j = topLeftPoint.y; j < lowerRightPoint.y; j += TILE_SIZE) {
            drawTile(Point<double>{i,j});
        }
    }

    render.display();
}