#pragma once
#include "Events.hpp"
#include "Render.hpp"
#include "BaseQtCanvas.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <QMainWindow>
#include <QHBoxLayout>
#include <memory>

namespace sfml {
    class Builder {
      public:
        Builder();
        std::shared_ptr<Events> events();
        std::shared_ptr<Render> render();

      private:
        std::shared_ptr<BaseQtCanvas> window;
    };
} // namespace sfml
