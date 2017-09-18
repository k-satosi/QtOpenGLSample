#pragma once

#include "Object.h"

class Cuboid : public Object
{
public:
	Cuboid(qreal x, qreal y, qreal z);

protected:
	void draw();

private:
	GLuint m_vboNormal;
};
