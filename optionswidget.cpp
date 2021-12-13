#include "optionswidget.h"
#include "pixelcanvas.h"

#include <QDebug>
#include <QLabel>
#include <QHBoxLayout>
#include <QColorDialog>
#include <QPushButton>
#include <QPalette>
#include <QMessageBox>

OptionsWidget::OptionsWidget(QWidget* parent, PixelCanvas *pixelCanvas) :
    QWidget(parent)
{
    QWidget* colorSelectorWidget = new QWidget(this);
    m_pixelCanvas = pixelCanvas;

    m_colorButton = new QPushButton;
    m_colorButton->setFixedSize(QSize(62, 62));

    m_colorLabel = new QLabel();

    m_eraseButton = new QPushButton;
    m_eraseButton->setIcon(QIcon(":/Images/eraser.png"));
    m_eraseButton->setIconSize(QSize(62, 62));

    m_saveButton = new QPushButton;
    m_saveButton->setIcon(QIcon(":/Images/save.png"));
    m_saveButton->setIconSize(QSize(62, 62));


    updateButtonColor(Qt::black);

    QHBoxLayout* colorsArea = new QHBoxLayout(colorSelectorWidget);
    colorsArea->addWidget(m_colorButton);
    colorsArea->addWidget(m_colorLabel);
    colorsArea->addSpacing(15);
    colorsArea->addWidget(m_eraseButton);
    colorsArea->addSpacing(40);
    colorsArea->addWidget(m_saveButton);
    this->setMinimumHeight(100); //set min height of color selector

    connect(m_colorButton,SIGNAL(clicked()),this, SLOT(selectColor()));
    connect(m_eraseButton,SIGNAL(clicked()),this, SLOT(eraseColor()));
    connect(m_saveButton,SIGNAL(clicked()),this, SLOT(saveImage()));
}

void OptionsWidget::selectColor() {
    QColor color = QColorDialog::getColor(Qt::white, this );
    m_lastSelectedColor = color;
    if (color.isValid()){
        updateButtonColor(color.name());
        //update the selected color on pixelCanvas
        m_pixelCanvas->changeSelectedColor(color.name());
    }
}

void OptionsWidget::eraseColor() {
    QColor highlight = Qt::yellow;
    QColor currentHighlight = m_eraseButton->palette().color(QPalette::Button).name();
    if(highlight != currentHighlight) {
        QColor color = Qt::white;
        m_pixelCanvas->changeSelectedColor(color.name());

        //highlight erase button
        m_eraseButtonStyle = QString("background-color: %1").arg(highlight.name());
        m_eraseButton->setStyleSheet(m_eraseButtonStyle);
    } else {
        //turn back to no highlight
        m_eraseButtonStyle = QString("background-color: %1").arg("rgb(0.0823529, 0.298039, 0.47451)");
        m_eraseButton->setStyleSheet(m_eraseButtonStyle);

        //reset painter to last selected color
        m_pixelCanvas->changeSelectedColor(m_lastSelectedColor.name());
    }
}

void OptionsWidget::saveImage() {
    qDebug() << "save image now";
    QFile file("pixelArt.png");
    file.open(QIODevice::WriteOnly);
    m_pixelCanvas->grab().save(&file, "PNG");

    // Display a message box : advise user the image was saved
    QMessageBox::information(this, "Image saved", "'pixelArt.png' was saved.", QMessageBox::Ok);
}

void OptionsWidget::updateButtonColor(QColor color) {
    //update button color
    m_colorButtonStyle = QString("background-color: %1").arg(color.name());
    m_colorButton->setStyleSheet(m_colorButtonStyle);

    //update corresponding label
    m_colorLabel->setText(QString("%1").arg(color.name()));

    //make sure erase button is not highlighted anymore
    m_eraseButtonStyle = QString("background-color: %1").arg("rgb(0.0823529, 0.298039, 0.47451)");
    m_eraseButton->setStyleSheet(m_eraseButtonStyle);
}
