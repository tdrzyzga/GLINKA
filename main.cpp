#include "mainwindow/mainwindow.h"
#include "glinka/glinka.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	MainWindow window;

	window.show();

    return a.exec();
}
