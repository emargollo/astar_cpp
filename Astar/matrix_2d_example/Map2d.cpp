#include "Map2d.h"
#include "../astar/astar.h"
#include <ctime>
#include <cstdlib>
#include <sys/timeb.h>
#include <chrono>

Map2d::Map2d()
{
}


Map2d::Map2d(int w, int h)
{
	height = h;
	width = w;
}

Map2d::~Map2d()
{
}

void Map2d::loadMapFrom2dVector(std::vector<std::vector<int>> array)
{
	for (int i = 0; i < height; ++i) 
	{
		for (int j = 0; j < width; ++j) 
		{
			Node2d* n = new Node2d(Vector2d<int>(j, i));
			if (j > 0) 
			{
				n->addNeighbors(get(j-1, i));
			}
			if (i > 0)
			{
				n->addNeighbors(get(j, i - 1));
				if (j < width - 1)
				{
					n->addNeighbors(get(j +1, i -1));
				}
			}
			if (i > 0 && j > 0)
			{
				n->addNeighbors(get(j - 1, i - 1));
			}
			nodes.push_back(n);
		}
	}
}

Node2d* Map2d::get(int x, int y)
{
	int pos = x + y * width;
	return nodes.at(pos);
}

Node2d * Map2d::get(Vector2d<int> pos)
{
	return get(pos.X(), pos.Y());
}

void Map2d::printMap()
{
	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			
			std::cout << get(j, i)->toString();
		}
		std::cout << std::endl;
	}
}

void Map2d::executeTest(int map_width, int map_height)
{
	std::cout << "building map\n";
	Map2d map(map_width, map_height);
	std::vector <std::vector<int> > vec2D(map_height, std::vector<int>(map_width, 0));
	map.loadMapFrom2dVector(vec2D);
	std::cout << "map built\n";

	//map.printMap();
	Vector2d<int> start(rand() % map_width, rand() % map_height);
	Vector2d<int> end(rand() % map_width, rand() % map_height);

	std::cout << "Searching for path from " << start.toString() << " to " << end.toString() << "\n";
	
	auto s = std::chrono::high_resolution_clock::now();
	astar<Node2d> a;
	std::vector<Node2d*> path;
	if (a.calculatePath(map.get(start), map.get(end))) {

		path = a.reconstructPath();
		auto elapsed = std::chrono::high_resolution_clock::now() - s;
		long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();

		std::cout << "Time taken to find path: " << microseconds <<" microseconds" << std::endl;

	}
}
