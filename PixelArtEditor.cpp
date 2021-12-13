#include "PixelArtEditor.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>

PixelArtEditor::PixelArtEditor(QWidget* parent) :
    QMainWindow(parent),
    m_pollingTimer(new QTimer(this)),
    m_requestManager(new RequestManager()),
    m_pixelcanvas(new PixelCanvas(this, m_requestManager)),
    m_optionswidget(new OptionsWidget(this, m_pixelcanvas)),
    m_chatWidget(new ChatWidget(this))
{
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    
    QHBoxLayout* mainLayout = new QHBoxLayout(centralWidget);
    QVBoxLayout *rightLayout = new QVBoxLayout();
    mainLayout->addWidget(m_pixelcanvas);
    rightLayout->addWidget(m_optionswidget);
    rightLayout->addWidget(m_chatWidget);
    mainLayout->addLayout(rightLayout);
    QObject::connect(m_chatWidget, &ChatWidget::messageSent, m_requestManager, &RequestManager::addMessage);



    connect(m_pollingTimer, &QTimer::timeout, this, &PixelArtEditor::pollAllData);
    m_pollingTimer->start(POLLING_COOLDOWN);

    // Bind the getAllData reply to the refreshAllData slot
    QObject::connect(
        m_requestManager,
        &RequestManager::answerReceived,
        this,
        &PixelArtEditor::refreshAllData
    );

    // Test for setting pixel
    //m_requestManager->setPixel(2, "F74521");
}

//called 3 times a second -> POLLING_COOLDOWN
void PixelArtEditor::pollAllData()
{
    m_requestManager->getAllData();
}

void PixelArtEditor::refreshAllData(const QJsonObject data)
{
    // TODO handle refresh widgets using the reply's data
    //JSON object with pixels and chat, and last 10 edited pixels --> do what is needed to refresh display
    //Request Manager handles the requests
    QVariantMap dataMap = data.toVariantMap();
    auto chat = dataMap["chat"].toMap()["messages"];
    auto image = dataMap["image"];
    auto lastPixels = dataMap["lastPixelsEdited"];

    std::vector<QString> messages;
    for (auto message : chat.toList()) {
        //qDebug()<<message;
        messages.push_back(message.toString());
    }
    m_chatWidget->setMessages(messages);

    
}

//override closeEvent
//closeEvent will prompt the user with a message box
// YES will quit the application
// NO will continue the application
void PixelArtEditor::closeEvent(QCloseEvent *event)
{
    qDebug("quit file");

    // Display a message box : Yes or No, Yes = QUIT and No = stay in application
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Urgent message", "Quit?", QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        event->accept();
    } else {
        event->ignore();
    }
}
