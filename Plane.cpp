#include "Plane.h"

Plane::Plane(const QVector3D &normal)
{
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

	QVector3D defaultNormal(0, 1, 0);
#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
	QVector3D nn = normal;
	nn.normalize();
	QVector3D axis = QVector3D::crossProduct(defaultNormal, nn);
	qreal dp = QVector3D::dotProduct(defaultNormal, nn);
	qreal angle = qAcos(dp);
	angle *= 180.0 / M_PI;   // radians to degrees
#else
	QQuaternion q = QQuaternion::rotationTo(defaultNormal, normal);
	QVector3D axis;
	float angle;
	q.getAxisAndAngle(&axis, &angle);
#endif
	rotate(axis, angle);
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
