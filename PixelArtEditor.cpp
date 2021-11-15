#include "PixelArtEditor.h"
#include <QPushButton>
#include "iostream"
#include <qjsondocument.h>
#include <qjsonobject.h>

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

            //QString answer = reply->readAll();
            //qDebug() << answer;

            //QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
            //QJsonObject rootObj = document.object();
            //qDebug() << rootObj;

            
        }
    );
}

void PixelArtEditor::on_pushButton_clicked()
{
    std::cout<<"hello";

    /*
    QJsonObject messageObject;
    messageObject["content"] = "This is a chat message :)";

    QJsonDocument messageDocument(messageObject);
    QByteArray jsonData = messageDocument.toJson();

    request.setUrl(QUrl("http://127.0.0.1:8080/chat"));
    manager->post(request, jsonData);
    */

    QJsonObject pixelObject;
    pixelObject["x"] = 1;
    pixelObject["y"] = 0;
    pixelObject["color"] = "112255";

    QJsonDocument pixelDocument(pixelObject);
    QByteArray jsonData = pixelDocument.toJson();

    request.setUrl(QUrl("http://127.0.0.1:8080/pixel"));
    manager->post(request, jsonData);
}
