#include "pixelcanvas.h"

#include <QDesktopWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QMouseEvent>
#include <Qt>

PixelCanvas::PixelCanvas(QWidget *parent)
    : QWidget(parent)
{
    QDesktopWidget dw;
    this->setMinimumSize(dw.width()*0.35,dw.height()*0.35); //set minimum size of canvas
    setMouseTracking(true);
}

//override resize event whenever the pixel canvas is resized
void PixelCanvas::resizeEvent(QResizeEvent *) {
    auto newRect = m_pixmap.rect().united(rect());
    if (newRect == m_pixmap.rect()) return;
    QPixmap newPixmap(newRect.size());
    QPainter painter(&newPixmap);
    painter.fillRect(newPixmap.rect(), Qt::white);
    painter.drawPixmap(0, 0, m_pixmap);
    m_pixmap = newPixmap;
    resize(240, 240);
}
