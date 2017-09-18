#pragma once

#include "Object.h"

class Cylinder : public Object
{
public:
	Cylinder(qreal radius, qreal height, int step = 20);

protected:
	void draw();

private:
	int m_step;
};
