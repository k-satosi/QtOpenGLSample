#include "Cylinder.h"

Cylinder::Cylinder(qreal radius, qreal height, int step) :
	m_step(step)
{
	scale(QVector3D(radius, height, radius));

	// create tube
	int index = 0;
	for (int deg = 0; deg <= 360; deg += m_step) {
		GLfloat rad = (GLfloat)deg * M_PI / 180;
		Vertex v1 = { { (GLfloat)qCos(rad),
						1,
						(GLfloat)qSin(rad) },
					  { (GLfloat)qCos(rad),
						0,
						(GLfloat)qSin(rad) } };
		m_vertexArray << v1;
		m_indexArray << index++;

		Vertex v2 = { { (GLfloat)qCos(rad),
						0,
						(GLfloat)qSin(rad) },
					  { (GLfloat)qCos(rad),
						0,
						(GLfloat)qSin(rad) } };
		m_vertexArray << v2;
		m_indexArray << index++;
	}

	// create top disk
	Vertex v_start = { { 0, 1, 0 },
					   { 0, 1, 0 } };
	m_vertexArray << v_start;
	m_indexArray << index++;
	for (int deg = 0; deg <= 360; deg += m_step) {
		GLfloat rad = (GLfloat)deg * M_PI / 180;
		Vertex v1 = { { (GLfloat)qCos(rad),
						1,
						(GLfloat)qSin(rad) },
					  { 0, 1, 0 } };
		m_vertexArray << v1;
		m_indexArray << index++;
	}

	// create bottom disk
	Vertex v_end = { { 0, 0, 0 },
					 { 0, -1, 0 } };
	m_vertexArray << v_end;
	m_indexArray << index++;
	for (int deg = 0; deg <= 360; deg += m_step) {
		GLfloat rad = (GLfloat)deg * M_PI / 180;
		Vertex v2 = { { (GLfloat)qCos(rad),
						0,
						(GLfloat)qSin(rad) },
					  { 0, -1, 0 } };
		m_vertexArray << v2;
		m_indexArray << index++;
	}

#ifdef _USE_VBO
	glGenBuffers(1, &m_vboVertex);
	glBindBuffer(GL_ARRAY_BUFFER, m_vboVertex);
	glBufferData(GL_ARRAY_BUFFER, m_vertexArray.size() * sizeof(Vertex),
				 m_vertexArray.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &m_vboIndex);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vboIndex);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indexArray.size() * sizeof(GLuint),
				 m_indexArray.data(), GL_STATIC_DRAW);
#endif // _USE_VBO
}

Cylinder::~Cylinder()
{
#ifdef _USE_VBO
	glDeleteBuffers(1, &m_vboVertex);
	glDeleteBuffers(1, &m_vboIndex);
#endif
}

void Cylinder::draw()
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);

#ifdef _USE_VBO
	glBindBuffer(GL_ARRAY_BUFFER, m_vboVertex);
	glVertexPointer(3, GL_FLOAT, sizeof(Vertex), 0);
	glNormalPointer(GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, n));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vboIndex);
#else // _USE_VBO
	glVertexPointer(3, GL_FLOAT, sizeof(Vertex), m_vertexArray.data());
	glNormalPointer(GL_FLOAT, sizeof(Vertex), (void*)m_vertexArray.data() + offsetof(Vertex, n));
#endif // _USE_VBO

	GLuint *offset;
	GLuint len;

#if _USE_VBO
	offset = NULL;
#else
	offset = m_indexArray.data();
#endif
	int angles = 360 / m_step;
	len = 2 * (angles + 1);
	glDrawElements(GL_TRIANGLE_STRIP, len, GL_UNSIGNED_INT, (void*)offset);

	offset += len;
	len = angles + 2;
	glDrawElements(GL_TRIANGLE_FAN, len, GL_UNSIGNED_INT, (void*)offset);

	offset += len;
	len = angles + 2;
	glDrawElements(GL_TRIANGLE_FAN, len, GL_UNSIGNED_INT, (void*)offset);

#ifdef _USE_VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
#endif // _USE_VBO

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
}
