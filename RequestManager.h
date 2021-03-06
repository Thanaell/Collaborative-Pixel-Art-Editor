#pragma once

#include <qobject.h>

#include <QNetworkAccessManager>
#include <QNetworkReply>

#include <qjsondocument.h>
#include <qjsonobject.h>

class RequestManager : public QObject
{
    Q_OBJECT

public:
    RequestManager();
    void getAllData();
    
public slots:
    void setPixel(const int id, const QString color);
    void addMessage(const QString message);
    void resetChat();
    void resetImage();

private:
    const QString API_PATH = "https://pixel-art.undeb.io";
    QNetworkAccessManager *m_manager;

signals:
    void answerReceived(const QJsonObject rootObject);
};
