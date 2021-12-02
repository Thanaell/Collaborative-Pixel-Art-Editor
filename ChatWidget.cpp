#include "ChatWidget.h"
#include "QVBoxLayout"
#include "QScrollArea"
#include "QLabel"

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
    QWidget* messagesWidget = new QWidget(this);
    m_messagesLayout = new QVBoxLayout(messagesWidget);
    m_messagesLayout->setContentsMargins(0, 0, 0, 0);
    m_messagesLayout->setSpacing(2);
    auto scrollArea = new QScrollArea(this);
    scrollArea->setMinimumSize(200,400);
    
    scrollArea->setWidget(messagesWidget);
    scrollArea->setWidgetResizable(true);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    
}
void ChatWidget::setMessages(std::vector<QString> messages) {

    //TODO : better to only go from last received
    clearLayout(*m_messagesLayout);
    for (auto message : messages) {
        m_messagesLayout->addWidget(new QLabel(message, this));
    }
}