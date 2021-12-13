#include "colorselectorwidget.h"

#include <QDebug>
#include <QDesktopWidget>
#include <QColorDialog>
#include <QPushButton>

ColorSelectorWidget::ColorSelectorWidget(QWidget* parent) :
    QWidget(parent) {
    QDesktopWidget dw;
    this->setMinimumHeight(100); //set min height of color selector
    //transparent icon, change color of button when color is selected
    //    QPushButton *button = new QPushButton;
//    button->setIcon(QIcon(":/icons/..."));
//    button->setIconSize(QSize(65, 65));
}

void ColorSelectorWidget::selectColor() {
    QColor color = QColorDialog::getColor(Qt::white, this );
    if (color.isValid()){
        qDebug() << "Color Choosen : " << color.name();
        //change color of button and update the selected color on pixelCanvas
    }
}
