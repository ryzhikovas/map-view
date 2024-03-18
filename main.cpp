#include "Builder.hpp"
#include "Events.hpp"
#include "Render.hpp"
#include "Scene.hpp"
#include "TilesSourceImpl.hpp"
#include <iostream>
#include <memory>

int main(int argc, char* argv[]) {

    if (argc < 2) {
        std::cerr << "Please, call with one argument "
                  << "( example: " << argv[0] << " <path to tiles directory>)";
        return 1;
    }
    try {
        auto tiles = std::dynamic_pointer_cast<TilesSource>(
            std::make_shared<TilesSourceImpl>(argv[1]));
        Scene scene;
        scene.addTilesSource(tiles);
        sfml::Builder sfmlBuilder;
        auto events = sfmlBuilder.events();
        auto render = sfmlBuilder.render();

        // TODO: зарегистрировать обработчики событий events->on...

        while (events->fetch()) {
            scene.show(*render);
        }
    } catch (std::exception& ex) {
        std::cerr << ex.what() << std::endl;
        return 2;
    }
}