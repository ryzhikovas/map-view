#include "EventsImpl.hpp"
#include <SFML/Window/Event.hpp>

namespace sfml {
    EventsImpl::EventsImpl(std::shared_ptr<sf::RenderWindow> window)
        : window{std::move(window)} {}

    bool EventsImpl::fetch() {
        auto toPt = [] (auto pointLike) {
            return Pt{double(pointLike.x), double(pointLike.y)};
        };

        for (sf::Event event{}; window->pollEvent(event); /**/) {
            if (event.type == sf::Event::EventType::Closed) {
                return false;
            } else if (event.type == sf::Event::EventType::MouseWheelScrolled) {
                for (const Events::WheelCallback& callback : mouseWheel) {
                    callback(toPt(event.mouseWheelScroll), event.mouseWheelScroll.delta);
                }
            } else if (event.type == sf::Event::EventType::MouseButtonReleased) {
                for (const Events::PosCallback& callback : mouseUp) {
                    callback(toPt(event.mouseButton));
                }
            }else if (event.type == sf::Event::EventType::MouseButtonPressed) {
                for (const Events::PosCallback& callback : mouseDown) {
                    callback(toPt(event.mouseButton));
                }
            }else if (event.type == sf::Event::EventType::MouseMoved) {
                for (const Events::PosCallback& callback : mouseMove) {
                    callback(toPt(event.mouseMove));
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

    void EventsImpl::changePtr(Location latlon) {
    }
} // namespace sfml