#ifndef ASTAR_H
#define ASTAR_H

#include <vector>
#include <map>
#include <queue>
#include <functional>
#include <unordered_map>
#include <algorithm>
#include "custom_queue.h"

template<class N>
class astar
{
public:
	astar() {};

	~astar() {};

	std::vector<N*> reconstructPath()
	{
		std::vector<N*> path;
		N* current = closedList.back();

		path.push_back(current);
		while (current != current->getPrev())
		{
			current = current->getPrev();
			path.push_back(current);
		}
		std::reverse(path.begin(), path.end());
		return path;
	}

	bool calculatePath(N *begin, N *end)
	{
		openList.push(begin);
		begin->setPrev(begin);
		while (!openList.empty())
		{
			N* current = openList.top();
			openList.pop();
			closedList.push_back(current);

			if (*current == *end) return true;

			std::vector<N*> neighbors = current->getNeighbors();
			for (auto it = neighbors.begin(); it != neighbors.end(); ++it)
			{
				if ((*it)->isBlocked()) continue;
				if (std::find(closedList.begin(), closedList.end(), *it) != closedList.end()) continue;

				double cost = current->getGValue() + current->distance(**it);
				
				auto openIt = openList.find(*it);
				if (openIt != openList.end() && cost < (*it)->getGValue())
				{
					(*it)->setGValue(cost);
					(*it)->setPrev(current);
				}

				
				if (openIt == openList.end())
				{
					(*it)->setGValue(cost);
					(*it)->calculateHeuristic(*end);
					(*it)->setPrev(current);
					openList.push(*it);
				}
			}
		}
		return false;
	}
private:
	custom_queue<N*, std::vector<N*>, N> openList;
	std::vector<N*> closedList;
};
#endif /*ASTAR_H*/
