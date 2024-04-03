#pragma once
#include "Events.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>
#include <list>

namespace sfml {
    class EventsImpl : public Events {
      public:
        EventsImpl(std::shared_ptr<sf::RenderWindow> window);
        bool fetch() override;
        void onMouseMove(PosCallback&& callback) override;
        void onMouseDown(PosCallback&& callback) override;
        void onMouseUp(PosCallback&& callback) override;
        void onMouseWheel(WheelCallback&& callback) override;

      private:
        std::shared_ptr<sf::RenderWindow> window;
        std::list<Events::PosCallback> mouseMove;
        std::list<Events::PosCallback> mouseDown;
        std::list<Events::PosCallback> mouseUp;
        std::list<Events::WheelCallback> mouseWheel;


    };
} // namespace sfml
