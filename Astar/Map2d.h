#ifndef MAP_2D_H
#define MAP_2D_H
#include <vector>
#include <map>
#include <queue>
#include <functional>
#include <iostream>
#include "Node2d.h"

class Map2d
{
public:
	Map2d(int w, int h);
	Map2d();
	~Map2d();

	void loadMapFrom2dVector(std::vector<std::vector<int>> array);
	Node2d* get(int x, int y);
	void printMap();

private:
	std::vector<Node2d*> nodes;
	int height;
	int width;
};
#endif

