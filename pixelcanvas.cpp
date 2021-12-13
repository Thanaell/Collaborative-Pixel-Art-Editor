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
    int row = 0;
    int col = 0;

    for (int i = 0; i < m_pixelRez; i++){
        if(i % 32 == 0 && i != 0) {
            row ++;
            col = 0;
        }
        //add to m_pixelList
        m_pixelList.append(PixelObject(i, Qt::white, m_gridColor, col*m_pixelSize, row*m_pixelSize));

        col++;
    }
    //display update
    update();
}

PixelCanvas::~PixelCanvas() {}

//paint event will redraw the shapes in path
void PixelCanvas::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.drawPixmap(0, 0, m_pixmap);

    QList <int> outlinedPixels;

    //go through Pixel Object list and redraw
    //pixels at their specific colors and outlines
    for (int i = 0; i < m_pixelRez; i++){
        PixelObject pixel = m_pixelList.at(i);
        QRectF pixelRect = QRectF(pixel.getX(), pixel.getY(), m_pixelSize, m_pixelSize);

        QPen pen;
        pen.setWidth(2);
        pen.setColor(pixel.getPixelOutlineColor());

        QBrush brush;
        brush.setColor(pixel.getPixelColor());
        brush.setStyle(Qt::SolidPattern);

        painter.setPen(pen);
        painter.setBrush(brush);

        painter.drawRect(pixelRect);
        painter.fillRect(pixelRect, brush);

        if(pixel.getPixelOutlineColor() != m_gridColor) {
            outlinedPixels.append(i);
        }
    }

    if(outlinedPixels.size() > 0) {
        qDebug() << outlinedPixels.size();
        //need to draw the highlighted pixels again over the rest of the grid
        for(int i = 0; i < outlinedPixels.size(); i++){
            int pixelAt  = outlinedPixels.at(i);
            PixelObject pixel = m_pixelList.at(pixelAt);
            QRectF pixelRect = QRectF(pixel.getX(), pixel.getY(), m_pixelSize, m_pixelSize);

            QPen pen;
            pen.setWidth(2);
            pen.setColor(pixel.getPixelOutlineColor());

            painter.setPen(pen);

            painter.drawRect(pixelRect);
        }
    }
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
        //check which pixel we are modifying (0-m_pixelRez)

        //update that pixel's color will
    }
}

//override mouse move event to draw
void PixelCanvas::mouseMoveEvent(QMouseEvent *event)
{
    //check which pixel we are currently over (0-m_pixelRez)
    for (int i = 0; i < m_pixelList.size(); i++) {
        //check if over a pixel
        if(getPixelPath(i).contains(event->pos())) {
            PixelObject pixel = m_pixelList.at(i);

//            //if clicking a button change their colors
//            if (event->buttons() & Qt::LeftButton){
//                //change their colors

//            }

            //if hovering over new pixel, change outline
            if(myCurrentPixel != i){
                //update pixel outline and update myCurrentPixel
                //first make sure previous hover is back to normal
                m_pixelList[myCurrentPixel].setPixelOutlineColor(m_gridColor);
                //update current pixel
                myCurrentPixel = i;
                //update current pixel outline color
                m_pixelList[myCurrentPixel].setPixelOutlineColor(m_hoverOutlineColor);

                //draw update
                update();
            }
        }
    }


}

//override mouse release event to either 'draw' or 'modify'
//void PixelCanvas::mouseReleaseEvent(QMouseEvent *event)
//{
//    //idk if I need tbh
//}

QPainterPath PixelCanvas::getPixelPath(int pixelNum) {
    QPainterPath path; //set up the path

    PixelObject pixel = m_pixelList.at(pixelNum);
    QRectF pixelRect = QRectF(pixel.getX(), pixel.getY(), m_pixelSize, m_pixelSize);

    path.addRect(pixelRect);

    return path;
}
