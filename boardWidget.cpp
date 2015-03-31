
#include"boardWidget.h"
#include"qevent.h"
#include"qapplication.h"

boardWidget::boardWidget(QWidget *parent) : QOpenGLWidget(parent), cur_shape(NULL), cur_type(NONE), cur_brush_size(1)
{
	setFocusPolicy(Qt::StrongFocus);
}

boardWidget::~boardWidget()
{
	for(int i = 0; i < shapes.size(); ++i)
	{
		delete shapes[i];
	}

	shapes.clear();
}

void boardWidget::initializeGL()
{
	glewInit();

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, width(), height(), 0.0, 1.0, -1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}

void boardWidget::resizeGL(int w, int h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, w, h, 0.0, 1.0, -1.0);

}

void boardWidget::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPointSize(1.0f);
	glLineWidth(1.0f);

	int size = shapes.size();

	for(int i = 0; i < size; ++i)
	{
		shapes[i]->draw();
	}

	if(cur_shape)
	{
		cur_shape->draw();
	}
}

void boardWidget::init_cur_shape()
{
	switch(cur_type)
	{
		case CIRCLE:
		{
			cur_shape = new Circle();
			break;
		}
		case SQUARE:
		{
			cur_shape = new Square();
			break;
		}
		case TRIANGLE:
		{
			cur_shape = new Triangle();
			break;
		}
		case PEN:
		{
			cur_shape = new PenShape();
			break;
		}
		case FILL:
			cur_shape = new Fill();
		
	}
		
	cur_shape->set_mouse_start(mouse_start);
	cur_shape->set_color(cur_color);
	cur_shape->set_brush_size(cur_brush_size);
	cur_shape->init();
}

void boardWidget::keyPressEvent(QKeyEvent* e)
{
	if(e->modifiers() == Qt::ControlModifier)
	{
		if(e->key() == Qt::Key_Z)
		{
			if(shapes.empty())
			{
				return;
			}

			if(undo_stack.push(shapes.back()))
			{
				shapes.pop_back();
				repaint();
			}
		}
		else if(e->key() == Qt::Key_Y)
		{
			Shape* shape;

			if(undo_stack.pop(shape))
			{
				shapes.push_back(shape);
				repaint();
			}
		}
		
	}
}

void boardWidget::mousePressEvent(QMouseEvent* e)
{
	if(e->button() == Qt::LeftButton)
	{
		mouse_start = e->localPos();
	}
}

void boardWidget::mouseMoveEvent(QMouseEvent* e)
{
	//Eðer mouse belirli bir mesafeden az kaydýrýlýrsa bir þey yapma
	if(e->buttons() & Qt::LeftButton)
	{
		if ((e->pos() - mouse_start).manhattanLength() < QApplication::startDragDistance())
		{
			return;
		}

		mouse_end = e->localPos();

		if(cur_type != NONE)
		{
			if(cur_shape == NULL)
			{
				init_cur_shape();
			}

			cur_shape->set_mouse_end(mouse_end);
			repaint();
		}
	}
}

void boardWidget::mouseReleaseEvent(QMouseEvent* e)
{
	if(cur_shape)
	{
		shapes.push_back(cur_shape);
		cur_shape = NULL;
		repaint();
	}
}
