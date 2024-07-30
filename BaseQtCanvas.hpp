#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics.hpp>
#include <QWidget>
#include <QTimer>
#include <QEvent>
#include <QResizeEvent>

class BaseQtCanvas: public QWidget, public sf::RenderWindow {
  public:
    BaseQtCanvas(QWidget* Parent, const QPoint& Position, const QSize& Size, unsigned int FrameTime = 0);

  private:

    virtual void render() = 0;
    QPaintEngine *paintEngine() const override;
    void showEvent(QShowEvent*) override;
    void paintEvent(QPaintEvent*) override;

  protected:
    void resizeEvent(QResizeEvent* event) override;

  private:
    QTimer myTimer;
    bool   myInitialized;
};
