#include "pixelcanvas.h"
#include "pixelobject.h"

#include <QDesktopWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QMouseEvent>
#include <Qt>

#include <QDebug>

PixelCanvas::PixelCanvas(QWidget *parent)
    : QWidget(parent)
{
    QDesktopWidget dw;
    this->setFixedSize(m_pixelRez,m_pixelRez); //set fixed size of canvas
    setMouseTracking(true);

    //initialize QList m_pixelList with white rects
    for (int i = 0; i < m_pixelRez; i++){
        //add to m_pixelList
        m_pixelList.append(PixelObject(i, Qt::black, Qt::magenta));
    }
}

PixelCanvas::~PixelCanvas() {}

//paint event will redraw the shapes in path
void PixelCanvas::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.drawPixmap(0, 0, m_pixmap);
    int row = 0;
    int col = 0;

    //go through Pixel Object list and redraw
    //pixels at their specific colors and size
    for (int i = 0; i < m_pixelList.size(); i++){
        if(i % 32 == 0 && i != 0) {
            qDebug() << "here";
            row ++;
            col = 0;
        }
        QRectF pixelRect = QRectF(col*m_pixelSize, row*m_pixelSize, m_pixelSize, m_pixelSize);
        qDebug() << "pixel: " << i << " " << row*m_pixelSize << "," << col*m_pixelSize;
        PixelObject pixel = m_pixelList.at(i);

        QPen pen;
        pen.setWidth(5);
        pen.setColor(pixel.getPixelOutlineColor());

        QBrush brush;
        brush.setColor(pixel.getPixelColor());
        brush.setStyle(Qt::SolidPattern);

        painter.setPen(pen);
        painter.setBrush(brush);

        painter.drawRect(pixelRect);
        painter.fillRect(pixelRect, brush);

        col++;
    }

    //draw hoverPixel with a light grey outline
}

void PixelCanvas::updatePixel() {
    //update the pixel's color in the Qlist m_pixelList

}

void PixelCanvas::changeFillColor(QColor fillColor) {
    myFillColor = fillColor;
}

//override resize event whenever the canvas is resized
void PixelCanvas::resizeEvent(QResizeEvent *) {
    auto newRect = m_pixmap.rect().united(rect());
    if (newRect == m_pixmap.rect()) return;
    QPixmap newPixmap(newRect.size());
    QPainter painter(&newPixmap);
    painter.fillRect(newPixmap.rect(), Qt::white);
    painter.drawPixmap(0, 0, m_pixmap);
    m_pixmap = newPixmap;
}

//override mousePressEvent to either 'draw' or 'modify' canvas
void PixelCanvas::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        //check which pixel we are modifying (0-31)

        //update that pixel's color will
    }
}

//override mouse move event to draw
void PixelCanvas::mouseMoveEvent(QMouseEvent *event)
{
    //check which pixel we are currently over (0-31)

    //if clicking a button change their colors
    if (event->buttons() & Qt::LeftButton){
        //change their colors

    }

    //if just hovering update the hover pixel num (0-31)

}

//override mouse release event to either 'draw' or 'modify'
void PixelCanvas::mouseReleaseEvent(QMouseEvent *event)
{
    //idk if I need tbh
}
