#include "Scene.hpp"

Scene::Scene() : zoom(ZoomLevel(0)), topLeftPoint(Point<double>{0,0}), isMoving{false}{}

void Scene::onMoving(Point<double> focusPos, bool moving) {
    this->isMoving = moving;
    if (moving) {
        lastPoint = Point<double>{focusPos.x,focusPos.y};
    }
}

void Scene::onZoom(Point<double> focusPos, double delta) {
    size_t z = zoom;
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
    tilesSource.push_back(source);
}

void Scene::show(Render& render) {
    render.clear();

    auto drawTile = [this, &render] (Point<double> ptr) {
        Point<size_t> posTile{(size_t)floor(ptr.x / 256),(size_t)floor(ptr.y / 256)};

        Point<double> topLeft{((double)posTile.x * 256) - topLeftPoint.x,
                              ((double)posTile.y * 256) - topLeftPoint.y};
        Point<double> bottomRight{topLeft.x + 256, topLeft.y + 256};

        TileId tileId(zoom, posTile);
        std::optional<TileData> tile = tilesSource[0]->get(tileId);
        if (tile.has_value()){
            render.draw(topLeft, bottomRight, tile.value());
        }
    };

    Point<int> lowerRightPoint{(int)(render.getHeightWindow() + topLeftPoint.y),
                               (int)(render.getWidthWindow() + topLeftPoint.x)};

    for (auto i = topLeftPoint.x; i < lowerRightPoint.x + 256; i += 256) {
        for (auto j = topLeftPoint.y; j < lowerRightPoint.y + 256; j += 256) {
            drawTile(Point<double>{i,j});
        }
    }

    render.display();
}