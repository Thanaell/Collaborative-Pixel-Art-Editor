#pragma once
#pragma once

#include <QtWidgets/QMainWindow>
#include <qtimer.h>

#include "pixelcanvas.h"
#include "optionswidget.h"
#include "ChatWidget.h"
#include "RequestManager.h"

class PixelArtEditor : public QMainWindow
{
    Q_OBJECT

public:
    PixelArtEditor(QWidget *parent = Q_NULLPTR);

private:
    const int POLLING_COOLDOWN = 300;

    QTimer *m_pollingTimer;
    RequestManager *m_requestManager;
    PixelCanvas *m_pixelcanvas;
    OptionsWidget *m_optionswidget;
    ChatWidget* m_chatWidget;

protected:
    void closeEvent(QCloseEvent *event) override;

public slots:
    void pollAllData();
    void refreshAllData(const QJsonObject data);
};
