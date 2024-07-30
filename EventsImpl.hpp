#pragma once
#include "Events.hpp"
#include "Location.hpp"
#include "SFMLWidget.hpp"
#include <QWidget>
#include <list>
#include <memory>
#include <queue>

class EventsImpl : public Events {
  public:
    EventsImpl();
    void render() override;
    void mouseMove(const Pt& pt) override;
    void mouseDown(const Pt& pt) override;
    void mouseUp(const Pt& pt) override;
    void mouseWheel(const Pt& pt, double step) override;
    void resizing(unsigned width, unsigned height) override;
    void onRender(DrawCallback&& callback) override;
    void onMouseMove(PosCallback&& callback) override;
    void onMouseDown(PosCallback&& callback) override;
    void onMouseUp(PosCallback&& callback) override;
    void onMouseWheel(WheelCallback&& callback) override;
    void onChangeLocation(ChangeLocation&& callback) override;
    void repositioning(const Location& latlon) override;
    void onResizingWindow(ResizingWindow&& callback) override;
  private:
    std::list<Events::DrawCallback> drawWidget;
    std::list<Events::PosCallback> mouseMoveCallbacks;
    std::list<Events::PosCallback> mouseDownCallbacks;
    std::list<Events::PosCallback> mouseUpCallbacks;
    std::list<Events::WheelCallback> mouseWheelCallbacks;
    std::list<ChangeLocation> changeLocation;
    std::list<ResizingWindow> resizingWindow;
};

