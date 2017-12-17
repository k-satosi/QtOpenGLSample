#include <QtGui>

#include "GLWidget.h"
#include "Cylinder.h"
#include "Cuboid.h"
#include "Plane.h"

static const int MARGIN = 5;

GLWidget::GLWidget(QWidget *parent) : QGLWidget(parent)
{
	for (int i = 0; i < AREA_NUM; i++) {
		rotationX[i] = 21.0;
		rotationY[i] = -57.0;
		rotationZ[i] = 0.0;
	}
}

GLWidget::~GLWidget()
{
	foreach (Object* o, m_objectList) {
		delete o;
	}
}

void GLWidget::addCylinder()
{
	Object *o = new Cylinder(1, 2);
	QColor color(Qt::red);
	QVector3D pos(1.5, 0, 0);
	o->setColor(color);
	o->translate(pos);
	m_objectList << o;
}

void GLWidget::addCuboid()
{
	Object *o = new Cuboid(1, 2, 3);
	QColor color(Qt::green);
	QVector3D pos(-1, 0, 0);
	o->setColor(color);
	o->translate(pos);
	m_objectList << o;
}

void GLWidget::addPlane()
{
	QVector3D normal(0, 1, 0);
	Object *o = new Plane(normal);
	QColor color(Qt::blue);
	QVector3D pos(0, 0, 0);
	o->setColor(color);
	o->translate(pos);
	m_objectList << o;
}

void GLWidget::addPlane2()
{
	QVector3D normal(0, 0, 1);
	Object *o = new Plane(normal);
	QColor color(Qt::yellow);
	QVector3D pos(0, 0, -1.5);
	o->setColor(color);
	o->translate(pos);
	m_objectList << o;
}

void GLWidget::addPlane3()
{
	QVector3D normal(1, 0, 0);
	Object *o = new Plane(normal);
	QColor color(Qt::magenta);
	QVector3D pos(-1.5, 0, 0);
	o->setColor(color);
	o->translate(pos);
	m_objectList << o;
}

void GLWidget::initializeGL()
{
	initializeGLFunctions();

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glEnable(GL_DEPTH_TEST);

	addCylinder();
	addCuboid();
	addPlane();
	addPlane2();
	addPlane3();
}

void GLWidget::resizeGL(int width, int height)
{
	m_windowSize.setWidth(width);
	m_windowSize.setHeight(height);
}

void GLWidget::paintArea(int area)
{
	int width = m_windowSize.width() / AREA_NUM - 2 * MARGIN;
	int height = m_windowSize.height() - 2 * MARGIN;
	int posX = width * area + MARGIN * (area + 1);
	int posY = MARGIN;

	glViewport(posX, posY, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	GLfloat x = GLfloat(width) / height;
#ifdef QT_OPENGL_ES_1
	glFrustumf(-x, x, -1.0, 1.0, 4.0, 15.0);
#else
	glFrustum(-x, x, -1.0, 1.0, 4.0, 15.0);
#endif

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0, -0.5, -12.0);
	glRotatef(rotationX[area], 1.0, 0.0, 0.0);
	glRotatef(rotationY[area], 0.0, 1.0, 0.0);
	glRotatef(rotationZ[area], 0.0, 0.0, 1.0);

	foreach (Object* o, m_objectList) {
		o->render();
	}
}

void GLWidget::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (int i = 0; i < AREA_NUM; i++) {
		paintArea(i);
	}
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
	lastPos = event->pos();
}

int GLWidget::getPointedArea(int x, int y)
{
	(void)y;

	int area = 0;
	for (int i = 1; i < AREA_NUM; i++) {
		if (x > (m_windowSize.width() / AREA_NUM) * i) {
			area = i;
		}
	}

	return area;
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
	GLfloat dx = GLfloat(event->x() - lastPos.x()) / width();
	GLfloat dy = GLfloat(event->y() - lastPos.y()) / height();

	int area = getPointedArea(event->x(), event->y());

	if (event->buttons() & Qt::LeftButton) {
		rotationX[area] += 180 * dx;
		rotationY[area] += 180 * dy;
		updateGL();
	} else if (event->buttons() & Qt::RightButton) {
		rotationX[area] += 180 * dy;
		rotationZ[area] += 180 * dx;
	}
	lastPos = event->pos();
}

void GLWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
	(void)event;
}
