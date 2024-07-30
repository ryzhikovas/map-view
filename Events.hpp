#pragma once
#include "Location.hpp"
#include "Point.hpp"
#include <functional>

class Events {
  protected:
    using Pt = Point<double>;
    using DrawCallback = std::function<void()>;
    using PosCallback = std::function<void(const Pt&)>;
    using WheelCallback = std::function<void(const Pt&, double step)>;
    using ChangeLocation = std::function<void(const Location& loc)>;
    using ResizingWindow = std::function<void(unsigned width, unsigned height)>;

  public:
    virtual ~Events() = default;
    virtual void render() = 0;
    virtual void mouseMove(const Pt&) = 0;
    virtual void mouseDown(const Pt&) = 0;
    virtual void mouseUp(const Pt&) = 0;
    virtual void mouseWheel(const Pt&, double step) = 0;
    virtual void resizing(unsigned width, unsigned height) = 0;
    virtual void onRender(DrawCallback&& callback) = 0;
    /**
     * @bref Связывает функции с событием MouseMove
     * @param callback ссылка на std::function выполняемая при событии MouseMove
     */
    virtual void onMouseMove(PosCallback&& callback) = 0;
    /**
     * @bref Связывает функции с событием MouseDown
     * @param callback ссылка на std::function выполняемая при событии MouseDown
     */
    virtual void onMouseDown(PosCallback&& callback) = 0;
    /**
     * @bref Связывает функции с событием MouseUp
     * @param callback ссылка на std::function выполняемая при событии MouseUp
     */
    virtual void onMouseUp(PosCallback&& callback) = 0;
    /**
     * @bref Связывает функции с событием MouseWheel
     * @param callback ссылка на std::function выполняемая при событии MouseWheel
     */
    virtual void onMouseWheel(WheelCallback&& callback) = 0;
    /**
     * @bref Вызывает обработку событий при изменении локации
     * @param latlon географические координаты
     */
    virtual void repositioning(const Location& latlon) = 0;
    /**
     * @bref Связывает функции с событием изменения локации
     * @param callback ссылка на std::function выполняемая при событии изменении местоположения
     */
    virtual void onChangeLocation(ChangeLocation&& callback) = 0;
    /**
     * @brief Связывает функции с событием изменения размера окна
     * @param callback ссылка на std::function выполняемая при событии изменения размера окна
     */
    virtual void onResizingWindow(ResizingWindow&& callback) = 0;
};
