#pragma once

#include "shape.h"

class PenShape : public Shape
{
public:
	PenShape(){}
	~PenShape(){}

	void init()
	{
		vertices.push_back(QVector2D(mouse_start.x(), mouse_start.y()));
	}

	void draw();

private:
	std::vector<QVector2D> vertices;
};

