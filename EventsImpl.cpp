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
                /**
                 * TODO: вызвать callback'и mouseWheel
                 * event.mouseWheelScroll.x event.mouseWheelScroll.y
                 * event.mouseWheelScroll.delta
                 */
            }
            // TODO: вызвать callback'и mouseMove/Down/Up
        }
        return true;
    }

    void EventsImpl::onMouseMove(Events::PosCallback&& callback) {}

    void EventsImpl::onMouseDown(Events::PosCallback&& callback) {}

    void EventsImpl::onMouseUp(Events::PosCallback&& callback) {}

    void EventsImpl::onMouseWheel(Events::WheelCallback&& callback) {}
} // namespace sfml