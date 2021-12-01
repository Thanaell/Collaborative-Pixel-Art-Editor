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
    //set size -> has to be square dimensions
    setMouseTracking(true);
}

//override resize event whenever the pixel canvas is resized
void PixelCanvas::resizeEvent(QResizeEvent *) {
    auto newRect = pixmap.rect().united(rect());
    if (newRect == pixmap.rect()) return;
    QPixmap newPixmap(newRect.size());
    QPainter painter(&newPixmap);
    painter.fillRect(newPixmap.rect(), Qt::white);
    painter.drawPixmap(0, 0, pixmap);
    pixmap = newPixmap;
    resize(240, 240);
}
