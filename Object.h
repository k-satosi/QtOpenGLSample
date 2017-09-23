#pragma once

#include <QList>
#include <QGLWidget>
#include <QGLFunctions>
#include <QVector3D>

struct Vertex
{
	GLfloat v[3];
	GLfloat n[3];
};

class Object : protected QGLFunctions
{
public:
	Object() {
		initializeGLFunctions();
		memset(m_pos, 0, sizeof(m_pos));
		m_scale[0] = 1;
		m_scale[1] = 1;
		m_scale[2] = 1;
	}

	virtual ~Object() {}

	void setColor(QColor &color) {
		m_color[0] = (GLfloat)color.redF();
		m_color[1] = (GLfloat)color.greenF();
		m_color[2] = (GLfloat)color.blueF();
	}
	void render() {
		glPushMatrix();
		glTranslatef(m_pos[0], m_pos[1], m_pos[2]);
		glScalef(m_scale[0], m_scale[1], m_scale[2]);
		draw();
		glPopMatrix();
	}

	void translate(QVector3D &pos) {
		m_pos[0] = (GLfloat)pos.x();
		m_pos[1] = (GLfloat)pos.y();
		m_pos[2] = (GLfloat)pos.z();
	}

protected:
	virtual void draw() = 0;

	QVector<Vertex> m_vertexArray;
	QVector<GLuint> m_indexArray;

	GLfloat m_pos[3];
	GLfloat m_scale[3];
	GLfloat m_color[3];
#ifdef _USE_VBO
	GLuint m_vboVertex;
	GLuint m_vboIndex;
#endif
};
