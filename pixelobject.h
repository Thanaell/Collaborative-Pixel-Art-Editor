#ifndef PIXELOBJECT_H
#define PIXELOBJECT_H

#include <QObject>
#include <QColor>

class PixelObject
{
public:
    PixelObject(int, QColor, QColor);
    int getPixelNum();
    QColor getPixelColor();
    QColor getPixelOutlineColor();
    void setPixelNum(int);
    void setPixelColor(QColor);
    void setPixelOutlineColor(QColor);

private:
    int m_pixelNum;
    QColor m_pixelColor;
    QColor m_pixelOutlineColor;

};

#endif // PIXELOBJECT_H
