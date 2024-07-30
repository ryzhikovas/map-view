#include "EventsImpl.hpp"

EventsImpl::EventsImpl() {}

void EventsImpl::render(){
    for (const DrawCallback& callback : drawWidget) {
        callback();
    }
}

void EventsImpl::mouseMove(const Pt& pt) {
    for (const Events::PosCallback& callback : mouseMoveCallbacks) {
        callback(pt);
    }
}
void EventsImpl::mouseDown(const Pt& pt) {
    for (const Events::PosCallback& callback : mouseDownCallbacks) {
        callback(pt);
    }
}
void EventsImpl::mouseUp(const Pt& pt) {
    for (const Events::PosCallback& callback : mouseUpCallbacks) {
        callback(pt);
    }
}
void EventsImpl::mouseWheel(const Pt& pt, double step) {
    for (const Events::WheelCallback& callback : mouseWheelCallbacks) {
        callback(pt, step);
    }
}

void EventsImpl::resizing(unsigned width, unsigned height) {
    for (const Events::ResizingWindow& callback : resizingWindow) {
        callback(width, height);
    }
}

void EventsImpl::onRender(DrawCallback&& callback) {
    drawWidget.push_back(callback);
}

void EventsImpl::onMouseMove(Events::PosCallback&& callback) {
    mouseMoveCallbacks.push_back(std::move(callback));
}

void EventsImpl::onMouseDown(Events::PosCallback&& callback) {
    mouseDownCallbacks.push_back(std::move(callback));
}

void EventsImpl::onMouseUp(Events::PosCallback&& callback) {
    mouseUpCallbacks.push_back(std::move(callback));
}

void EventsImpl::onMouseWheel(Events::WheelCallback&& callback) {
    mouseWheelCallbacks.push_back(std::move(callback));
}

void EventsImpl::onChangeLocation(ChangeLocation&& callback) {
    changeLocation.push_back(std::move(callback));
}

void EventsImpl::repositioning(const Location& latlon) {
    for(const ChangeLocation& callback : changeLocation) {
        callback(latlon);
    }
}

void EventsImpl::onResizingWindow(ResizingWindow&& callback) {
    resizingWindow.push_back(std::move(callback));
}