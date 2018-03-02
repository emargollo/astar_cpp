#include "Map2d.h"



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
