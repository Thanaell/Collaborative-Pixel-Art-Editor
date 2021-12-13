#include "colorselectorwidget.h"
#include "pixelcanvas.h"

#include <QDebug>
#include <QLabel>
#include <QHBoxLayout>
#include <QColorDialog>
#include <QPushButton>

ColorSelectorWidget::ColorSelectorWidget(QWidget* parent) :
    QWidget(parent)
{
    QWidget* colorSelectorWidget = new QWidget(this);

    button = new QPushButton;
    button->setFixedSize(QSize(62, 62));

    colorLabel = new QLabel();


    updateButtonColor(Qt::white);

    QHBoxLayout* colorsArea = new QHBoxLayout(colorSelectorWidget);
    colorsArea->addWidget(button);
    colorsArea->addWidget(colorLabel);
    this->setMinimumHeight(100); //set min height of color selector

    connect(button,SIGNAL(clicked()),this,SLOT(selectColor()));
}

void ColorSelectorWidget::selectColor() {
    QColor color = QColorDialog::getColor(Qt::white, this );
    if (color.isValid()){
        qDebug() << "Color Choosen : " << color.name();
        updateButtonColor(color.name());
        //update the selected color on pixelCanvas
        pixelCanvas->changeSelectedColor(color);
    }
}

void ColorSelectorWidget::updateButtonColor(QColor color) {
    //update button color
    m_buttonStyle = QString("background-color: %1").arg(color.name());
    button->setStyleSheet(m_buttonStyle);

    //update corresponding label
    colorLabel->setText(QString("%1").arg(color.name()));
}
