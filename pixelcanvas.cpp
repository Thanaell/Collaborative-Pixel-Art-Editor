#include "pixelcanvas.h"
#include "pixelobject.h"
#include "RequestManager.h"

#include <QDesktopWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QMouseEvent>
#include <Qt>

#include <QDebug>

PixelCanvas::PixelCanvas(QWidget *parent, RequestManager *requestManager)
    : QWidget(parent)
{
    QDesktopWidget dw;

    m_requestManager = requestManager;

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

    //TEST last few updated
//    updatePixelOutline(0, "#D3D3D3");
//    updatePixelOutline(1, "#D3D3D3");
//    updatePixelOutline(2, "#D3D3D3");
//    updatePixelOutline(100, "#D3D3D3");

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

        if(pixel.getPixelOutlineColor() != m_gridColor) {
            outlinedPixels.append(i);
        }
    }

    if(outlinedPixels.size() > 0) {
        //need to draw the highlighted pixels again over the rest of the grid
        for(int i = 0; i < outlinedPixels.size(); i++){
            int pixelAt  = outlinedPixels.at(i);
            PixelObject pixel = m_pixelList.at(pixelAt);
            QRectF pixelRect = QRectF(pixel.getX(), pixel.getY(), m_pixelSize, m_pixelSize);

            QPen pen;
            pen.setWidth(2);
            pen.setColor(pixel.getPixelOutlineColor());

            QBrush brush;
            brush.setColor(Qt::transparent);
            brush.setStyle(Qt::SolidPattern);

            painter.setPen(pen);
            painter.setBrush(brush);

            painter.drawRect(pixelRect);
        }
    }
}

void PixelCanvas::updatePixelColor(int pixelNum, QString color) {
    //update the pixel's color
    m_pixelList[pixelNum].setPixelColor(QColor(color));
}

void PixelCanvas::updatePixelOutline(int pixelNum, QString color) {
    //update the pixel's outline color
    m_pixelList[pixelNum].setPixelOutlineColor(QColor(color));
}

void PixelCanvas::resetPixelOutline(int pixelNum) {
    //rest the pixel's outline to transparent
    m_pixelList[pixelNum].setPixelOutlineColor(m_gridColor);
}

void PixelCanvas::changeSelectedColor(QString selectedColor) {
    mySelectedColor = QColor(selectedColor);
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
        //check which pixel we are currently over (0-m_pixelRez)
        for (int i = 0; i < m_pixelList.size(); i++) {
            //check if over a pixel
            if(getPixelPath(i).contains(event->pos())) {
                //change pixel color
                m_pixelList[i].setPixelColor(mySelectedColor);
                //send update to server
                QString pixelColor = m_pixelList[i].getPixelColor().name(QColor::HexRgb);
                m_requestManager->setPixel(i, pixelColor);
                update();
            }
        }
    }
}

//override mouse move event to draw
void PixelCanvas::mouseMoveEvent(QMouseEvent *event)
{
    //check which pixel we are currently over (0-m_pixelRez)
    for (int i = 0; i < m_pixelList.size(); i++) {
        //check if over a pixel
        if(getPixelPath(i).contains(event->pos())) {
            //if clicking a button change the pixel color
            if (event->buttons() & Qt::LeftButton){
                //change pixel color
                m_pixelList[i].setPixelColor(mySelectedColor);
                //send update to server
                QString pixelColor = m_pixelList[i].getPixelColor().name(QColor::HexRgb);
                m_requestManager->setPixel(i, pixelColor);
                update();
            }

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
