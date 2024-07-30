#include "SFMLWidget.hpp"

std::shared_ptr<Events> SFMLWidget::events() {
    return qtEvents;
}

void SFMLWidget::render() {
    qtEvents->render();
}

void SFMLWidget::mousePressEvent(QMouseEvent *event) {
    qtEvents->mouseDown(Point<double>{(double)event->x(),
                                      (double)event->y()});
    BaseQtCanvas::mousePressEvent(event);
}

void SFMLWidget::mouseReleaseEvent(QMouseEvent *event) {
    qtEvents->mouseUp(Point<double>{(double)event->x(),
                                    (double)event->y()});
    BaseQtCanvas::mouseReleaseEvent(event);
}

void SFMLWidget::mouseMoveEvent(QMouseEvent *event) {
    qtEvents->mouseMove(Point<double>{(double)event->x(),
                                      (double)event->y()});
    BaseQtCanvas::mouseMoveEvent(event);
}

void SFMLWidget::wheelEvent(QWheelEvent *event) {
    int angle = event->angleDelta().y();
    qtEvents->mouseWheel(Point<double>{(double)event->position().x(),
                                       (double)event->position().y()},
                                        abs(angle) / angle);
    BaseQtCanvas::wheelEvent(event);
}

void SFMLWidget::resizeEvent(QResizeEvent *event){
    qtEvents->resizing(event->size().width(), event->size().height());
    //BaseQtCanvas::resizeEvent(event);
}
