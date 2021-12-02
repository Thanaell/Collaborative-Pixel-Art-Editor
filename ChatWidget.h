#pragma once
#include <qwidget.h>
#include <QVBoxLayout>
class ChatWidget :public QWidget
{
	Q_OBJECT
public:
	ChatWidget(QWidget* parent = nullptr);
	void setMessages(std::vector<QString>);
private:
	QVBoxLayout *m_messagesLayout;

signals:
	void messageSent(QString);
};

