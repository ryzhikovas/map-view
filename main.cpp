#include "Builder.hpp"
#include "Events.hpp"
#include "Render.hpp"
#include "Scene.hpp"
#include "TilesSourceImpl.hpp"
#include <iostream>
#include <memory>
#include <QApplication>

#ifdef WIN32
#include <QtPlugin>
Q_IMPORT_PLUGIN(QWindowsIntegrationPlugin);
#endif

int main(int argc, char* argv[]) {

    if (argc < 2) {
        std::cerr << "Please, call with one argument "
                  << "( example: " << argv[0] << " <path to tiles directory>)";
        return 1;
    }
    try {
        auto tiles = std::dynamic_pointer_cast<TilesSource>(
            std::make_shared<TilesSourceImpl>(argv[1]));

        QApplication app(argc, argv);

        sfml::Builder sfmlBuilder;
        auto events = sfmlBuilder.events();
        auto render = sfmlBuilder.render();
        Scene scene(events);
        scene.addTilesSource(tiles);

        events->onMouseMove([&scene] (Point<double> pt) {
            scene.onOffset(pt);
        });

        events->onMouseDown([&scene] (Point<double> pt) {
            scene.onMoving(pt, true);
        });

        events->onMouseUp([&scene] (Point<double> pt) {
            scene.onMoving(pt, false);
        });

        events->onMouseWheel([&scene] (Point<double> pt, double step) {
            scene.onZoom(pt, step);
        });

        events->onResizingWindow([&scene] (unsigned width, unsigned height) {
            scene.resizeScene(width, height);
        });

        return QApplication::exec();
    } catch (std::exception& ex) {
        std::cerr << ex.what() << std::endl;
        return 2;
    }
}