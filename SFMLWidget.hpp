
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


    std::shared_ptr<Events> qtEvents;
};
