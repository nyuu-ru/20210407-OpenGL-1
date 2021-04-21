/*
 * DemoWindow.cc
 *
 *  Created on: 7 апр. 2021 г.
 *      Author: unyuu
 */

#include <numbers>
#include <cmath>
#include "Coords.h"
#include "DemoWindow.h"

DemoWindow::DemoWindow(int width, int height)
: Window(width, height)
{
	SDL_SetRelativeMouseMode(SDL_TRUE);

	set_title("OpenGL Demo Window");

	_map = std::make_shared<Map>("map01.txt");
	_player.spawn(
			Point3D_Cart(_map->start_x(), _map->start_y(), 0.5),
			Point3D_Sph(1.0, _map->start_dir(), std::numbers::pi / 2.));

	_player.set_walk_check_function(
			[&](double x, double y) -> bool {
		int mx = int(floor(x));
		int my = int(floor(y));
		if (_map->cell(mx, my) == MapCell::SPACE)
			return true;
		return false;
	});
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

	_space_list = glGenLists(1);
	_wall_list = glGenLists(1);

	glNewList(_space_list, GL_COMPILE);
	draw_space();
	glEndList();

	glNewList(_wall_list, GL_COMPILE);
	draw_wall();
	glEndList();

	glCullFace(GL_BACK);
	glFrontFace(GL_CW);
	glEnable(GL_CULL_FACE);
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

	glColor3d(0.1, 0.8, 0.1);		// Нижняя грань, красная
	glVertex3d( 0.0,  1.0,  0.0);
	glVertex3d( 1.0,  1.0,  0.0);
	glVertex3d( 1.0,  0.0,  0.0);
	glVertex3d( 0.0,  0.0,  0.0);

	glColor3d(0.1, 0.4, 0.8);		// Верхняя грань, бирюзовая
	glVertex3d( 0.0,  0.0,  1.0);
	glVertex3d( 1.0,  0.0,  1.0);
	glVertex3d( 1.0,  1.0,  1.0);
	glVertex3d( 0.0,  1.0,  1.0);

	glEnd();
}

void DemoWindow::draw_wall()
{
	glBegin(GL_QUADS);

	glColor3d(0.7, 0.7, 0.7);
	glVertex3d( 1.0,  0.0,  1.0);
	glVertex3d( 1.0,  1.0,  1.0);
	glVertex3d( 1.0,  1.0,  0.0);
	glVertex3d( 1.0,  0.0,  0.0);

	glVertex3d( 0.0,  1.0,  1.0);
	glVertex3d( 0.0,  0.0,  1.0);
	glVertex3d( 0.0,  0.0,  0.0);
	glVertex3d( 0.0,  1.0,  0.0);

	glColor3d(0.6, 0.6, 0.6);
	glVertex3d( 1.0,  1.0,  1.0);
	glVertex3d( 0.0,  1.0,  1.0);
	glVertex3d( 0.0,  1.0,  0.0);
	glVertex3d( 1.0,  1.0,  0.0);

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

	auto pos = _player.pos();
	auto dir = _player.dir();
	auto dir_cart = Point3D_Cart(dir);
	auto center = pos;
	center.x += dir_cart.x;
	center.y += dir_cart.y;
	center.z += dir_cart.z;

	gluLookAt(	pos.y, pos.x, pos.z,		// Координаты камеры
				center.y, center.x, center.z,		// Координаты центра
				0.0, 0.0, 1.0);		// Направление вверх,	MV = C

//	glRotated(_cube_angle, 0.0, 0.0, 1.0);

	for (int x = 0; x < _map->width(); ++x)
		for (int y = 0; y < _map->height(); ++y) {
			glPushMatrix();
			glTranslated(x, y, 0.0);

			switch (_map->cell(y, x)) {
			case MapCell::SPACE:	glCallList(_space_list); break;
			case MapCell::WALL:		glCallList(_wall_list); break;
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

void DemoWindow::handle_keys(const Uint8 *keys)
{
	if (keys[SDL_SCANCODE_Q]) _player.turn_left();
	if (keys[SDL_SCANCODE_E]) _player.turn_right();
	if (keys[SDL_SCANCODE_R]) _player.turn_up();
	if (keys[SDL_SCANCODE_F]) _player.turn_down();
	if (keys[SDL_SCANCODE_W]) _player.walk_forward();
	if (keys[SDL_SCANCODE_S]) _player.walk_backward();
	if (keys[SDL_SCANCODE_D]) _player.strafe_right();
	if (keys[SDL_SCANCODE_A]) _player.strafe_left();
}

void DemoWindow::handle_event(const SDL_Event &event)
{
	if (event.type == SDL_MOUSEMOTION) {
		double dphi = double(event.motion.xrel) / 300.0;
		double dtheta = double(event.motion.yrel) / 300.0;
		_player.turn_right(dphi);
		_player.turn_down(dtheta);
	}
}
