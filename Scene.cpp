#include "Scene.hpp"

Scene::Scene(std::shared_ptr<Events> e) : events(std::move(e)) {}

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
    topLeftPoint += offset;
    bottomRightPoint = scalingCoordinates(bottomRightPoint);
    bottomRightPoint += offset;
}

void Scene::focusOnCoord(Location latlon){
    double width = bottomRightPoint.x - topLeftPoint.x;
    double height = bottomRightPoint.y - topLeftPoint.y;
    topLeftPoint = Geography::toRelativeCoord(latlon) * this->getSizeMap();

    // перемещение в точку
    topLeftPoint.x -= width / 2;
    topLeftPoint.y -= height / 2;
    bottomRightPoint.x = topLeftPoint.x + width;
    bottomRightPoint.y = topLeftPoint.y + height;
}

void Scene::emitGeolocation(Point<double> coord) const{
    coord += topLeftPoint;
    coord /= this->getSizeMap();
    events->repositioning(Geography::toLocationCoord(coord));
}

void Scene::resizeScene(unsigned width, unsigned height) {
    bottomRightPoint.x = topLeftPoint.x + width;
    bottomRightPoint.y = topLeftPoint.y + height;
}

void Scene::onOffset(Point<double> newPoint) {
    if (isMoving) {
        Point<double> offset {lastPoint.x - newPoint.x,
                              lastPoint.y - newPoint.y};
        lastPoint = newPoint;
        topLeftPoint += offset;
        bottomRightPoint += offset;

        emitGeolocation(newPoint);
    }
}

[[maybe_unused]] double Scene::getSizeMap() const{
    return sqrt(pow(4, zoom)) * TILE_SIZE;
}

void Scene::addTilesSource(std::shared_ptr<TilesSource> source) {
    tilesSource.push_back(std::move(source));
}

void Scene::show(Render& render) {
    render.clear();

    auto drawTile = [this, &render] (Point<double> ptr) {
        Point<size_t> posTile = (floor(ptr / (double)TILE_SIZE)).convert<size_t>();

        Point<double> topLeft{(posTile.convert<double>() * TILE_SIZE) - topLeftPoint};
        Point<double> bottomRight{topLeft + TILE_SIZE};

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

    Point<double> lowerRightBorder{bottomRightPoint + TILE_SIZE};

    cache.clean([this, &lowerRightBorder] (const TileId& tileId) {
        Point<double> posTile{(double)tileId.pos.x * TILE_SIZE,
                              (double)tileId.pos.y * TILE_SIZE};

        if (!(topLeftPoint - TILE_SIZE <= posTile and
              lowerRightBorder + TILE_SIZE >= posTile) or tileId.level != zoom)
            return true;
        return false;
    });

    for (auto i = topLeftPoint.x; i < lowerRightBorder.x; i += TILE_SIZE) {
        for (auto j = topLeftPoint.y; j < lowerRightBorder.y; j += TILE_SIZE) {
            drawTile(Point<double>{i,j});
        }
    }

    render.display();
}

