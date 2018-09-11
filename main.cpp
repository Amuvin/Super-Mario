#include "stdafx.h"
#include "SuperMario.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	SuperMario w;
	w.show();
	return a.exec();
}