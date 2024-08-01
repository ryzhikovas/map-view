#pragma once

#include <SFML/System/Vector2.hpp>
#include "BaseQtCanvas.hpp"
#include "Events.hpp"

class SFMLWidget : public BaseQtCanvas{
  public:
    SFMLWidget(QWidget* Parent, const QPoint& Position, const QSize& Size,
          std::shared_ptr<Events> events) :
          BaseQtCanvas(Parent, Position, Size), qtEvents(std::move(events)) {}
    std::shared_ptr<Events> events();

  private:
   void render() override;
   void mousePressEvent(QMouseEvent *event) override;
   void mouseReleaseEvent(QMouseEvent *event) override;
   void mouseMoveEvent(QMouseEvent *event) override;
   void wheelEvent(QWheelEvent *event) override;
   void resizeEvent(QResizeEvent *event) override;


   std::shared_ptr<Events> qtEvents;
};
