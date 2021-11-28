#include "RequestManager.h"

RequestManager::RequestManager() : m_manager(new QNetworkAccessManager())
{
    // Nothing to do here :)
}

void RequestManager::getAllData()
{
    QNetworkRequest request;
    request.setUrl(QUrl(API_PATH + "/all"));

    QNetworkReply *reply = m_manager->get(request);

    QObject::connect(reply, &QNetworkReply::finished, [this, reply]() {
        if (reply->error()) {
            qDebug() << reply->errorString();
            return;
        }

        QJsonDocument responseDocument = QJsonDocument::fromJson(reply->readAll());
        QJsonObject rootObject = responseDocument.object();
        
        emit answerReceived(rootObject);
    });
}

/*
Expects a JSON object with the following keys / values
- "x" : int
- "y" : int
- "color" : string (RGB color in hexadecimal)
*/
void RequestManager::setPixel(const QJsonObject pixelObject)
{
    QJsonDocument pixelDocument(pixelObject);
    QByteArray jsonData = pixelDocument.toJson();

    QNetworkRequest request;
    request.setUrl(QUrl(API_PATH + "/pixel"));

    QNetworkReply *reply = m_manager->post(request, jsonData);

    QObject::connect(reply, &QNetworkReply::finished, [reply]() {
        if (reply->error()) {
            qDebug() << reply->errorString();
            return;
        }
    });
}

// Expects a JSON object with a string set for "content" key
void RequestManager::addMessage(const QJsonObject messageObject)
{
    QJsonDocument messageDocument(messageObject);
    QByteArray jsonData = messageDocument.toJson();

    QNetworkRequest request;
    request.setUrl(QUrl(API_PATH + "/chat"));

    QNetworkReply *reply = m_manager->post(request, jsonData);

    QObject::connect(reply, &QNetworkReply::finished,  [reply]() {
        if (reply->error()) {
            qDebug() << reply->errorString();
            return;
        }
    });
}

void RequestManager::resetChat()
{
    QNetworkRequest request;
    request.setUrl(QUrl(API_PATH + "/chat"));

    QNetworkReply *reply = m_manager->deleteResource(request);

    QObject::connect(reply, &QNetworkReply::finished, [reply]() {
        if (reply->error()) {
            qDebug() << reply->errorString();
            return;
        }
    });
}

void RequestManager::resetImage()
{
    QNetworkRequest request;
    request.setUrl(QUrl(API_PATH + "/image"));

    QNetworkReply *reply = m_manager->deleteResource(request);

    QObject::connect(reply, &QNetworkReply::finished, [reply]() {
        if (reply->error()) {
            qDebug() << reply->errorString();
            return;
        }
    });
}
