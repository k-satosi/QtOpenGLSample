#pragma once

#include <QGLFunctions>
#include <QVector3D>
#include <QMatrix4x4>
#include <QQuaternion>
#include <QtCore/qmath.h>

struct Vertex
{
	GLfloat v[3];
	GLfloat n[3];
};

class Object : protected QGLFunctions
{
public:
	Object() : m_scale(QVector3D(1, 1, 1)) {
		initializeGLFunctions();
	}

	virtual ~Object() {}

	void setColor(const QColor &color) {
		m_color = color;
	}

	void render() {
		GLfloat color[] = {
			(GLfloat)m_color.redF(),
			(GLfloat)m_color.greenF(),
			(GLfloat)m_color.blueF()
		};
		glLightfv(GL_LIGHT0, GL_DIFFUSE, color);
		glPushMatrix();
		QMatrix4x4 matrix;
		matrix.translate(m_pos);
		matrix.rotate(m_quaternion);
		matrix.scale(m_scale);
		glMultMatrix(matrix.data());
		draw();
		glPopMatrix();
	}

	void scale(const QVector3D &s) {
		m_scale = s;
	}

	void translate(const QVector3D &pos) {
		m_pos = pos;
	}

	void rotate(const QVector3D &vec, float angle) {
		QQuaternion q = QQuaternion::fromAxisAndAngle(vec, angle);
		m_quaternion = q * m_quaternion;
	}

	void rotateX(qreal angle) {
		QVector3D vec(1, 0, 0);
		rotate(vec, angle);
	}

	void rotateY(qreal angle) {
		QVector3D vec(0, 1, 0);
		rotate(vec, angle);
	}

	void rotateZ(qreal angle) {
		QVector3D vec(0, 0, 1);
		rotate(vec, angle);
	}

protected:
	virtual void draw() = 0;

	QVector<Vertex> m_vertexArray;
	QVector<GLuint> m_indexArray;
#ifdef _USE_VBO
	GLuint m_vboVertex;
	GLuint m_vboIndex;
#endif

private:
	inline void glMultMatrix(const GLdouble *matrix) {
		glMultMatrixd(matrix);
	}

	inline void glMultMatrix(const GLfloat *matrix) {
		glMultMatrixf(matrix);
	}

	QVector3D m_pos;
	QVector3D m_scale;
	QColor m_color;
	QQuaternion m_quaternion;
};
