#include "Cuboid.h"

static const Vertex v[] = {
	{ { 1, 1, 1 }, { 0, 0, 1 } },
	{ { 0, 1, 1 }, { 0, 0, 1 } },
	{ { 0, 0, 1 }, { 0, 0, 1 } },
	{ { 1, 0, 1 }, { 0, 0, 1 } },

	{ { 1, 1, 1 }, { 1, 0, 0 } },
	{ { 1, 0, 1 }, { 1, 0, 0 } },
	{ { 1, 0, 0 }, { 1, 0, 0 } },
	{ { 1, 1, 0 }, { 1, 0, 0 } },

	{ { 1, 1, 1 }, { 0, 1, 0 } },
	{ { 1, 1, 0 }, { 0, 1, 0 } },
	{ { 0, 1, 0 }, { 0, 1, 0 } },
	{ { 0, 1, 1 }, { 0, 1, 0 } },

	{ { 0, 1, 1 }, { -1, 0, 0 } },
	{ { 0, 1, 0 }, { -1, 0, 0 } },
	{ { 0, 0, 0 }, { -1, 0, 0 } },
	{ { 0, 0, 1 }, { -1, 0, 0 } },

	{ { 0, 0, 0 }, { 0, -1, 0 } },
	{ { 1, 0, 0 }, { 0, -1, 0 } },
	{ { 1, 0, 1 }, { 0, -1, 0 } },
	{ { 0, 0, 1 }, { 0, -1, 0 } },

	{ { 1, 0, 0 }, { 0, 0, -1 } },
	{ { 0, 0, 0 }, { 0, 0, -1 } },
	{ { 0, 1, 0 }, { 0, 0, -1 } },
	{ { 1, 1, 0 }, { 0, 0, -1 } },
};

static const GLuint i[] = {
	0, 1, 2,   2, 3, 0,
	4, 5, 6,   6, 7, 4,
	8, 9,10,   10,11,8,
	12,13,14,  14,15,12,
	16,17,18,  18,19,16,
	20,21,22,  22,23,20
};

Cuboid::Cuboid(qreal x, qreal y, qreal z)
{
	scale(QVector3D(x, y, z));
#ifdef _USE_VBO
	glGenBuffers(1, &m_vboVertex);
	glBindBuffer(GL_ARRAY_BUFFER, m_vboVertex);
	glBufferData(GL_ARRAY_BUFFER, sizeof(v), v, GL_STATIC_DRAW);

	glGenBuffers(1, &m_vboIndex);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vboIndex);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(i), i, GL_STATIC_DRAW);
#endif // _USE_VBO
}

Cuboid::~Cuboid()
{
#ifdef _USE_VBO
	glDeleteBuffers(1, &m_vboVertex);
	glDeleteBuffers(1, &m_vboIndex);
#endif // _USE_VBO
}

void Cuboid::draw()
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);

#ifdef _USE_VBO
	glBindBuffer(GL_ARRAY_BUFFER, m_vboVertex);
	glVertexPointer(3, GL_FLOAT, sizeof(Vertex), 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vboIndex);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, NULL);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
#else
	glVertexPointer(3, GL_FLOAT, sizeof(Vertex), v);
	glNormalPointer(GL_FLOAT, sizeof(Vertex), (void*)v + offsetof(Vertex, n));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, i);
#endif
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
}
