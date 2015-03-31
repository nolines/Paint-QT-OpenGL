#include "Triangle.h"

void Triangle::draw()
{
	QPointF center = (mouse_end + mouse_start) * 0.5f;
	QPointF extent = (mouse_end - mouse_start) * 0.5f;

	//Enable Anti-Aliasing
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);

	glColor3f(color.redF(), color.greenF(), color.blueF());

	glLineWidth(brush_size);
	glPointSize(brush_size);

	glBegin(GL_LINE_LOOP);
		glVertex2f(center.x(), center.y() - extent.y());
		glVertex2f(center.x() - extent.x(), center.y() + extent.y());
		glVertex2f(center.x() + extent.x(), center.y() + extent.y());
	glEnd();

	glBegin(GL_POINTS);
		glVertex2f(center.x(), center.y() - extent.y());
		glVertex2f(center.x() - extent.x(), center.y() + extent.y());
		glVertex2f(center.x() + extent.x(), center.y() + extent.y());
	glEnd();

	glDisable(GL_BLEND);
}