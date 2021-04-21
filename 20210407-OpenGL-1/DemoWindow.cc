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
	set_title("OpenGL Demo Window");

	_map = std::make_shared<Map>("map01.txt");
}

void DemoWindow::setup_gl()
{
	glEnable(GL_DEPTH_TEST);

	glClearColor(0.2f, 0.4f, 0.7f, 1.0f);

	glMatrixMode(GL_PROJECTION);
	gluPerspective(
			45.0,								// Угол обзора по вертикали
			double(width()) / double(height()),	// Соотношение сторон
			0.1,								// Расстояние до ближней ПО
			20.0);								// Расстояние до дальней ПО
	glMatrixMode(GL_MODELVIEW);
}


void DemoWindow::draw_cube()
{
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

	glColor3d(0.0, 1.0, 0.0);		// Передняя грань, зелёная
	glVertex3d( 1.0, -1.0,  1.0);
	glVertex3d( 1.0,  1.0,  1.0);
	glVertex3d( 1.0,  1.0, -1.0);
	glVertex3d( 1.0, -1.0, -1.0);

	glColor3d(1.0, 0.0, 1.0);		// Задняя грань, малиновая
	glVertex3d(-1.0,  1.0,  1.0);
	glVertex3d(-1.0, -1.0,  1.0);
	glVertex3d(-1.0, -1.0, -1.0);
	glVertex3d(-1.0,  1.0, -1.0);

	glColor3d(0.0, 0.0, 1.0);		// Правая грань, синяя
	glVertex3d( 1.0,  1.0,  1.0);
	glVertex3d(-1.0,  1.0,  1.0);
	glVertex3d(-1.0,  1.0, -1.0);
	glVertex3d( 1.0,  1.0, -1.0);

	glColor3d(1.0, 1.0, 0.0);		// Левая грань, жёлтая
	glVertex3d(-1.0, -1.0,  1.0);
	glVertex3d( 1.0, -1.0,  1.0);
	glVertex3d( 1.0, -1.0, -1.0);
	glVertex3d(-1.0, -1.0, -1.0);

	glEnd();
}

void DemoWindow::draw_space()
{
	glBegin(GL_QUADS);

	glColor3d(1.0, 0.0, 0.0);		// Нижняя грань, красная
	glVertex3d( 0.0,  1.0,  0.0);
	glVertex3d( 1.0,  1.0,  0.0);
	glVertex3d( 1.0,  0.0,  0.0);
	glVertex3d( 0.0,  0.0,  0.0);

	glColor3d(0.0, 1.0, 1.0);		// Верхняя грань, бирюзовая
	glVertex3d( 0.0,  0.0,  1.0);
	glVertex3d( 1.0,  0.0,  1.0);
	glVertex3d( 1.0,  1.0,  1.0);
	glVertex3d( 0.0,  1.0,  1.0);

	glEnd();
}

void DemoWindow::draw_wall()
{
	glBegin(GL_QUADS);

	glColor3d(0.0, 1.0, 0.0);		// Передняя грань, зелёная
	glVertex3d( 1.0,  0.0,  1.0);
	glVertex3d( 1.0,  1.0,  1.0);
	glVertex3d( 1.0,  1.0,  0.0);
	glVertex3d( 1.0,  0.0,  0.0);

	glColor3d(1.0, 0.0, 1.0);		// Задняя грань, малиновая
	glVertex3d( 0.0,  1.0,  1.0);
	glVertex3d( 0.0,  0.0,  1.0);
	glVertex3d( 0.0,  0.0,  0.0);
	glVertex3d( 0.0,  1.0,  0.0);

	glColor3d(0.0, 0.0, 1.0);		// Правая грань, синяя
	glVertex3d( 1.0,  1.0,  1.0);
	glVertex3d( 0.0,  1.0,  1.0);
	glVertex3d( 0.0,  1.0,  0.0);
	glVertex3d( 1.0,  1.0,  0.0);

	glColor3d(1.0, 1.0, 0.0);		// Левая грань, жёлтая
	glVertex3d( 0.0,  0.0,  1.0);
	glVertex3d( 1.0,  0.0,  1.0);
	glVertex3d( 1.0,  0.0,  0.0);
	glVertex3d( 0.0,  0.0,  0.0);

	glEnd();
}

void DemoWindow::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Очистка

	glLoadIdentity(); // MV = единичная матрица

	gluLookAt(	3.0, 4.0, 2.0,		// Координаты камеры
				0.0, 0.0, 0.0,		// Координаты центра
				0.0, 0.0, 1.0);		// Направление вверх,	MV = C

	glRotated(_cube_angle, 0.0, 0.0, 1.0);

	for (int x = 0; x < _map->width(); ++x)
		for (int y = 0; y < _map->height(); ++y) {
			glPushMatrix();
			glTranslated(x, y, 0.0);

			switch (_map->cell(y, x)) {
			case MapCell::SPACE:	draw_space(); break;
			case MapCell::WALL:		draw_wall(); break;
			default:				;
			}

			glPopMatrix();
		}
}

void DemoWindow::update()
{
	_cube_angle += 1;
	if (_cube_angle >= 360.0)
		_cube_angle -= 360.0;
}
