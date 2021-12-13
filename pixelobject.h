#ifndef PIXELOBJECT_H
#define PIXELOBJECT_H

#include <QObject>
#include <QColor>

class PixelObject
{
public:
    PixelObject(int, QColor, QColor, int, int);
    int getPixelNum();
    QColor getPixelColor();
    QColor getPixelOutlineColor();
    int getX();
    int getY();
    void setPixelNum(int);
    void setPixelColor(QColor);
    void setPixelOutlineColor(QColor);
    void setX(int);
    void setY(int);

private:
    int m_pixelNum;
    QColor m_pixelColor;
    QColor m_pixelOutlineColor;
    int m_x;
    int m_y;

};

#endif // PIXELOBJECT_H
