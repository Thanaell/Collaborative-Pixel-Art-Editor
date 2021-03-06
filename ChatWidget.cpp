#include "ChatWidget.h"
#include "QVBoxLayout"
#include "QScrollArea"
#include "QLabel"
#include "qlineedit.h"
#include <qpushbutton.h>
#include <qscrollbar.h>

void hideAllWidgets(QLayout& layout)
{
    for (int i = 0; i < layout.count(); ++i) {
        auto item = layout.itemAt(i);
        if (item->layout()) hideAllWidgets(*item->layout());
        if (item->widget()) item->widget()->hide();
    }
}

void clearLayout(QLayout& layout)
{
    hideAllWidgets(layout);

    QLayoutItem* item;
    while ((item = layout.takeAt(0)))
    {
        // If item is layout itself, we should clear that layout as well.
        if (item->layout()) {
            clearLayout(*item->layout());

            // After clearing layout, we delete it.
            item->layout()->deleteLater();
        }
        else if (item->widget()) {
            item->widget()->deleteLater();

            //delete item->widget();
        }
        else if (item->spacerItem())
        {
            delete item->spacerItem();
        }

        delete item;

    }
}
ChatWidget::ChatWidget(QWidget* parent) : 
    QWidget(parent) {

    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    QWidget* messagesWidget = new QWidget(this);
    QVBoxLayout* mainMessagesLayout = new QVBoxLayout(messagesWidget);
    m_messagesLayout = new QVBoxLayout(this);
    m_messagesLayout->setSpacing(10);
    mainMessagesLayout->addLayout(m_messagesLayout, Qt::AlignTop);
    mainMessagesLayout->addStretch();
    m_scrollArea = new QScrollArea(this);
    m_scrollArea->setMinimumSize(200,400);    
    m_scrollArea->setWidget(messagesWidget);
    m_scrollArea->setWidgetResizable(true);
    m_scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    QObject::connect(m_scrollArea->verticalScrollBar(), &QScrollBar::rangeChanged, [this](int min, int max) {
        (void)min;
        if (max > m_scrollBarMax) m_scrollArea->verticalScrollBar()->setValue(max);
        m_scrollBarMax = max;
        }
    );


    QWidget* writeMessageWidget = new QWidget(this);
    QHBoxLayout* writeMessageLayout = new QHBoxLayout(writeMessageWidget);
    QLineEdit* writeArea = new QLineEdit();
    QPushButton* validateButton = new QPushButton("SEND");
    validateButton->setMinimumSize(100, 50);
    writeMessageLayout->addWidget(writeArea);
    writeMessageLayout->addWidget(validateButton);
    QObject::connect(validateButton, &QPushButton::clicked,this, [this,writeArea](){
        //m_messagesLayout->addWidget(new QLabel(writeArea->text(), this)); //locally adding message
        emit messageSent(writeArea->text());
        writeArea->setText("");
        });
    
    mainLayout->addWidget(m_scrollArea);
    mainLayout->addWidget(writeMessageWidget);

}
void ChatWidget::setMessages(std::vector<QString> messages) {
    clearLayout(*m_messagesLayout);
    for (auto message : messages) {
        auto messageLabel = new QLabel("\n " +message + "\n", this);
        messageLabel->setAlignment(Qt::AlignVCenter);
        m_messagesLayout->addWidget(messageLabel);
    }
}