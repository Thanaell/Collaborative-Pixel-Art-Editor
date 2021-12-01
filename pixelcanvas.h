#ifndef PIXELCANVAS_H
#define PIXELCANVAS_H

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
    // Create a QPixmap object that you will use to store the bitmap the user will draw [on].
    QPixmap pixmap;
//    PixelCanvas(QWidget *parent = 0) : QWidget(parent), m_pressed(0) {
//        m_color = Qt::black;
//        pixmap = new QPixmap("h:/small.png");
//        resize(240, 240);
//    }
//    ~PixelCanvas() { if (pixmap) delete pixmap; }

    //size for pixel art : 64 x 64
    //grid of 64x64 --> how many actual pixels are within the grid of drawing area pixels
    //or qgrid layout with empty widgets
    //see where we are on pixel and where others are on pixel
    //possible fix : zoomable area

protected:
    void paintEvent(QPaintEvent *) override {
        QPainter painter(this);
        painter.drawPixmap(0, 0, m_pixmap->scaled(240, 240));
        painter.drawPixmap(0, 0, *m_pixmap);
    }

    void mousePressEvent(QMouseEvent *e) override {
        if (e->button() == Qt::RightButton)
            m_color = m_color == Qt::black ? Qt::white : Qt::black;
        else {
            m_pressed = 1;
            draw(e);
        }
    }

    void mouseReleaseEvent(QMouseEvent *) override { m_pressed = 0; }
    void mouseMoveEvent(QMouseEvent *e) override { draw(e); }
    void resizeEvent(QResizeEvent *event) override;
private:
    void draw(QMouseEvent *e) {
        if (m_pressed) {
            QPainter painter(m_pixmap);
            painter.setPen(m_color);
            int x = e->pos().x() / 12;
            int y = e->pos().y() / 12;
            painter.drawPoint(x, y);
            repaint();
        }
    }
//private members use m_ before var name
    QColor m_color;
    QPixmap *m_pixmap;
    bool m_pressed;
};

#endif // PIXELCANVAS_H
