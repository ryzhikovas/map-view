#include "Builder.hpp"
#include "EventsImpl.hpp"
#include "RenderImpl.hpp"
#include "constants.hpp"

namespace sfml {
    Builder::Builder() {
        QMainWindow* MainFrame = new QMainWindow();
        MainFrame->setWindowTitle("map-view");
        MainFrame->resize(WINDOW_WIDTH, WINDOW_HEIGHT);
        window = std::make_shared<SFMLWidget>(MainFrame, QPoint(0, 0), QSize(WINDOW_WIDTH, WINDOW_HEIGHT),
                                              std::make_shared<EventsImpl>());
        MainFrame->setCentralWidget(window.get());
        MainFrame->show();
    }

    std::shared_ptr<Events> Builder::events() {
        return ((SFMLWidget*)window.get())->events();
    }

    std::shared_ptr<Render> Builder::render() {
        return std::make_shared<RenderImpl>(window);
    }
} // namespace sfml
