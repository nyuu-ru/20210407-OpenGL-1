/*
 * Map.h
 *
 *  Created on: 21 апр. 2021 г.
 *      Author: unyuu
 */

#ifndef MAP_H_
#define MAP_H_

#include <vector>

enum class MapCell
{
	VOID,		// Не знаю, что... неизвестный символ на карте?
	SPACE,		// _ - проход
	WALL		// # - стена
};

class Map final
{
protected:
	int _width { 0 }, _height { 0 };
	std::vector<std::vector<MapCell>> _cells;
public:
	Map(const char * filename);

	int height() const { return _height; }
	int width() const  { return _width;  }

	MapCell cell(int x, int y) const;
};

#endif /* MAP_H_ */
