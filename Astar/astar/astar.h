#ifndef ASTAR_H
#define ASTAR_H

#include <vector>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <memory>
#include "custom_queue.h"

template<class N>
class astar
{
public:
	astar() {};

	~astar() {};

	//builds back the path found from the cameFrom map.
	std::vector<std::shared_ptr<Node2d>> reconstructPath()
	{
		std::vector<std::shared_ptr<Node2d>> path;
		std::shared_ptr<N> current(std::move(closedList.back()));

		while (current != cameFrom.at(current)) {
			path.push_back(current);
			current = cameFrom.at(current);
		}
		path.push_back(current);

		std::reverse(path.begin(), path.end());
		return path;
	}

	//calculates the path between two node objects, returns false if no path is found
	bool calculatePath(std::shared_ptr<N> begin, std::shared_ptr<N> end)
	{
		cameFrom.clear();
		closedList.clear();
		openList = custom_queue<std::shared_ptr<N>, std::vector<std::shared_ptr<N>>, N>();

		openList.push(begin);
		cameFrom.insert(std::make_pair(begin, begin));
		while (!openList.empty())
		{
			std::shared_ptr<N> current = openList.top();
			openList.pop();
			closedList.push_back(current);

			if (*current == *end) return true;

			std::vector<std::shared_ptr<N>> neighbors = current->getNeighbors();
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
	std::map<std::shared_ptr<N>, std::shared_ptr<N>> cameFrom;
	custom_queue<std::shared_ptr<N>, std::vector<std::shared_ptr<N>>, N> openList;
	std::vector<std::shared_ptr<N>> closedList;
};
#endif /*ASTAR_H*/
