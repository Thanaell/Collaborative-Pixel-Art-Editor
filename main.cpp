#include "PixelArtEditor.h"
#include <QtWidgets/QApplication>

int main(int argc, char** argv)
{
	QApplication app(argc, argv);
	PixelArtEditor editor;

	QFile file("./Style/customStyle.qss");
	file.open(QFile::ReadOnly);
	QString styleSheet{ QString(file.readAll()) };
	app.setStyleSheet(styleSheet);

	editor.show();
	return app.exec();
}

