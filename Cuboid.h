#pragma once

#include "Object.h"

class Cuboid : public Object
{
public:
	Cuboid(qreal x, qreal y, qreal z);
	~Cuboid();

protected:
	void draw();
};
