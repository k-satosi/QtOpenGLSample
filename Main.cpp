#include <QApplication>
#include <QDebug>
#include "GLWidget.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	if (!QGLFormat::hasOpenGL()) {
		qDebug() << "This system has no OpenGL support";
		return 1;
	}

	GLWidget w;
	w.setWindowTitle(QObject::tr("Qt OpenGL Sample"));
	w.resize(1200, 600);
	w.show();

	return app.exec();
}
