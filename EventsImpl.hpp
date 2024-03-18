#pragma once
#include "Events.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>

namespace sfml {
    class EventsImpl : public Events {
      public:
        EventsImpl(std::shared_ptr<sf::RenderWindow> window);
        bool fetch() override;
        // TODO: реализовать сохранение колбеков
        void onMouseMove(PosCallback&& callback) override;
        void onMouseDown(PosCallback&& callback) override;
        void onMouseUp(PosCallback&& callback) override;
        void onMouseWheel(WheelCallback&& callback) override;

      private:
        std::shared_ptr<sf::RenderWindow> window;
    };
} // namespace sfml
