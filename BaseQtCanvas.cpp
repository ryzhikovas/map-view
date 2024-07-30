#include "BaseQtCanvas.hpp"

#ifdef Q_WS_X11
#include <Qt/qx11info_x11.h>
#include <X11/Xlib.h>
#endif

BaseQtCanvas::BaseQtCanvas(QWidget* Parent, const QPoint& Position, const QSize& Size, unsigned int FrameTime) :
      QWidget (Parent),
      myInitialized (false)
{
    setAttribute(Qt::WA_PaintOnScreen);
    setAttribute(Qt::WA_OpaquePaintEvent);
    setAttribute(Qt::WA_NoSystemBackground);

    setFocusPolicy(Qt::StrongFocus);

    move(Position);
    resize(Size);

    myTimer.setInterval(FrameTime);
}

void BaseQtCanvas::showEvent(QShowEvent*)
{
    if (!myInitialized)
    {
        #ifdef Q_WS_X11
                XFlush(QX11Info::display());
        #endif

        sf::RenderWindow::create((HWND)winId());

        render();

        connect(&myTimer, SIGNAL(timeout()), this, SLOT(repaint()));
        myTimer.start();

        myInitialized = true;
    }
}

QPaintEngine* BaseQtCanvas::paintEngine() const
{
    return nullptr;
}

void BaseQtCanvas::paintEvent(QPaintEvent*)
{
    sf::RenderWindow::clear();
    render();
    sf::RenderWindow::display();
}
void BaseQtCanvas::resizeEvent(QResizeEvent* event) {
    setView(sf::View(sf::FloatRect(0.f, 0.f,
                     event->size().width(), event->size().height())));
    QWidget::resizeEvent(event);
}
