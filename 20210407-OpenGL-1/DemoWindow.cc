/*
 * DemoWindow.cc
 *
 *  Created on: 7 апр. 2021 г.
 *      Author: unyuu
 */

#include "DemoWindow.h"

DemoWindow::DemoWindow(int width, int height)
: Window(width, height)
{
	SDL_SetWindowTitle(_window.get(), "OpenGL Demo Window");
}

void DemoWindow::setup_gl()
{
	glClearColor(0.2f, 0.4f, 0.7f, 1.0f);

	glMatrixMode(GL_PROJECTION);
	gluPerspective(
			45.0,								// Угол обзора по вертикали
			double(width()) / double(height()),	// Соотношение сторон
			0.1,								// Расстояние до ближней ПО
			20.0);								// Расстояние до дальней ПО
	glMatrixMode(GL_MODELVIEW);
}

void DemoWindow::render()
{
	glClear(GL_COLOR_BUFFER_BIT); // Очистка

	glLoadIdentity(); // MV = единичная матрица

	gluLookAt(	3.0, 4.0, 2.0,		// Координаты камеры
				0.0, 0.0, 0.0,		// Координаты центра
				0.0, 0.0, 1.0);		// Направление вверх,	MV = C

	glRotated(_cube_angle, 0.0, 0.0, 1.0);

	glBegin(GL_QUADS);

	glColor3d(1.0, 0.0, 0.0);		// Нижняя грань, красная
	glVertex3d(-1.0,  1.0, -1.0);
	glVertex3d( 1.0,  1.0, -1.0);
	glVertex3d( 1.0, -1.0, -1.0);
	glVertex3d(-1.0, -1.0, -1.0);

	glColor3d(0.0, 1.0, 1.0);		// Верхняя грань, бирюзовая
	glVertex3d(-1.0, -1.0,  1.0);
	glVertex3d( 1.0, -1.0,  1.0);
	glVertex3d( 1.0,  1.0,  1.0);
	glVertex3d(-1.0,  1.0,  1.0);

	glEnd();
}

void DemoWindow::update()
{
	_cube_angle += 1;
	if (_cube_angle >= 360.0)
		_cube_angle -= 360.0;
}
