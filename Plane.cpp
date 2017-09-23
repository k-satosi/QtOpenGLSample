#include "Plane.h"

Plane::Plane(QVector3D &normal)
{
	(void)normal;

	Vertex v0 = { { 0, 0, 0 }, { 0, 1, 0 } };
	Vertex v1 = { { 100, 0, 100 }, { 0, 1, 0 } };
	Vertex v2 = { { -100, 0, 100 }, { 0, 1, 0 } };
	Vertex v3 = { { -100, 0, -100 }, { 0, 1, 0 } };
	Vertex v4 = { { 100, 0, -100 }, { 0, 1, 0 } } ;
	int index = 0;

	m_vertexArray.append(v0);
	m_indexArray.append(index++);
	m_vertexArray.append(v1);
	m_indexArray.append(index++);
	m_vertexArray.append(v2);
	m_indexArray.append(index++);
	m_vertexArray.append(v3);
	m_indexArray.append(index++);
	m_vertexArray.append(v4);
	m_indexArray.append(index++);
	m_vertexArray.append(v1);
	m_indexArray.append(index++);
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

Plane::~Plane()
{
#ifdef _USE_VBO
	glDeleteBuffers(1, &m_vboVertex);
	glDeleteBuffers(1, &m_vboIndex);
#endif // _USE_VBO
}

void Plane::draw()
{
	glLightfv(GL_LIGHT0, GL_DIFFUSE, m_color);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);

#ifdef _USE_VBO
	glBindBuffer(GL_ARRAY_BUFFER, m_vboVertex);
	glVertexPointer(3, GL_FLOAT, sizeof(Vertex), 0);
	glNormalPointer(GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, n));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vboIndex);
	glDrawElements(GL_TRIANGLE_FAN, 6, GL_UNSIGNED_INT, NULL);
#else // _USE_VBO
	glVertexPointer(3, GL_FLOAT, sizeof(Vertex), m_vertexArray.data());
	glNormalPointer(GL_FLOAT, sizeof(Vertex), (void*)m_vertexArray.data() + offsetof(Vertex, n));
	glDrawElements(GL_TRIANGLE_FAN, 6, GL_UNSIGNED_INT, m_indexArray.data());
#endif // _USE_VBO


#ifdef _USE_VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
#endif // _USE_VBO

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
}
