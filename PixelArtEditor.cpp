#include "PixelArtEditor.h"

PixelArtEditor::PixelArtEditor(QWidget* parent) :
    QMainWindow(parent),
    m_pollingTimer(new QTimer(this)),
    m_requestManager(new RequestManager()),
    m_pixelcanvas(new PixelCanvas(this))
{
    QWidget *centralWidget = new QWidget();
    setCentralWidget(centralWidget);

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
    //m_requestManager->setPixel(3, 2, "F74521");
}

void PixelArtEditor::pollAllData()
{
    m_requestManager->getAllData();
}

void PixelArtEditor::refreshAllData(const QJsonObject data)
{
    // TODO handle refresh widgets using the reply's data
}
