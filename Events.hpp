#pragma once
#include "Point.hpp"
#include <functional>

class Events {
  protected:
    using Pt = Point<double>;
    using PosCallback = std::function<void(const Pt&)>;
    using WheelCallback = std::function<void(const Pt&, double step)>;

  public:
    virtual ~Events() = default;
    virtual bool fetch() = 0;
    virtual void onMouseMove(PosCallback&& callback) = 0;
    virtual void onMouseDown(PosCallback&& callback) = 0;
    virtual void onMouseUp(PosCallback&& callback) = 0;
    virtual void onMouseWheel(WheelCallback&& callback) = 0;
};
