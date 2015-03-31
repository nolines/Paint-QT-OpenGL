#include "PenShape.h"

void PenShape::draw()
{
	vertices.push_back(QVector2D(mouse_end.x(), mouse_end.y()));

	int size = vertices.size();

	//Enable Anti-Aliasing
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);

	glColor3f(color.redF(), color.greenF(), color.blueF());

	glLineWidth(brush_size);
	glPointSize((brush_size - 0.5f));

	//Baz� durumlardaki �izim bozuklu�unu d�zeltmek i�in aralara nokta yerle�tiriyoruz.
	//Brush size k���k de�erlerdeyken noktalar belirgin oluyor. Bu y�zden bu kontrol� yap�yoruz.
	if(brush_size > 3)
	{
		glBegin(GL_POINTS);
			for(int i = 0; i < size; ++i)
			{
				glVertex2f(vertices[i].x(), vertices[i].y());
			}
		glEnd();
	}

	glBegin(GL_LINE_STRIP);
		for(int i = 0; i < size; ++i)
		{
			glVertex2f(vertices[i].x(), vertices[i].y());
		}
	glEnd();

	glDisable(GL_BLEND);

}
