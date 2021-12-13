#ifndef PIXELCANVAS_H
#define PIXELCANVAS_H

#include "pixelobject.h"
#include <QObject>
#include <QWidget>
#include <QPixmap>
#include <QPainter>
#include <QPaintEvent>

class PixelCanvas : public QWidget
{
    Q_OBJECT
public:
    PixelCanvas(QWidget *parent = nullptr);
    ~PixelCanvas();
    void updatePixel();//update the pixel
    void changeFillColor(QColor); //change the color we have in hand
    QPainterPath getPixelPath(int);
    QColor myFillColor = Qt::white; //color of mypixel
    int myCurrentPixel = 0; //pixel (0-m_pixelRez) user hovers over

protected:
    void mousePressEvent(QMouseEvent *event) override;
//    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    QList<PixelObject> m_pixelList;
    int m_pixelRez = 1024;
    int m_pixelSize = 32;
    int m_hoverPixel; //pixel (0-m_pixelRez) user is hovering over
    QColor m_hoverOutlineColor = Qt::lightGray; //color of the outline of the pixel we are hovering over
    QColor m_gridColor = Qt::transparent;
    QImage m_image; //eventual image output
    bool m_mouseIsPressed; //true if user presses mouse click
    // Create a QPixmap object that you will use to store the bitmap the user will draw [on].
    QPixmap m_pixmap;
};

#endif // PIXELCANVAS_H
