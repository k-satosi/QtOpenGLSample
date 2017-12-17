#pragma once

#include <QGLWidget>
#include <QGLFunctions>

#define AREA_NUM 2

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
	void addPlane2();
	void addPlane3();
	void paintArea(int area);
	int getPointedArea(int x, int y);

	QList<Object*> m_objectList;

	GLfloat rotationX[AREA_NUM];
	GLfloat rotationY[AREA_NUM];
	GLfloat rotationZ[AREA_NUM];
	QPoint lastPos;

	QSize m_windowSize;
};
