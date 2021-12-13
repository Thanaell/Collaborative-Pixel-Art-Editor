#include "colorselectorwidget.h"
#include "pixelcanvas.h"

#include <QDebug>
#include <QLabel>
#include <QHBoxLayout>
#include <QColorDialog>
#include <QPushButton>

ColorSelectorWidget::ColorSelectorWidget(QWidget* parent, PixelCanvas *pixelCanvas) :
    QWidget(parent)
{
    QWidget* colorSelectorWidget = new QWidget(this);
    m_pixelCanvas = pixelCanvas;

    m_button = new QPushButton;
    m_button->setFixedSize(QSize(62, 62));

    m_colorLabel = new QLabel();


    updateButtonColor(Qt::white);

    QHBoxLayout* colorsArea = new QHBoxLayout(colorSelectorWidget);
    colorsArea->addWidget(m_button);
    colorsArea->addWidget(m_colorLabel);
    this->setMinimumHeight(100); //set min height of color selector
    connect(m_button,SIGNAL(clicked()),this, SLOT(selectColor()));
}

void ColorSelectorWidget::selectColor() {
    QColor color = QColorDialog::getColor(Qt::white, this );
    if (color.isValid()){
        qDebug() << "Color Choosen : " << color.name();
        updateButtonColor(color.name());
        //update the selected color on pixelCanvas
        m_pixelCanvas->changeSelectedColor(color.name());
    }
}

void ColorSelectorWidget::updateButtonColor(QColor color) {
    //update button color
    m_buttonStyle = QString("background-color: %1").arg(color.name());
    m_button->setStyleSheet(m_buttonStyle);

    //update corresponding label
    m_colorLabel->setText(QString("%1").arg(color.name()));
}
