#include"Circle.h"

void Circle::draw()
{
	float radius = mouse_end.x() - mouse_start.x();

	//Enable Anti-Aliasing
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

	glColor3f(color.redF(), color.greenF(), color.blueF());

	glLineWidth(brush_size);

	glBegin(GL_LINE_LOOP);
		for(int i = 0; i < point_count; ++i)
		{
			glVertex2f(mouse_start.x() + (cos(i * angle) * radius), mouse_start.y() + (sin(i * angle) * radius));
		}
	glEnd();

	glDisable(GL_BLEND);
}