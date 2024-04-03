#include "EventsImpl.hpp"
#include <SFML/Window/Event.hpp>

namespace sfml {
    EventsImpl::EventsImpl(std::shared_ptr<sf::RenderWindow> window)
        : window{std::move(window)} {}

    bool EventsImpl::fetch() {
        for (sf::Event event{}; window->pollEvent(event); /**/) {
            if (event.type == sf::Event::EventType::Closed) {
                return false;
            } else if (event.type == sf::Event::EventType::MouseWheelScrolled) {
                for (Events::WheelCallback i : mouseWheel) {
                    Pt point{double(event.mouseWheelScroll.x), double(event.mouseWheelScroll.y)};
                    i(point, event.mouseWheelScroll.delta);
                }
            } else if (event.type == sf::Event::EventType::MouseButtonReleased) {
                for (Events::PosCallback i : mouseUp) {
                    Pt point{double(event.mouseButton.x), double(event.mouseButton.y)};
                    i(point);
                }
            }else if (event.type == sf::Event::EventType::MouseButtonPressed) {
                for (Events::PosCallback i : mouseDown) {
                    Pt point{double(event.mouseButton.x), double(event.mouseButton.y)};
                    i(point);
                }
            }else if (event.type == sf::Event::EventType::MouseMoved) {
                for (Events::PosCallback i : mouseMove) {
                    Pt point{double(event.mouseMove.x), double(event.mouseMove.y)};
                    i(point);
                }
            }
        }
        return true;
    }

    void EventsImpl::onMouseMove(Events::PosCallback&& callback) {
        mouseMove.push_back(std::move(callback));
    }

    void EventsImpl::onMouseDown(Events::PosCallback&& callback) {
        mouseDown.push_back(std::move(callback));
    }

    void EventsImpl::onMouseUp(Events::PosCallback&& callback) {
        mouseUp.push_back(std::move(callback));
    }

    void EventsImpl::onMouseWheel(Events::WheelCallback&& callback) {
        mouseWheel.push_back(std::move(callback));
    }
} // namespace sfml