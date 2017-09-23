#include <QtGui>

#include "GLWidget.h"
#include "Cylinder.h"
#include "Cuboid.h"
#include "Plane.h"

GLWidget::GLWidget(QWidget *parent) : QGLWidget(parent)
{
	rotationX = 21.0;
	rotationY = -57.0;
	rotationZ = 0.0;
}

GLWidget::~GLWidget()
{
	foreach (Object* o, m_objectList) {
		delete o;
	}
}

void GLWidget::addCylinder()
{
	Object *o1 = new Cylinder(1, 2);
	QColor red(Qt::red);
	QVector3D pos1(1.5, 0, 0);
	o1->setColor(red);
	o1->translate(pos1);
	m_objectList.append(o1);
}

void GLWidget::addCuboid()
{
	Object *o2 = new Cuboid(1, 2, 3);
	QColor green(Qt::green);
	QVector3D pos2(-1, 0, 0);
	o2->setColor(green);
	o2->translate(pos2);
	m_objectList.append(o2);
}

void GLWidget::addPlane()
{
	QVector3D normal(0, 1, 0);
	Object *o3 = new Plane(normal);
	QColor blue(Qt::blue);
	QVector3D pos3(0, 0, 0);
	o3->setColor(blue);
	o3->translate(pos3);
	m_objectList.append(o3);
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
}

void GLWidget::resizeGL(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	GLfloat x = GLfloat(width) / height;
	glFrustum(-x, x, -1.0, 1.0, 4.0, 15.0);
	glMatrixMode(GL_MODELVIEW);
}

void GLWidget::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0, -0.5, -12.0);
	glRotatef(rotationX, 1.0, 0.0, 0.0);
	glRotatef(rotationY, 0.0, 1.0, 0.0);
	glRotatef(rotationZ, 0.0, 0.0, 1.0);

	foreach (Object* o, m_objectList) {
		o->render();
	}
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
	lastPos = event->pos();
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
	GLfloat dx = GLfloat(event->x() - lastPos.x()) / width();
	GLfloat dy = GLfloat(event->y() - lastPos.y()) / height();

	if (event->buttons() & Qt::LeftButton) {
		rotationX += 180 * dx;
		rotationY += 180 * dy;
		updateGL();
	} else if (event->buttons() & Qt::RightButton) {
		rotationX += 180 * dy;
		rotationZ += 180 * dx;
	}
	lastPos = event->pos();
}

void GLWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
	(void)event;
}
