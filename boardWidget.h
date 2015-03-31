#pragma once

#ifndef boardWidget_H
#define boardWidget_H

#include "Circle.h"
#include "Square.h"
#include "Triangle.h"
#include "PenShape.h"
#include "Stack.h"
#include "fill.h"
#include <glut.h>
#include <qfiledialog.h>

#include <qopenglwidget.h>
#include <QOpenGLShaderProgram>

class boardWidget:public QOpenGLWidget
{
public:
	boardWidget(QWidget *parent = 0);
	~boardWidget();

	void init_cur_shape();

	void set_cur_object(OBJECT_TYPE type)
	{
		cur_type = type;
	}

	void set_color(const QColor& color)
	{
		cur_color = color;
	}

	void set_brush_size(int size)
	{
		cur_brush_size = size;
	}
	

protected:
	void initializeGL();
	void paintGL();
	void resizeGL(int w, int h);

	void mousePressEvent(QMouseEvent* e);
	void mouseMoveEvent(QMouseEvent* e);
	void mouseReleaseEvent(QMouseEvent* e);

	void keyPressEvent(QKeyEvent* e);

private:
	std::vector<Shape*> shapes;
	Shape* cur_shape;
	QColor cur_color;
	int cur_brush_size;
	OBJECT_TYPE cur_type;

	QPointF mouse_start;
	QPointF mouse_end;

	Stack<Shape*> undo_stack;

};

#endif // !BoardWidget_H