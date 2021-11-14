#include "PixelArtEditor.h"
#include <QPushButton>
#include "iostream"

PixelArtEditor::PixelArtEditor(QWidget* parent) :
    QMainWindow(parent)
{
    QWidget* centralWidget = new QWidget();
    setCentralWidget(centralWidget);
    QPushButton* button = new QPushButton(centralWidget);
    QObject::connect(button, &QPushButton::clicked, this, &PixelArtEditor::on_pushButton_clicked);

    manager = new QNetworkAccessManager();
    QObject::connect(manager, &QNetworkAccessManager::finished,
        this, [=](QNetworkReply* reply) {
            if (reply->error()) {
                qDebug() << reply->errorString();
                return;
            }

            QString answer = reply->readAll();

            qDebug() << answer;
        }
    );
}

void PixelArtEditor::on_pushButton_clicked()
{
    std::cout<<"hello";
    request.setUrl(QUrl("http://127.0.0.1:8080/chat"));
    manager->deleteResource(request);
}
