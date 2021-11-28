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
    QPixmap m_pixmap;
//    PixelCanvas(QWidget *parent = 0) : QWidget(parent), pressed(0) {
//        color = Qt::black;
//        pixmap = new QPixmap("h:/small.png");
//        resize(240, 240);
//    }
//    ~PixelCanvas() { if (pixmap) delete pixmap; }

protected:
    void paintEvent(QPaintEvent *) override {
        QPainter painter(this);
        painter.drawPixmap(0, 0, pixmap->scaled(240, 240));
        painter.drawPixmap(0, 0, *pixmap);
    }

    void mousePressEvent(QMouseEvent *e) override {
        if (e->button() == Qt::RightButton)
            color = color == Qt::black ? Qt::white : Qt::black;
        else {
            pressed = 1;
            draw(e);
        }
    }

    void mouseReleaseEvent(QMouseEvent *) override { pressed = 0; }
    void mouseMoveEvent(QMouseEvent *e) override { draw(e); }
    void resizeEvent(QResizeEvent *event) override;
private:
    void draw(QMouseEvent *e) {
        if (pressed) {
            QPainter painter(pixmap);
            painter.setPen(color);
            int x = e->pos().x() / 12;
            int y = e->pos().y() / 12;
            painter.drawPoint(x, y);
            repaint();
        }
    }

    QColor color;
    QPixmap *pixmap;
    bool pressed;
};

#endif // PIXELCANVAS_H
