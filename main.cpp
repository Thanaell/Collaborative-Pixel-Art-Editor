#include "PixelArtEditor.h"
#include <QtWidgets/QApplication>



int main(int argc, char** argv)
{
	QApplication app(argc, argv);
	PixelArtEditor editor;
	editor.show();
	return app.exec();
}