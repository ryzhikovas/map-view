#pragma once
#include "Events.hpp"
#include "Location.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <list>
#include <memory>

namespace sfml {
    class EventsImpl : public Events {
      public:
        EventsImpl(std::shared_ptr<sf::RenderWindow> window);
        bool fetch() override;
        void onMouseMove(PosCallback&& callback) override;
        void onMouseDown(PosCallback&& callback) override;
        void onMouseUp(PosCallback&& callback) override;
        void onMouseWheel(WheelCallback&& callback) override;
        void onChangeLocation(ChangeLocation&& callback) override;
        void repositioning(const Location& latlon) override;
      private:
        std::shared_ptr<sf::RenderWindow> window;
        std::list<Events::PosCallback> mouseMove;
        std::list<Events::PosCallback> mouseDown;
        std::list<Events::PosCallback> mouseUp;
        std::list<Events::WheelCallback> mouseWheel;
        std::list<ChangeLocation> changeLocation;
    };
} // namespace sfml
