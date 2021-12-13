#include "pixelobject.h"

#include <QPainterPath>
#include <QPoint>
#include <QColor>
#include <QPainter>

#include <QDebug>

PixelObject::PixelObject(int pixelNum, QColor pixelColor, QColor pixelOutlineColor)
{
    this->m_pixelNum = pixelNum;
    this->m_pixelColor = pixelColor;
    this->m_pixelOutlineColor = pixelOutlineColor;
}

int PixelObject::getPixelNum() {
    return this->m_pixelNum;
}

QColor PixelObject::getPixelColor(){
    return this->m_pixelColor;
}

QColor PixelObject::getPixelOutlineColor(){
    return this->m_pixelOutlineColor;
}

void PixelObject::setPixelNum(int n) {
    m_pixelNum = n;
}

void PixelObject::setPixelColor(QColor c){
    m_pixelColor = c;
}

void PixelObject::setPixelOutlineColor(QColor o){
    m_pixelOutlineColor = o;
}
