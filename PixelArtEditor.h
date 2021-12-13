#pragma once
#pragma once

#include <QtWidgets/QMainWindow>
#include <qtimer.h>

#include "pixelcanvas.h"
#include "colorselectorwidget.h"
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
    ColorSelectorWidget *m_colorselectorwidget;
    ChatWidget* m_chatWidget;

public slots:
    void pollAllData();
    void refreshAllData(const QJsonObject data);
};
