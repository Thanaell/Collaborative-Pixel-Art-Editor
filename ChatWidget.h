#pragma once
#include <qwidget.h>
#include <QVBoxLayout>
#include <QScrollArea>
class ChatWidget :public QWidget
{
	Q_OBJECT
public:
	ChatWidget(QWidget* parent = nullptr);
	void setMessages(std::vector<QString>);
private:
	QVBoxLayout *m_messagesLayout;
	QScrollArea* m_scrollArea;

signals:
	void messageSent(QString);
};

