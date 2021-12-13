#ifndef COLORSELECTORWIDGET_H
#define COLORSELECTORWIDGET_H

#include "pixelcanvas.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QColorDialog>

class ColorSelectorWidget : public QWidget
{
    Q_OBJECT
public:
    ColorSelectorWidget(QWidget* parent = nullptr);
    PixelCanvas *pixelCanvas;
private slots:
    void selectColor();
private:
    QVBoxLayout *m_colorsLayout;
    QString m_buttonStyle;
    QPushButton *button;
    QLabel *colorLabel;
    void updateButtonColor(QColor);
};

#endif // COLORSELECTORWIDGET_H
