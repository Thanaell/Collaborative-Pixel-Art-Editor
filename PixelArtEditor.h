#pragma once
#pragma once

#include <QtWidgets/QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class PixelArtEditor : public QMainWindow
{
    Q_OBJECT

public:
    PixelArtEditor(QWidget* parent = Q_NULLPTR);

private:
    QNetworkAccessManager* manager;
    QNetworkRequest request;
public slots:
    void on_pushButton_clicked();
};
