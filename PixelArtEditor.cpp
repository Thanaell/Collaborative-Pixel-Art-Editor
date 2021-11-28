#include "PixelArtEditor.h"

#include "pixelcanvas.h"

PixelArtEditor::PixelArtEditor(QWidget* parent) :
    QMainWindow(parent),
    m_pollingTimer(new QTimer(this)),
    m_requestManager(new RequestManager())
//    pixelcanvas(new PixelCanvas(this))
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
}

void PixelArtEditor::pollAllData()
{
    m_requestManager->getAllData();
}

void PixelArtEditor::refreshAllData(const QJsonObject data)
{
    // TODO handle refresh widgets using the reply's data
}
