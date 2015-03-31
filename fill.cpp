#include "fill.h"

void Fill::draw()
{
	QPointF center = (mouse_end + mouse_start) * 0.5f;
	QPointF extent = (mouse_end - mouse_start) * 0.5f;

	glDisable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_SMOOTH);

	glColor3f(color.redF(), color.greenF(), color.blueF());

	glLineWidth(brush_size);
	glPointSize(brush_size);

	
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(center.x() - extent.x(), center.y() - extent.y());
	glVertex2f(center.x() - extent.x(), center.y() + extent.y());
	glVertex2f(center.x() + extent.x(), center.y() + extent.y());
	glVertex2f(center.x() + extent.x(), center.y() - extent.y());
	glEnd();

	glBegin(GL_POINTS);
	glVertex2f(center.x() - extent.x(), center.y() - extent.y());
	glVertex2f(center.x() - extent.x(), center.y() + extent.y());
	glVertex2f(center.x() + extent.x(), center.y() + extent.y());
	glVertex2f(center.x() + extent.x(), center.y() - extent.y());
	glEnd();

}