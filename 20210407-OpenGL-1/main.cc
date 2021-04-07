/*
 * main.cc
 *
 *  Created on: 7 апр. 2021 г.
 *      Author: unyuu
 */

/*
		Библиотеки:

		Для Windows и MinGW:
		mingw32
		SDL2main
		SDL2
		SDL2_image
		opengl32
		glu32

		Для UNIX-подобных:
		SDL2
		SDL2_image
		GL
		GLU
 */

#include <iostream>
#include <stdexcept>

#include <SDL2/SDL.h>
#include <SDL2/SDL_main.h>

#include "DemoWindow.h"

int main(int, char **)
{
	std::cout << "Program started!" << std::endl;

	SDL_Init(SDL_INIT_EVERYTHING);

	try {
		DemoWindow w;

		w.main_loop();
	} catch (const std::exception& e) {
		std::cerr << "При выполнении программы возникла ошибка:\n" <<
				e.what() << std::endl;
		return 1;
	}

	std::cout << "Program ended!" << std::endl;
	return 0;
}


















