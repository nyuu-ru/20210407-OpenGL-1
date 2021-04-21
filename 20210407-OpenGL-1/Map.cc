/*
 * Map.cc
 *
 *  Created on: 21 апр. 2021 г.
 *      Author: unyuu
 */

#include <fstream>
#include <string>
#include <sstream>

#include "Map.h"

Map::Map(const char *filename)
{
	std::ifstream file;
	file.exceptions(std::ifstream::badbit);
	file.open(filename);

	std::string line;
	std::getline(file, line);

	std::stringstream params_ss(line);
	params_ss >> _width >> _height >> _start_x >> _start_y >> _start_dir;

	/*	_height		  _width
	 * 		|			|
	 * 		v			v
	 * 	std::vector<std::vector<MapCell>>
	 */

	_cells.resize(_height);
	for (int row = 0; row < _height; ++row) {
		_cells[row].resize(_width);
		std::getline(file, line);
		for (int col = 0; col < _width; ++col) {
			switch(line[col]) {
			case '_':	_cells[row][col] = MapCell::SPACE;	break;
			case '#':	_cells[row][col] = MapCell::WALL;	break;
			default:	_cells[row][col] = MapCell::VOID;	break;
			}
		}
	}
}

MapCell Map::cell(int x, int y) const
{
	if (x < 0 or y < 0 or x >= _width or y >= _height)
		return MapCell::VOID;
	return _cells[y][x];
}
