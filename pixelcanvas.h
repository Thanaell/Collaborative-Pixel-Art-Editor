#ifndef PIXELCANVAS_H
#define PIXELCANVAS_H

#include "pixelobject.h"
#include "RequestManager.h"

#include <QObject>
#include <QWidget>
#include <QPixmap>
#include <QPainter>
#include <QPaintEvent>
#include <qpainterpath.h>

class PixelCanvas : public QWidget
{
    Q_OBJECT
public:
    PixelCanvas(QWidget *parent = nullptr, RequestManager *requestManager = nullptr);
    ~PixelCanvas();
    void updatePixelColor(int, QString); //update a pixel color
    void updatePixelOutline(int, QString); //update a pixel's outline color
    void resetPixelOutline(int); //reset a pixel's outline color
    void changeSelectedColor(QString); //change the color we have in hand
    QPainterPath getPixelPath(int);
    QColor mySelectedColor; //color which is selected
    int myCurrentPixel = 0; //pixel currently hovering over

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
    QColor m_hoverOutlineColor = Qt::lightGray; //color of the outline of the pixel we are hovering over
    QColor m_gridColor = Qt::transparent;
    QImage m_image; //eventual image output
    bool m_mouseIsPressed; //true if user presses mouse click
    // Create a QPixmap object that you will use to store the bitmap the user will draw [on].
    QPixmap m_pixmap;
};

#endif // PIXELCANVAS_H
