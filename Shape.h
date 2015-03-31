#pragma once

#include"GL\glew.h"
#include"qpoint.h"
#include"qvector2d.h"
#include"qcolor.h"

enum OBJECT_TYPE
{
	NONE,
	SQUARE,
	CIRCLE,
	TRIANGLE,
	PEN,
	FILL,
};

class Shape
{
public:
	Shape(){}
	virtual ~Shape(){}

	virtual void init() = 0;
	virtual void draw() = 0;

	void set_mouse_start(const QPointF& pos)
	{
		mouse_start = pos;
	}

	void set_mouse_end(const QPointF& pos)
	{
		mouse_end = pos;
	}

	void set_color(const QColor& _color)
	{
		color = _color;
	}

	void set_brush_size(int size)
	{
		brush_size = size;
	}

protected:
	QPointF mouse_start;
	QPointF mouse_end;
	QColor color;
	int brush_size;

};