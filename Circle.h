#pragma once

#include"Shape.h"

class Circle : public Shape
{
public:
	Circle(){}
	~Circle(){}

	void init()
	{
		angle = 360.0f / point_count * 0.0174532925f;
	}

	void draw();

private:
	float angle;
	
	static const int point_count = 100;
};