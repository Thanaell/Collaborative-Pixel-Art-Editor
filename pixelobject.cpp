#include "pixelobject.h"

#include <QPainterPath>
#include <QPoint>
#include <QColor>
#include <QPainter>

#include <QDebug>

PixelObject::PixelObject(int pixelNum, QColor pixelColor, QColor pixelOutlineColor, int x, int  y)
{
    this->m_pixelNum = pixelNum;
    this->m_pixelColor = pixelColor;
    this->m_pixelOutlineColor = pixelOutlineColor;
    this->m_x = x;
    this->m_y = y;
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

int PixelObject::getX() {
    return this->m_x;
}

int PixelObject::getY() {
    return this->m_y;
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

void PixelObject::setX(int x) {
    m_x = x;
}

void PixelObject::setY(int y) {
    m_y = y;
}
