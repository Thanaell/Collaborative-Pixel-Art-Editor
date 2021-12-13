#ifndef COLORSELECTORWIDGET_H
#define COLORSELECTORWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QColorDialog>

class ColorSelectorWidget : public QWidget
{
    Q_OBJECT
public:
    ColorSelectorWidget(QWidget* parent = nullptr);
    void selectColor();
private:
    QVBoxLayout *m_colorsLayout;
};

#endif // COLORSELECTORWIDGET_H
