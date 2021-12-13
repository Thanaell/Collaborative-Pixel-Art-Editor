#ifndef OPTIONSWIDGET_H
#define OPTIONSWIDGET_H

#include "pixelcanvas.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QColorDialog>

class OptionsWidget : public QWidget
{
    Q_OBJECT
public:
    OptionsWidget(QWidget* parent = nullptr, PixelCanvas *pixelCanvas = nullptr);
private slots:
    void selectColor();
    void eraseColor();
private:
    QVBoxLayout *m_colorsLayout;
    QString m_colorButtonStyle;
    QPushButton *m_colorButton;
    QString m_eraseButtonStyle;
    QPushButton *m_eraseButton;
    QLabel *m_colorLabel;
    void updateButtonColor(QColor);
    QColor m_lastSelectedColor;
    PixelCanvas *m_pixelCanvas;
};

#endif // OPTIONSWIDGET_H
