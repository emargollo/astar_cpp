#ifndef ASTAR_H
#define ASTAR_H

#include <vector>
#include <map>
#include <unordered_map>
#include <algorithm>
#include "custom_queue.h"

template<class N>
class astar
{
public:
	astar() {};

	~astar() {};

	//builds back the path found from the cameFrom map.
	std::vector<N*> reconstructPath()
	{
		std::vector<N*> path;
		N* current = closedList.back();

		while (current != cameFrom.at(current)) {
			path.push_back(current);
			current = cameFrom.at(current);
		}
		path.push_back(current);

		std::reverse(path.begin(), path.end());
		return path;
	}

	//calculates the path between two node objects, returns false if no path is found
	bool calculatePath(N *begin, N *end)
	{
		cameFrom.clear();
		closedList.clear();
		openList = custom_queue<N*, std::vector<N*>, N>();

		openList.push(begin);
		cameFrom.insert(std::make_pair(begin, begin));
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
					cameFrom.at(*it) = current;
				}

				
				if (openIt == openList.end())
				{
					(*it)->setGValue(cost);
					(*it)->calculateHeuristic(*end);
					cameFrom.insert(std::make_pair(*it, current));
					openList.push(*it);
				}
			}
		}
		return false;
	}
private:
	std::map<N*, N*> cameFrom;
	custom_queue<N*, std::vector<N*>, N> openList;
	std::vector<N*> closedList;
};
#endif /*ASTAR_H*/
