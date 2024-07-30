#include "SFMLWidget.hpp"

std::shared_ptr<Events> SFMLWidget::events() {
    return qtEvents;
}

void SFMLWidget::render() {
    qtEvents->render();
}
