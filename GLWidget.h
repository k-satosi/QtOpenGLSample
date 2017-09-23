#pragma once

#include <QColor>
#include <QWidget>
#include <QGLWidget>
#include <QGLFunctions>

class Object;

class GLWidget : public QGLWidget, protected QGLFunctions
{
	Q_OBJECT

public:
	GLWidget(QWidget *parent = 0);
	~GLWidget();

protected:
	void initializeGL();
	void resizeGL(int width, int height);
	void paintGL();
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseDoubleClickEvent(QMouseEvent *event);

private:
	void addCuboid();
	void addCylinder();
	void addPlane();

	QList<Object*> m_objectList;

	GLfloat rotationX;
	GLfloat rotationY;
	GLfloat rotationZ;
	QPoint lastPos;
};
