#include "ChatWidget.h"
#include "QVBoxLayout"
#include "QScrollArea"
#include "QLabel"
#include "qlineedit.h"
#include <qpushbutton.h>

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
    m_messagesLayout->setContentsMargins(0, 0, 0, 0);
    m_messagesLayout->setSpacing(2);
    mainMessagesLayout->addLayout(m_messagesLayout);
    mainMessagesLayout->addStretch();
    auto scrollArea = new QScrollArea(this);
    scrollArea->setMinimumSize(200,400);    
    scrollArea->setWidget(messagesWidget);
    scrollArea->setWidgetResizable(true);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    QWidget* writeMessageWidget = new QWidget(this);
    QHBoxLayout* writeMessageLayout = new QHBoxLayout(writeMessageWidget);
    QLineEdit* writeArea = new QLineEdit();
    QPushButton* validateButton = new QPushButton("SEND");
    writeMessageLayout->addWidget(writeArea);
    writeMessageLayout->addWidget(validateButton);
    QObject::connect(validateButton, &QPushButton::clicked,this, [this,writeArea](){
        emit messageSent(writeArea->text());
        writeArea->setText("");
        });
    
    mainLayout->addWidget(scrollArea);
    mainLayout->addWidget(writeMessageWidget);

}
void ChatWidget::setMessages(std::vector<QString> messages) {

    //TODO : better to only go from last received
    clearLayout(*m_messagesLayout);
    for (auto message : messages) {
        m_messagesLayout->addWidget(new QLabel(message, this));
    }
}