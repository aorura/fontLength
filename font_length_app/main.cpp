#include <QApplication>

#include "FontDialog.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	FontDialog dialog;
	//dialog.resize(600, 400);
	dialog.show();

	return app.exec();
}